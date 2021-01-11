#!/usr/bin/env python2

import logging
logging.getLogger('scapy.runtime').setLevel(logging.ERROR)

import argparse
import threading
import time

from json import load as load_json
from os import path, devnull
from subprocess import call, Popen, PIPE, STDOUT
import subprocess as sp
from time import sleep
from scapy.all import wrpcap, rdpcap, sendp, sniff
from P4_to_C import run as p4_to_c

# ==== Constants =========================================================================

SNIFFING_TIMEOUT_S = 0.75
MAX_TEST_CASES = 10
P4PKTGEN_INFILE = 'p4pktgen.json'
P4PKTGEN_OUTFILE = 'test-cases.json'
P4PKTGEN_PCAP = 'test.pcap'
PATH_TO_P4C = '/home/gabriel/Software/p4c/build/p4c-bm2-ss'
PATH_TO_P4PKTGEN = '/home/gabriel/Software/p4pktgen/my-venv/bin/p4pktgen'

# ==== Helper functions ==================================================================

def hexchar_to_binstr(hexchar):
    return '{0:04b}'.format(int(hexchar, 16))

def pkt_to_binstr(pkt):
    p = str(pkt)
    hexstr = p.encode('hex')
    binstr = ''
    for hexchar in hexstr:
        binstr += hexchar_to_binstr(hexchar)
    return binstr

class Bmv2Sniffer(threading.Thread):
    def __init__(self, port, iface):
        self.port = port
        self.iface = iface
        self.capture = [None, None]
        threading.Thread.__init__(self)
    
    def run(self):
        # iface == None, expecting packet drop
        if self.iface != None:
            # if input_port == output_port, then 2 packets will be sniffed
            # after sniffing 2, there is nothing more to capture
            # in other cases, wait some time before timing out to capture packets
            self.capture = sniff(iface=self.iface, timeout=SNIFFING_TIMEOUT_S, count=2)

# ========================================================================================

