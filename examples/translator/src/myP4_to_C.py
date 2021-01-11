import json
import sys
import Node
import myC_translation
import parse_forwarding_rules

from os.path import splitext, basename

def run(p4_json, input_json, iterN, commands=None, outfile=None):
    with open(p4_json) as data_file:    
        program = json.load(data_file)
        # print program
        # print "#########################"

    if commands != None:
        forwardingRules = parse_forwarding_rules.parse(commands)
    else:
        forwardingRules = None

    if input_json != '0':
        with open(input_json) as input_file:    
            inputProgram = json.load(input_file)

        model = myC_translation.run(Node.NodeFactory(program), forwardingRules, Node.NodeFactory(inputProgram), iterN)
    else:
        model = myC_translation.run(Node.NodeFactory(program), forwardingRules, 0, iterN)
    
    model = myC_translation.post_processing(model)

    #Print output to file
    if outfile == None:
        p4_program_name = splitext(basename(p4_json))[0]
        assert_p4_outfile = "{}.c".format(p4_program_name)
    else:
        assert_p4_outfile = outfile

    with open(assert_p4_outfile, "w") as output:
        output.write(model)

def main():
    print len(sys.argv)
    if len(sys.argv) > 4:
        run(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
    else:
        run(sys.argv[1], sys.argv[2], sys.argv[3])

if __name__ == '__main__':
    main()