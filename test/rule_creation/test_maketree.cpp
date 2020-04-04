#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Rule.h"
#include "Generator.h"
#include <cassert>

using namespace std;

// forward declaration

bool testKiteTreeRuleCreation();
bool testYoyoTreeRuleCreation();

int main() {
    assert(testKiteTreeRuleCreation());
    assert(testYoyoTreeRuleCreation());
    return 0;
}

bool testKiteTreeRuleCreation() {
    Graph* g = new Graph();
    assert(g->import("graph_schemas/kite.txt"));
    Generator gtr;
    assert(gtr.makeTree(g));
    gtr.printRules();
    delete g;
    return true;
}

bool testYoyoTreeRuleCreation() {
    Graph* g = new Graph();
    assert(g->import("graph_schemas/yoyo.txt"));
    Generator* gtr = new Generator();
    assert(gtr->makeTree(g));
    gtr->printRules();
    delete g;
    delete gtr;
    return true;
}
