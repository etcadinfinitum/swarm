#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Rule.h"
#include <cassert>

using namespace std;

// forward declarations
bool testRuleCreation();
bool testVertexAdd();
bool testGetRHSLHSGraphs();
bool testLeftVertexJoin();
bool testRightVertexJoin();
bool testPrint();

int main() {
    assert(testRuleCreation());
    assert(testGetRHSLHSGraphs());
    assert(testVertexAdd());
    assert(testLeftVertexJoin());
    assert(testRightVertexJoin());
    assert(testPrint());
    return 0;
}

bool testRuleCreation() {
    Rule r;
    Rule* heap = new Rule();
    delete heap;
    return true;
}

bool testGetRHSLHSGraphs() {
    Rule* r = new Rule();
    Graph* lhs = r->getLeftGraph();
    Graph* rhs = r->getRightGraph();
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    // TODO: assert vertex size for both is 0
    delete r;
    return true;
}

bool testVertexAdd() {
    Rule* r = new Rule();
    shared_ptr<Vertex> v1 = make_shared<Vertex>("a");
    assert(r->addVertex(v1, "a", "b"));
    Graph* lhs = r->getLeftGraph();
    Graph* rhs = r->getRightGraph();
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    assert(lhs->containsVertex(v1));
    assert(rhs->containsVertex(v1));
    delete r;
    return true;
}

bool testLeftVertexJoin() {
    Rule* r = new Rule();
    shared_ptr<Vertex> v1 = make_shared<Vertex>("a");
    shared_ptr<Vertex> v2 = make_shared<Vertex>("b");
    shared_ptr<Edge> e = make_shared<Edge>(v1, v2);
    assert(r->addVertex(v1, "a", "b"));
    // NOTE: the fact that addVertex(v2) was not called presents an 
    // interesting problem for rule completeness.
    // The solution here is:
    // Perform a completeness check at the end of a specific operation:
    //    a) at the beginning of the join() call for rules
    //    b) in the operator<< function
    assert(!(r->lhsJoin(v1, v1)));
    assert(!(r->lhsJoin(v1, v2)));
    assert(r->addVertex(v2, "a", "c"));
    assert(r->lhsJoin(v1, v2));
    assert(!(r->lhsJoin(v1, v2)));
    Graph* lhs = r->getLeftGraph();
    assert(lhs != nullptr);
    assert(lhs->containsVertex(v1));
    assert(lhs->containsVertex(v2));
    assert(lhs->containsEdge(e));
    delete r;
    return true;
}

bool testRightVertexJoin() {
    Rule* r = new Rule();
    shared_ptr<Vertex> v1 = make_shared<Vertex>("a");
    shared_ptr<Vertex> v2 = make_shared<Vertex>("b");
    shared_ptr<Edge> e = make_shared<Edge>(v1, v2);
    assert(r->addVertex(v1, "a", "b"));
    assert(!(r->rhsJoin(v1, v1)));
    assert(!(r->rhsJoin(v1, v2)));
    assert(r->addVertex(v2, "a", "c"));
    assert(r->rhsJoin(v1, v2));
    assert(!(r->rhsJoin(v1, v2)));
    Graph* rhs = r->getRightGraph();
    assert(rhs != nullptr);
    assert(rhs->containsVertex(v1));
    assert(rhs->containsVertex(v2));
    assert(rhs->containsEdge(e));
    delete r;
    return true;
}

bool testPrint() {
    Rule* r = new Rule();
    shared_ptr<Vertex> v1 = make_shared<Vertex>("A");
    shared_ptr<Vertex> v2 = make_shared<Vertex>("B");
    shared_ptr<Vertex> v3 = make_shared<Vertex>("C");
    shared_ptr<Edge> e = make_shared<Edge>(v1, v2);
    assert(r->addVertex(v1, "a", "b"));
    assert(r->addVertex(v2, "a", "c"));
    assert(r->addVertex(v3, "a", "d"));
    assert(r->lhsJoin(v1, v2));
    assert(r->lhsJoin(v2, v3));
    assert(r->rhsJoin(v1, v2));
    assert(r->rhsJoin(v2, v3));
    assert(r->rhsJoin(v3, v1));
    cout << *r << endl;
    delete r;
    return true;
}
