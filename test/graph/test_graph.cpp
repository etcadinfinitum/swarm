#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <cassert>

using namespace std;

// forward declarations
bool createEmptyGraph();
bool createNonEmptyGraphFromFile();
bool createNonEmptyGraphFromBoutiqueVertices();
bool testCopyAssignment();
bool testCopyConstructor();
bool testTreeSplitting();
bool testTreeSplittingFailure();

int main() {
    assert(createEmptyGraph());
    assert(createNonEmptyGraphFromFile());
    assert(createNonEmptyGraphFromBoutiqueVertices());
    assert(testCopyAssignment());
    assert(testCopyConstructor());
    assert(testTreeSplitting());
    assert(testTreeSplittingFailure());
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
    cout << "Testing graph construction using join()/separate()...\n";
    Graph g;
    shared_ptr<Vertex> v1 = make_shared<Vertex>("a");
    shared_ptr<Vertex> v2 = make_shared<Vertex>("b");
    shared_ptr<Vertex> v3 = make_shared<Vertex>("c");
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
    cout << "Final graph: \n" << g << endl;
    cout << endl;
    return true;
}

bool testCopyAssignment() {
    cout << "Testing copy assignment...\n";
    Graph g;
    assert(g.import("graph_schemas/cycleThree.txt"));
    Graph h;
    h = g;
    assert(&g != &h);
    cout << "Graph g: \n" << g;
    cout << "Graph h: \n" << h;
    cout << endl;
    return true;
}

bool testCopyConstructor() {
    cout << "Testing copy constructor...\n";
    Graph g;
    assert(g.import("graph_schemas/cycleThree.txt"));
    Graph h(g);
    assert(&g != &h);
    cout << "Graph g: \n" << g;
    cout << "Graph h: \n" << h;
    cout << endl;
    return true;
}

bool testTreeSplitting() {
    cout << "Testing tree splitting along existing edge...\n";
    Graph g;
    shared_ptr<Vertex> v1 = make_shared<Vertex>("a");
    shared_ptr<Vertex> v2 = make_shared<Vertex>("b");
    shared_ptr<Vertex> v3 = make_shared<Vertex>("c");
    shared_ptr<Vertex> v4 = make_shared<Vertex>("d");
    assert(g.join(v1, v2));
    assert(g.join(v2, v3));
    assert(g.join(v3, v4));
    shared_ptr<Edge> eSuccess = make_shared<Edge>(v2, v3);
    pair<Graph*, Graph*>* split1 = g.splitTree(eSuccess);
    assert(split1 != nullptr);
    assert(split1->first != nullptr);
    assert(split1->second != nullptr);
    cout << "G1 half of tree split: \n" << *(split1->first);
    cout << "G2 half of tree split: \n" << *(split1->second);
    assert(split1->first->containsVertex(v1));
    assert(split1->first->containsVertex(v2));
    assert(split1->first->containsEdge(make_shared<Edge>(v1, v2)));
    assert(!split1->first->containsVertex(v3));
    assert(!split1->first->containsVertex(v4));
    assert(!split1->first->containsEdge(eSuccess));
    assert(!split1->first->containsEdge(make_shared<Edge>(v3, v4)));
    assert(split1->second->containsVertex(v3));
    assert(split1->second->containsVertex(v4));
    assert(split1->second->containsEdge(make_shared<Edge>(v3, v4)));
    assert(!split1->second->containsVertex(v1));
    assert(!split1->second->containsVertex(v2));
    assert(!split1->second->containsEdge(eSuccess));
    assert(!split1->second->containsEdge(make_shared<Edge>(v1, v2)));
    cout << endl;
    delete split1->first;
    delete split1->second;
    delete split1;
    return true;
}

bool testTreeSplittingFailure() {
    cout << "Testing tree splitting along nonexistent edge...\n";
    Graph g;
    shared_ptr<Vertex> v1 = make_shared<Vertex>("a");
    shared_ptr<Vertex> v2 = make_shared<Vertex>("b");
    shared_ptr<Vertex> v3 = make_shared<Vertex>("c");
    shared_ptr<Vertex> v4 = make_shared<Vertex>("d");
    assert(g.join(v1, v2));
    assert(g.join(v2, v3));
    assert(g.join(v3, v4));
    shared_ptr<Edge> eFail = make_shared<Edge>(v1, v4);
    pair<Graph*, Graph*>* split1 = g.splitTree(eFail);
    assert(split1 == nullptr);
    cout << endl;
    return true;
}