class Validator:

    def __init__(self, path_to_p4file, max_test_cases, keep_files):
        self.path_to_p4file = path_to_p4file
        self.p4_program_name = path.splitext(path.basename(self.path_to_p4file))[0]

        self.keep_files = keep_files
        self.max_test_cases = max_test_cases
        self.bmv2_log = 'bmv2log.txt'

        self.p4pktgen_in_json = P4PKTGEN_INFILE
        self.p4pktgen_outfile = P4PKTGEN_OUTFILE
        self.p4pktgen_pcap = P4PKTGEN_PCAP
        self.assertp4_in_json = '{}.json'.format(self.p4_program_name)

        self.test_cases = []
        self.structs = {}
        self.hdr_extractors = {}
        self.hdr_emitters = {}

        self.test_success = 0
        self.test_fail = 0
        self.test_total = 0

    def run(self):
        start_time = time.time()

        self.generate_json()
        self.run_p4pktgen()
        self.parse_p4pktgen_output()
        self.generate_commands_txt()
        self.generate_c_models()
        self.run_c_models()
        self.run_bmv2_tests()
        self.compare_outputs()
        self.cleanup()
        self.summary()

        elapsed_time = time.time() - start_time
        print('Elapsed time: {:.2f} seconds'.format(elapsed_time))

    def generate_json(self):
        '''
        Generates the JSON from the P4 program for both Assert-p4 and p4pktgen/bmv2
        '''
        print('### Generating JSON files from P4 program')
        cmd_assertp4 = '{} {} --toJSON {}.json'.format(
            PATH_TO_P4C, self.path_to_p4file, self.p4_program_name
        )
        cmd_p4pktgen = '{} {} -o p4pktgen.json'.format(
            PATH_TO_P4C, self.path_to_p4file
        )

        with open(devnull, 'w') as null:
            # print(cmd_assertp4.split())
            call(cmd_assertp4.split(), stdout=null, stderr=null)
            # print(cmd_p4pktgen.split())
            call(cmd_p4pktgen.split(), stdout=null, stderr=null)

    def run_p4pktgen(self):
        '''
        Runs p4pktgen
        '''
        print('### Running p4pktgen')
        cmd_p4pktgen = '{} -au p4pktgen.json'.format(PATH_TO_P4PKTGEN)

        with open(devnull, 'w') as null:
            call(cmd_p4pktgen.split(), stdout=null, stderr=null)

    def parse_p4pktgen_output(self):
        '''
        Parses the JSON output of p4pktgen pointed by 'p4pktgen_outfile'
        '''
        print('### Parsing p4pktgen output')
        with open(self.p4pktgen_outfile) as p4pktgen_out:
            test_cases = load_json(p4pktgen_out)
            pcap_pkts = rdpcap(self.p4pktgen_pcap)

            count = 0
            it = -1

            for case in test_cases:
                if case['result'] == 'NO_PACKET_FOUND': continue
                it += 1
                if count >= self.max_test_cases: break

                saved_test = {}
                saved_test['id'] = count
                saved_test['result'] = case['result']
                saved_test['commands'] = case['ss_cli_setup_cmds']
                saved_test['pcap_packet'] = pcap_pkts[it]

                saved_test['packet'] = case['input_packets'][0]
                saved_test['packet']['packet_binstr'] = ''
                for i in range(len(saved_test['packet']['packet_hexstr'])):
                    saved_test['packet']['packet_binstr'] += \
                        hexchar_to_binstr(saved_test['packet']['packet_hexstr'][i])

                saved_test['parser_path'] = []
                for i in range(len(case['parser_path'])):
                    src, _, dst = case['parser_path'][i].split()
                    if i == 0: 
                        saved_test['parser_path'].append(src)
                        saved_test['parser_path'].append(dst)
                    else:
                        saved_test['parser_path'].append(dst)

                self.test_cases.append(saved_test)
                count += 1

    def generate_commands_txt(self):
        '''
        Writes the commands.txt files based on the test cases from p4pktgen
        '''
        print('### Generating commands.txt')
        for test_case in self.test_cases:
            test_case['cmdfile'] = 'commands{}.txt'.format(test_case['id'])
            with open(test_case['cmdfile'], 'w') as f:
                for cmd in test_case['commands']:
                    f.write('{}\n'.format(cmd))
                f.close()

    def generate_c_models(self):
        '''
        Generates the C model of the P4 program with an input packet set.
        '''
        print('### Generating C models')
        for test_case in self.test_cases:
            test_case['c_model'] = '{}{}.c'.format(self.p4_program_name, test_case['id'])
            p4_to_c(self.assertp4_in_json, test_case['cmdfile'], test_case['c_model'])

            lines = []
            with open(test_case['c_model'], 'r') as c_model:
                lines = c_model.readlines()

            # add include for 'memcpy'
            lines.insert(1, '#include<string.h> // [VALIDATION]\n')
            # add include for validation functions
            lines.insert(1, '#include "validation.h" // [VALIDATION]\n')

            # lines to be inserted into 'ParserImpl'
            memset1 = '\tmemset(&hdr, 0, sizeof(headers));\n'
            memset2 = '\tmemset(&meta, 0, sizeof(metadata));\n'
            memset3 = '\tmemset(&standard_metadata, 0, sizeof(standard_metadata_t));\n'
            port = '\tstandard_metadata.ingress_port = {};\n'.format(
                test_case['packet']['port']
            )
            packet_len = '\tstandard_metadata.packet_length = {};\n'.format(
                test_case['packet']['packet_len_bytes']
            )
            validation_lines = [memset1, memset2, memset3, port, packet_len]

            # erase all contents of the file and rewrite it while adding the input packet
            with open(test_case['c_model'], 'w') as c_model:
                inside_ParserImpl = False
                packet_inserted = False
                
                line = 0
                while line < len(lines):
                    # parse each header field for future processing
                    if 'typedef struct {' in lines[line]:
                        self.parse_struct(lines, line)

                    # create functions to fill header with information from input packets
                    if '//Extract ' in lines[line]:
                        self.place_hdr_extraction(lines, line)

                    # create functions to "emit" output packet
                    if '//Emit ' in lines[line]:
                        self.place_hdr_emitter(lines, line)

                    # place function to print output packet
                    if 'end_assertions();' in lines[line] and 'void' not in lines[line]:
                        lines.insert(line+1, '\tv_print_output(); // [VALIDATION]\n')

                    # comment out unnecessary klee calls
                    if 'klee_print_once' in lines[line]:
                        lines[line] = '// {}'.format(lines[line])
                        lines.insert(line+1, '\tprintf("%s\\n", msg);\n')

                    if not packet_inserted:
                        # comment out 'klee_make_symbolic' calls
                        if 'klee_make_symbolic' in lines[line]:
                            lines[line] = '// {}'.format(lines[line])

                        # check if the current line is inside the 'ParserImpl' function
                        if 'void ParserImpl()' in lines[line]:
                            inside_ParserImpl = True

                        # write test packet information before 'start()' call
                        if inside_ParserImpl and 'start()' in lines[line]:
                            c_model.write('\t// [VALIDATION]\n')
                            for validation_line in validation_lines:
                                c_model.write(validation_line)
                            c_model.write('\n')
                            packet_inserted = True
                    
                    c_model.write(lines[line])
                    line += 1

                # include validation functions in the C model
                self.emit_validation_functions(c_model, test_case['packet'])

                c_model.close()

        # emit header file for validation functions
        self.emit_validation_h()
        
    def parse_struct(self, lines, start):
        '''
        Parses a C struct.

        Parameters
        ----------
        lines : string array
            lines of the C program

        start : integer
            line where the struct definition begins (index of `lines`)
        '''
        struct = []
        name = ''
        i = start+1
        finished = False

        while not finished:
            # each line will be either
            #   <type> <field_name>[ : <size_in_bits>];\n 
            # OR
            #   } <struct_name>;\n
            tokens = lines[i][:-2].split() # ignore ';\n'

            # end of struct
            if tokens[0] == '}':
                finished = True
                name = tokens[1]
            
            # field definition
            else:
                type_ = tokens[0]
                name_ = tokens[1]

                grouped_colon = name_[-1] == ':'
                
                field = {}
                field['name'] = name_ if not grouped_colon else name_[:-1]
                field['type'] = type_

                # <type> <field_name>: <size_in_bits>
                if grouped_colon:
                    field['bitsize'] = int(tokens[2])
                # <type> <field_name> : <size_in_bits>
                elif len(tokens) >= 4:
                    field['bitsize'] = int(tokens[3])
                else:
                    field['bitsize'] = 0

                struct.append(field)

            i += 1       

        self.structs[name] = struct     

    def place_hdr_extraction(self, lines, pos):
        '''
        Place the C function to fill the header variables based on the input packet.

        Parameters
        ----------
        lines : string array
            lines of the C program

        pos : integer
            index of `lines` where '//Extract [...]' line is located    
        '''
        # '//Extract hdr.<hdr_name>'
        tokens = lines[pos].split()
        hdr_variable = tokens[1]
        _, hdr_name = hdr_variable.split('.')

        # insert line to call header extractor function
        caller_name = 'v_set_packet_fields_{}'.format(hdr_name)
        lines.insert(pos+1, '\t{}(); // [VALIDATION]\n\n'.format(caller_name))

        # no need to redefine the header extractor funcion
        if hdr_name in self.hdr_extractors: return
        
        # gets the type of the header defined as `hdr_name`
        hdr_type = next((hdr for hdr in self.structs['headers'] \
            if hdr['name'] == hdr_name))['type']

        header_fields = self.structs[hdr_type]

        # defining the function that will get the field values from the input packet
        definition = 'void {}()'.format(caller_name)
        function = '{} {}\n'.format(definition, '{')

        for i in range(len(header_fields)):
            field = header_fields[i]
            if field['name'] == 'isValid': continue

            assignment = '\thdr.{}.{} = v_get_value_from_packet({} {});\n'.format(
                hdr_name, field['name'], '(uint64_t)', field['bitsize']
            )

            function += assignment

        function += '}'
        self.hdr_extractors[hdr_name] = definition, function

    def place_hdr_emitter(self, lines, pos):
        '''
        Place the C functions to "emit" the output packet after processing the input 
        packet

        Parameters
        ----------
        lines : string array
            lines of the C program

        pos : integer
            index of `lines` where '//Emit [...]' line is located    
        '''
        # '//Emit hdr.<hdr_name>'
        tokens = lines[pos].split()
        hdr_variable = tokens[1]
        _, hdr_name = hdr_variable.split('.')

        # insert line to call header emitter function
        caller_name = 'v_emit_header_{}'.format(hdr_name)
        lines.insert(pos+1, '\t{}(); // [VALIDATION]\n\n'.format(caller_name))

        # no need to redefine the header emitter funcion
        if hdr_name in self.hdr_emitters: return
        
        # gets the type of the header defined as `hdr_name`
        hdr_type = next((hdr for hdr in self.structs['headers'] \
            if hdr['name'] == hdr_name))['type']

        header_fields = self.structs[hdr_type]

        # defining the function that will set the header values on the output packet
        definition = 'void {}()'.format(caller_name)
        function = '{} {}\n'.format(definition, '{')
        function += '\tif (hdr.{}.isValid != 1) return;\n\n'.format(hdr_name)

        for i in range(len(header_fields)):
            field = header_fields[i]
            if field['name'] == 'isValid': continue

            emitter = '\tv_add_to_output_packet({0} hdr.{1}.{2}, {0} {3});\n'.format(
                '(uint64_t)', hdr_name, field['name'], field['bitsize']
            )

            function += emitter

        function += '}'
        self.hdr_emitters[hdr_name] = definition, function
  
    def emit_validation_functions(self, c_model, packet):
        '''
        Writes into the C model the helper functions for test packet processing

        Parameters
        ----------
        c_model : file descriptor
            file descriptor of the C model being generated
        
        packet : dict
            input packet parsed from the p4pktgen output
        '''
        c_model.write('\n// [VALIDATION]\n')

        # helper variables
        c_model.write('char* v_input_packet = "{}";\n'.format(packet['packet_binstr']))
        c_model.write('uint64_t v_input_packet_offset = 0;\n\n')
        c_model.write('char* v_output_packet = NULL;\n')
        c_model.write('uint64_t v_output_packet_size_bits = 0;\n\n')

        # packet parser function
        c_model.write('uint64_t v_get_value_from_packet(uint64_t n_bits) {\n')
        c_model.write('\tchar* start = &v_input_packet[v_input_packet_offset];\n')
        c_model.write('\tuint64_t count = 0;\n')
        c_model.write('\tuint64_t result = 0;\n')
        c_model.write('\twhile (count < n_bits) {\n')
        c_model.write('\t\tif (v_input_packet_offset >= strlen(v_input_packet)) break;\n')
    	c_model.write('\t\tresult <<= 1;\n')
        c_model.write('\t\tif (*start++ == \'1\') result ^= 1;\n')
    	c_model.write('\t\tcount++;\n')
    	c_model.write('\t\tv_input_packet_offset++;\n')
        c_model.write('\t}\n')
        c_model.write('\treturn result;\n')
        c_model.write('}\n\n')

        # packet emitter function
        c_model.write('void v_add_to_output_packet(uint64_t value, uint64_t n_bits) {\n')
        c_model.write('\tif (v_output_packet == NULL)\n') 
        c_model.write('\t\tv_output_packet = (char*) calloc(1, sizeof(hdr));\n')
        c_model.write('\n\tchar binstr[n_bits];\n')
        c_model.write('\tfor (int i = n_bits-1; i >= 0; --i) {\n')
        c_model.write('\t\tbinstr[i] = value & 0x1? \'1\' : \'0\';\n')
        c_model.write('\t\tvalue >>= 1;\n')
        c_model.write('\t}\n')
        c_model.write('\tstrncpy(v_output_packet+v_output_packet_size_bits, binstr, n_bits);\n')
        c_model.write('\tv_output_packet_size_bits += n_bits;\n')
        c_model.write('}\n\n')

        # output packet printer function
        c_model.write('void v_print_output() {\n')
        c_model.write('\tint64_t p = assert_forward? standard_metadata.egress_spec : -1;\n')
        c_model.write('\tfprintf(stderr, "egress_spec: %ld\\n", p);\n')
        c_model.write('\tfprintf(stderr, "packet: %s\\n", v_output_packet);\n')
        c_model.write('}\n\n')

        # header extraction functions
        for function in self.hdr_extractors.values():
            c_model.write('{}\n\n'.format(function[1]))

        # header emitting functions
        for function in self.hdr_emitters.values():
            c_model.write('{}\n\n'.format(function[1]))

    def emit_validation_h(self):
        '''
        Creates a file called 'validation.h' which contain the definition of helper 
        functions for test packet processing
        '''
        with open('validation.h', 'w') as h:
            h.write('#include<stdint.h>\n\n')
            h.write('uint64_t v_get_value_from_packet(uint64_t n_bits);\n')
            h.write('void v_add_to_output_packet(uint64_t value, uint64_t n_bits);\n')
            h.write('void v_print_output();\n')
            for function in self.hdr_extractors.values():
                h.write('{};\n'.format(function[0]))
            for function in self.hdr_emitters.values():
                h.write('{};\n'.format(function[0]))
            h.close()

    def run_c_models(self):
        '''
        Compiles, executes and parses the output of the C model

        Places on each test case with key 'c_model_output' a dict with:   
            'port' : port where the output packet was emitted 
            'packet' : binary representation of the packet
            * -1 and None respectively if no packet was emitted by the C model
        '''
        print('### Running C models')
        # running all test cases
        with open(devnull, 'w') as null:
            for case in self.test_cases:
                # compiling
                call(['gcc', case['c_model']], stdout=null, stderr=null)
                # running
                pid = Popen('./a.out', shell=True, stdout=PIPE, stderr=PIPE)
                # getting output
                _, output = pid.communicate()
                # parsing ('egress_spec:', [port], 'packet', [binary string])
                _, egress_spec, _, binstr = output.split()
                case['c_model_output'] = {
                    'port': int(egress_spec), 
                    'packet': binstr if binstr != '(null)' else None
                }
        call('rm -f a.out'.split())

    def run_bmv2_tests(self):
        '''
        Runs each test case on the bmv2 switch

        Algorithm:
            1. setup veth ports
            2. run bmv2
            3. for each test case:
                i) place table entries
                ii) send packet 
                iii) capture output
                iv) clear table entries
            4. kill bmv2
            5. clear veth ports
        '''
        print('### Running tests in Bmv2')
        # 0. get `validation.py` directory
        basedir = path.dirname(path.realpath(__file__))

        # 1. setup veth ports
        print('Setting up veth ports...')
        call(['sudo', '{}/validation/veth_setup.sh'.format(basedir)], 
            stdout=PIPE, stderr=PIPE)

        # bmv2 will have port 0 mapped to veth1, port 1 mapped to veth3 and so on
        #   veth0 <-> veth1
        #   veth2 <-> veth3
        #   veth4 <-> veth5
        #   veth6 <-> veth7
        # the dict below maps which iface must be used to send/sniff packets 
        port2veth = {
            0: 'veth0',
            1: 'veth2',
            2: 'veth4',
            3: 'veth6'
        }
        # 2. run bmv2 
        print('Starting bmv2...')

        outfile = open(self.bmv2_log, 'w')

        bmv2_cmd = 'sudo simple_switch {} {} --log-console'.format(
            self.p4pktgen_in_json,
            '-i0@veth1 -i1@veth3 -i2@veth5 -i3@veth7'
        )
        Popen(bmv2_cmd.split(), stdout=outfile, stderr=outfile)
        sleep(2) # waiting for bmv2 to setup

        # 3. for each test case
        i = 1
        n = len(self.test_cases)
        for case in self.test_cases:
            print('Running test case ({}/{})...'.format(i, n))
            i += 1

            input_port = case['packet']['port']
            c_out_port = case['c_model_output']['port']
            pcap = case['pcap_packet']

            # i) place table entries
            cmd = 'simple_switch_CLI < {}'.format(case['cmdfile'])
            call(cmd, stdout=PIPE, stderr=PIPE, shell=True)  

            # ii/0 - setup sniffer
            out_iface = port2veth[c_out_port] if c_out_port != -1 else None
            sniffer = Bmv2Sniffer(c_out_port, out_iface)
            sniffer.start()
            sleep(0.05) # concede CPU to sniffer

            # ii) send packet         
            # print('sending packet ports {} => {}'.format(input_port, c_out_port))
            sendp(pcap, iface=port2veth[input_port], verbose=False)

            # iii) capture output
            sniffer.join()
            case['bmv2_output'] = [
                pkt_to_binstr(pkt) for pkt in sniffer.capture if pkt != None
            ]
            case['bmv2_output_raw'] = [
                pkt for pkt in sniffer.capture if pkt != None
            ]
                
            # iv) clear table entries
            cmd = 'echo "reset_state" | simple_switch_CLI'
            call(cmd, stdout=PIPE, stderr=PIPE, shell=True)

        # 4. kill bmv2
        print('Stopping bmv2...')
        call('sudo pkill simple_switch', shell=True)

        # 5. clear veth ports
        print('Removing veth ports...')
        call(['sudo', '{}/validation/veth_teardown.sh'.format(basedir)], 
            stdout=PIPE, stderr=PIPE)

        outfile.close()
        
        print('###############################################################')

    def compare_outputs(self):
        '''
        Compares the output of the C model vs bmv2 processing
        
        Algorithm for each test case:
        1. check if pkt was dropped or emitted (bmv2 log)
        2. if pkt was emitted:
            i) check if the output port was the same
            ii) check if the pkt binstr was the same
        3. if pkt was dropped:
            i) check if the C_model dropped it as well
        ''' 
        print('### Comparing outputs')

        bmv2log = []
        with open(self.bmv2_log, 'r') as f:
            bmv2log = f.readlines()

        # # joining logs...
        # name_splitted = self.bmv2_log.rsplit('.', 1)
        # for i in range(1, 11):
        #     splitted_log_name = '{}.{}.{}'.format(name_splitted[0], i, name_splitted[1])
        #     if path.isfile(splitted_log_name):
        #         with open(splitted_log_name, 'r') as f:
        #             bmv2log = f.readlines() + bmv2log

        # if len(bmv2log) == 0:
        #     print('ERROR: could not read bmv2 log')
        #     return

        line = 0
        it = 1
        for case in self.test_cases:
            print('Comparing output of test case #{}...'.format(it))
            it += 1

            input_port = case['packet']['port']
            bmv2_output = case['bmv2_output']
            c_model_output = case['c_model_output']

            # 1. check if pkt was dropped or emited (bmv2 log)
            # 1/1 - find acknowledgement of new pkt in bmv2 log
            while 'Processing packet received on port' not in bmv2log[line]:
                line += 1
                # TODO: why bmv2 does not log the last one?...
                if line >= len(bmv2log):
                    print("bmv2 log truncated... skipping")
                    return
            
            # # outputs
            # print(c_model_output['port'], c_model_output['packet'])
            # print(case['bmv2_output'])

            # 1/2 - find if packet was dropped or emitted
            while 'Dropping packet' not in bmv2log[line] and \
                  'Transmitting packet' not in bmv2log[line]:
                line += 1
                # TODO: why bmv2 does not log the last one?...
                if line >= len(bmv2log):
                    print("bmv2 log truncated... skipping")
                    return

            dropped = True if 'Dropping packet' in bmv2log[line] else False

            # 2. if pkt was emitted:
            if not dropped:
                tline = bmv2log[line].split()
                bmv2_port = int(tline[-1]) 
                # i) check if the output port was the same
                if c_model_output['port'] == bmv2_port:
                    # ii) check if the pkt binstr was the same
                    # ii/1 - get pkt from bmv2 output
                    bmv2_pkt = ''
                    if input_port == bmv2_port:
                        # if the input and output port are the same, the sniffer
                        # captured both packets, so the 2nd must be selected
                        bmv2_pkt = bmv2_output[1] if len(bmv2_output) >= 2 else None
                    else:
                        bmv2_pkt = bmv2_output[0]
                    
                    # ii/2 - compare packets
                    if bmv2_pkt == c_model_output['packet']:
                        print('SUCCESS: emitted packets are the same')
                        self.test_success += 1
                    else:
                        # workaround: check for scapy bug - trailing byte
                        # [...] Transmitting packet of size X out of port Y
                        size = int(tline[-5]) * 8 # X is in bytes
                        if bmv2_pkt[:size] == c_model_output['packet']:
                            print('SUCCESS: emitted packets are the same')
                            self.test_success += 1
                        else:
                            print('ERROR: emitted packets are not the same')
                            print('cout: {}'.format(c_model_output['packet']))
                            print('bmv2: {}'.format(bmv2_pkt))
                            # print(len(str(case['bmv2_output_raw'][1])))
                            # print(bmv2_output)
                            self.test_fail += 1
                
                # ERROR: output ports were not the same
                else:
                    print('ERROR: bmv2 emitted in port {} but c model in {}'\
                        .format(bmv2_port, c_model_output['port']))
                    self.test_fail += 1

            # 3. if pkt was dropped:
            if dropped:
                # i) check if the C_model dropped it as well
                if c_model_output['port'] == -1:
                    print('SUCCESS: both bmv2 and c model dropped the packet')
                    self.test_success += 1
                else:
                    print('ERROR: bmv2 dropped but c model didnt')
                    print(c_model_output)
                    self.test_fail += 1

            
            self.test_total += 1

            print('----------------------------------------------------------')
        print('###############################################################')        

    def cleanup(self):
        '''
        Cleans all generated files
        '''
        if keep_files: return
        print('### Cleaning up...')

        files = [
            P4PKTGEN_INFILE, P4PKTGEN_OUTFILE, P4PKTGEN_PCAP,
            '{}.json'.format(self.p4_program_name), 
            '{}*.c'.format(self.p4_program_name), 'commands*.txt',
            self.bmv2_log, 'validation.h'
        ]
        
        for file in files:
            cmd_rm = 'rm -f {}'.format(file)
            call(cmd_rm, shell=True)

    def summary(self):
        '''
        Summarizes the validation results
        '''
        if self.test_total == 0:
            print 'ERROR: no tests were evaluated.'
            exit(1)

        percent_success = ((self.test_success*1.0)/self.test_total) * 100.0
        percent_failed = ((self.test_fail*1.0)/self.test_total) * 100.0

        print('###############################################################')
        print('### Summary')
        print('P4 Program: {}'.format(self.p4_program_name))
        print('Total tests: {}'.format(self.test_total))
        print('')
        print('Successful tests: {} ({:.2f}%)'.format(self.test_success, percent_success))
        print('Failed tests: {} ({:.2f}%)'.format(self.test_fail, percent_failed))
        print('###############################################################')

