#include "Edge.h"
#include "Vertex.h"
#include <cassert>

using namespace std;

// forward declarations
bool testCreation();
bool testEquality();
bool testLessThanOperator();

int main() {
    assert(testCreation());
    assert(testEquality());
    assert(testLessThanOperator());
    return 0;
}

bool testCreation() {
    Vertex* v1 = new Vertex("a");
    Vertex* v2 = new Vertex("b");
    Edge* e1 = new Edge(v1, v2, false);
    assert(*(e1->getFirst()) == *v1);
    assert(*(e1->getSecond()) == *v2);
    delete e1;
    delete v1;
    delete v2;
    return true;
}

bool testEquality() {
    Vertex* v1 = new Vertex("a");
    Vertex* v2 = new Vertex("b");
    Vertex* v3 = new Vertex("c");
    // different obj/ptr, same name
    Vertex* v4 = new Vertex("b");
    Edge* ex1f = new Edge(v1, v2, false);
    Edge* ex1b = new Edge(v2, v1, false);
    Edge* ex2f = new Edge(v1, v3, false);
    Edge* ex2b = new Edge(v3, v1, false);
    Edge* ex1repeat = new Edge(v4, v1, false);
    assert(*ex1f == *ex1b);
    assert(*ex1f == *ex1f);
    assert(!(*ex1b == *ex2f));
    assert(*ex2f == *ex2b);
    assert(!(*ex1f == *ex2f));
    assert(*ex1f == *ex1repeat);
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete ex1f;
    delete ex1b;
    delete ex2f;
    delete ex2b;
    delete ex1repeat;
    return true;
}

bool testLessThanOperator() {
    // create vertices
    Vertex* v1 = new Vertex("a");
    Vertex* v2 = new Vertex("b");
    Vertex* v3 = new Vertex("c");
    Vertex* v4 = new Vertex("b");                       // different obj/ptr, same name
    // create edges
    Edge* e1 = new Edge(v1, v1, false);     // (a, a)
    Edge* e2 = new Edge(v2, v1, false);     // (a, b)
    Edge* e3 = new Edge(v2, v4, false);     // (b, b)
    Edge* e4 = new Edge(v1, v3, false);     // (a, c)
    assert(*e1 < *e2);
    assert(*e4 < *e3);
    assert(*e2 < *e3);
    assert(*e1 < *e4);
    assert(!(*e1 < *e1));
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete e1;
    delete e2;
    delete e3;
    delete e4;
    return true;
}
