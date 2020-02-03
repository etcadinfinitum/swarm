#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <cassert>

using namespace std;

// forward declarations
bool createEmptyGraph();
bool createNonEmptyGraphFromFile();
bool createNonEmptyGraphFromBoutiqueVertices();

int main() {
    assert(createEmptyGraph());
    assert(createNonEmptyGraphFromFile());
    assert(createNonEmptyGraphFromBoutiqueVertices());
    return 0;
}

bool createEmptyGraph() {
    Graph g;
    return true;
}

bool createNonEmptyGraphFromFile() {
    Graph g;
    assert(g.import("graph_schemas/cycleThree.txt"));
    return true;
}

bool createNonEmptyGraphFromBoutiqueVertices() {
    Graph g;
    Vertex* v1 = new Vertex("a");
    Vertex* v2 = new Vertex("b");
    Vertex* v3 = new Vertex("c");
    cout << "Join v1 and v2 (a, b)..." << endl;
    assert(g.join(v1, v2));
    cout << "Sep v2 and v3 (b, c) (should fail)" << endl;
    assert(!g.separate(v2, v3));
    cout << "Join v2 and v3 (b, c)..." << endl;
    assert(g.join(v2, v3));
    cout << "Join v2 and v3 (b, c) (should fail)..." << endl;
    assert(!g.join(v2, v3));     // duplicate edges should be detected with comparison overload for Edge. 
    cout << "Sep v2 and v3 (b, c) (should succeed)..." << endl;
    assert(g.separate(v2, v3));
    cout << "Sep v2 and v3 (b, c) (should fail)..." << endl;
    assert(!g.separate(v2, v3));
    return true;
}
