#!/bin/bash

echo -e "Testing Vertex class..."
g++ -o test -I../../src/graph -I. ../../src/graph/Vertex.cpp test_vertex.cpp -g
if [[ $? == 0 ]]; then ./test; fi
if [[ $? == 0 ]]; then valgrind ./test; rm test; fi

echo -e "\nTesting Edge class..."
g++ -o test -I../../src/graph -I. ../../src/graph/Edge.cpp ../../src/graph/Vertex.cpp test_edge.cpp -g
if [[ $? == 0 ]]; then ./test; fi
if [[ $? == 0 ]]; then valgrind ./test; rm test; fi

echo -e "\nTesting Graph class..."
g++ -o test -I../../src/graph -I. ../../src/graph/Graph.cpp ../../src/graph/Edge.cpp ../../src/graph/Vertex.cpp test_graph.cpp -g
if [[ $? == 0 ]]; then ./test; fi
if [[ $? == 0 ]]; then valgrind ./test --leak-check=yes; rm test; fi
