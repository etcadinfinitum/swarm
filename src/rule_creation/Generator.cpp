#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "Rule.h"
#include "Generator.h"
#include <iostream>
#include <set>
#include <utility>
#include <queue>

using namespace std;

Generator::Generator() : singletonLabel(0) {
    ruleset = new set<Rule*>();
}

Generator::~Generator() {
    set<Rule*>::iterator it;
    for (it = this->ruleset->begin(); it != this->ruleset->end(); ++it) {
        delete *it;
    }
    delete ruleset;
}

bool Generator::makeTree(Graph* g) {
    // represent processed edges to avoid backtracking
    set<shared_ptr<Vertex>> processed;
    set<shared_ptr<Edge>> hasRule;
    // represent node to fan out from + edge rule to construct
    // has format (currVertex, prevEdge)
    // currVertex should have existing label
    queue<pair<shared_ptr<Vertex>, shared_ptr<Edge>>> next;
    // check to ensure g has edges (should be fully formed tree)
    if (g->getEdges()->empty()) return false;
    // choose starting edge
    // TODO: select randomly instead of grabbing first
    shared_ptr<Edge> tmp = *(g->getEdges()->begin());
    // set labels for initial edge
    tmp->getFirst()->setLabel(to_string(singletonLabel));
    tmp->getSecond()->setLabel(to_string(singletonLabel));
    // add initial edge to queue
    next.push(make_pair(tmp->getFirst(), tmp));
    next.push(make_pair(tmp->getSecond(), tmp));
    while (!next.empty()) {
        // pop first item from queue
        pair<shared_ptr<Vertex>, shared_ptr<Edge>> popped = next.front();
        next.pop();
        // if popped is in processed, continue
        if (processed.find(popped.first) != processed.end()) continue;
        // iterate through all edges in g, 
        // pushing all vertices if edge contains popped
        set<shared_ptr<Edge>>::iterator it;
        for (it = g->getEdges()->begin(); it != g->getEdges()->end(); ++it) {
            // do not enqueue same edge
            if (*it == popped.second) continue;
            if ((*it)->getFirst() == popped.first) {
                // set singleton label for it->second
                (*it)->getSecond()->setLabel(to_string(singletonLabel));
                // enqueue (it->second, it)
                next.push(make_pair((*it)->getSecond(), (*it)));
            } else if ((*it)->getSecond() == popped.first) {
                // set singleton label for it->second
                (*it)->getFirst()->setLabel(to_string(singletonLabel));
                // enqueue (it->second, it)
                next.push(make_pair((*it)->getFirst(), (*it)));
            }
        }
        // add popped vertex to processed set
        processed.insert(popped.first);
        // if Edge already has rule, do not process
        if (hasRule.find(popped.second) != hasRule.end()) continue;

        // construct rule for edge
        Rule* newRule = new Rule();
        // get paired vertex in edge (not the popped vertex)
        shared_ptr<Vertex> altVtx = popped.second->getFirst();
        if (popped.first == altVtx) altVtx = popped.second->getSecond();
        // assign new label to focal vertex
        string firstVtxOldLabel = popped.first->getLabel();
        string firstVtxNewLabel = to_string(++this->labelCounter);
        popped.first->setLabel(firstVtxNewLabel);
        // assign new label to alt vertex
        string secondVtxOldLabel = altVtx->getLabel();
        string secondVtxNewLabel = to_string(++this->labelCounter);
        altVtx->setLabel(secondVtxNewLabel);
        // add both vertices to rule
        newRule->addVertex(popped.first, firstVtxOldLabel, firstVtxNewLabel);
        newRule->addVertex(altVtx, secondVtxOldLabel, secondVtxNewLabel);
        // perform rhsJoin on vertices
        newRule->rhsJoin(popped.first, altVtx);
        // add rule to ruleset
        this->ruleset->insert(newRule);
        // add popped edge to hasRule set
        hasRule.insert(popped.second);
    }
    return true;
}

void Generator::printRules() {
    set<Rule*>::iterator it;
    for (it = this->ruleset->begin(); it != this->ruleset->end(); ++it) {
        cout << *(*it) << endl;
    }
}