# ========================================================================================

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('p4file', type=str, help='path to p4 program (.p4)')
    parser.add_argument('-t', '--max-test-cases', type=int, default=MAX_TEST_CASES,
        help='number of test cases (default: 10)')
    parser.add_argument('-k', '--keep-files', action='store_const', const=True,
        help='if set, does not perform cleanup activities after validation')
    parser.add_argument('--p4c', type=str, help='path to p4c-bm2-ss binary')
    parser.add_argument('--p4pktgen', type=str, help='path to p4pktgen binary')
    args = parser.parse_args()

    p4 = args.p4file
    max_test_cases = args.max_test_cases
    keep_files = True if args.keep_files else False

    # finding p4c-bm2-ss binary
    PATH_TO_P4C = args.p4c
    if PATH_TO_P4C == None:
        find_p4c = 'find {} -type f -name p4c-bm2-ss'.format(path.expanduser('~'))
        out, _ = Popen(find_p4c.split(), stdout=PIPE).communicate()
        PATH_TO_P4C = out.split()[0] if out else None

        if PATH_TO_P4C == None:
            print('p4c-bm2-ss not found in your home directory. Please inform the path to ' + \
                  'p4c-bm2-ss using argument `--p4c`.')
            exit(1)

    # findind p4pktgen binary
    PATH_TO_P4PKTGEN = args.p4pktgen
    if PATH_TO_P4PKTGEN == None:
        find_p4pktgen = 'find {} -type f -name p4pktgen'.format(path.expanduser('~'))
        out, _ = Popen(find_p4pktgen.split(), stdout=PIPE).communicate()
        PATH_TO_P4PKTGEN = out.split()[0] if out else None

        if PATH_TO_P4PKTGEN == None:
            print('p4pktgen not found in your home directory. Please inform the path to ' + \
                  ' p4pktgen using argument `--p4pktgen`.')
            exit(1)

    validator = Validator(args.p4file, args.max_test_cases, args.keep_files)
    validator.run()