#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "Rule.h"
#include <iostream>
#include <set>
#include <utility>

using namespace std;

#ifndef GENERATOR_H__
#define GENERATOR_H__

class Generator {
    private:
        set<Rule*>* ruleset;
        const int singletonLabel;
        int labelCounter = 0;
    public:
        Generator();
        ~Generator();
        bool makeTree(Graph* g);
        void printRules();
        // TODO: makeGraph signature
};

#endif      // GENERATOR_H__
