import json
import sys
import Node
import C_translation
import parse_forwarding_rules

from os.path import splitext, basename

def run(p4_json, commands=None, outfile=None):
    with open(p4_json) as data_file:    
        program = json.load(data_file)

    if commands != None:
        forwardingRules = parse_forwarding_rules.parse(commands)
    else:
        forwardingRules = None

    model = C_translation.run(Node.NodeFactory(program), forwardingRules)
    model = C_translation.post_processing(model)

    #Print output to file
    if outfile == None:
        p4_program_name = splitext(basename(p4_json))[0]
        assert_p4_outfile = "{}.c".format(p4_program_name)
    else:
        assert_p4_outfile = outfile

    with open(assert_p4_outfile, "w") as output:
        output.write(model)

def main():
    if len(sys.argv) > 2:
        run(sys.argv[1], sys.argv[2])
    else:
        run(sys.argv[1])

if __name__ == '__main__':
    main()