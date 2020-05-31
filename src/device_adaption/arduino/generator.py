import static
import sys
import os
from RuleParser import *

def write_ruleset(rule):
    # TODO: support labels of any data type with proper quotations and string escaping
    return '    { pairs: { { older: %s, newer: %s }, { older: %s, newer: %s }, }, },\n' % (rule[0][0], rule[0][1], rule[1][0], rule[1][1])

def write_rules(rules):
    if not os.path.exists('output'):
        os.mkdir('output')
    with open('output/sketch.ino', 'w') as outfile:
        # write file opening segment
        outfile.write(static.beginning)

        # write out label data
        outfile.write('const uint8_t MAX_LABELS = %s;\n' % len(rules._labels))
        # TODO: adapt variable type to label type
        outfile.write('const uint8_t labels[MAX_LABELS] = {\n')
        for label in sorted(list(rules._labels)):
            outfile.write('    %s,\n' % label)
        outfile.write('};\n\n')
        outfile.write('uint8_t CURR_LABEL_INDEX = 0;\n')
        # TODO: adapt variable type to label type
        outfile.write('int CURR_LABEL = labels[CURR_LABEL_INDEX];\n')

        # write rule label pairs
        outfile.write('const int RULE_COUNT = %s;\n' % len(rules))
        outfile.write('\nrule ruleset[RULE_COUNT] = {\n')
        for rule in rules:
            outfile.write(write_ruleset(list(rule)))
        outfile.write('};\n')

        # write file remainder
        outfile.write(static.end)

def main():
    rules = RuleParser([line for line in sys.stdin.read().splitlines() if line.strip()])
    write_rules(rules)

if __name__=='__main__':
    main()
