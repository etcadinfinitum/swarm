// Graph file includes
#include "Graph.cpp"
#include "Vertex.cpp"
#include "Edge.cpp"

// Rule generator includes
#include "Generator.cpp"
#include "Rule.cpp"

// Standard includes
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // Ensure we have a filename for the input graph
    if (argc != 2) {
        cerr << "Invalid number of arguments." << endl;
        return 1;
    }

    // Make graph from argument filename's contents
    Graph* g = new Graph();
    g->import(string(argv[1]));

    // Make generator instance
    Generator* gen = new Generator();
    bool worked = gen->makeTree(g);
    if (!worked) {
        cerr << "The grammar generator encountered an error!" << endl;
    }

    gen->printRules();

    return 0;
}
