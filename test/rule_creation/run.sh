#!/bin/bash

echo -e "Testing Rule class..."

g++ -o test -I../../src/rule_creation -I../../src/graph -I. ../../src/graph/Vertex.cpp ../../src/graph/Edge.cpp ../../src/graph/Graph.cpp ../../src/rule_creation/Rule.cpp test_rule.cpp -g

if [[ $? == 0 ]]; then ./test; fi
if [[ $? == 0 ]]; then valgrind ./test; rm test; fi

echo -e "Testing Generator class (MakeTree only)..."

g++ -o test -I../../src/rule_creation -I../../src/graph -I. ../../src/graph/Vertex.cpp ../../src/graph/Edge.cpp ../../src/graph/Graph.cpp ../../src/rule_creation/Rule.cpp ../../src/rule_creation/Generator.cpp test_maketree.cpp -g

if [[ $? == 0 ]]; then ./test; fi
if [[ $? == 0 ]]; then valgrind ./test; rm test; fi
