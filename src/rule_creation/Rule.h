#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <utility>      // std::pair
#include <vector>
#include <iostream>

using namespace std;

#ifndef RULE_H__
#define RULE_H__ 

class Rule {
    private:
        Graph* initialState = nullptr;
        Graph* finalState = nullptr;
        // necessary to ensure state preservation of labels for vertices; label 
        // member of Vertex* will change throughout call stack
        vector<pair<shared_ptr<Vertex>, pair<string, string>*>*>* labelData;
        bool confirmLabelDataForVertexJoin(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2);
    public:
        Rule();
        ~Rule();
        pair<string, string>* getLabelsForNamedVertex(string) const;
        friend ostream& operator<<(ostream&, const Rule&);
        bool addVertex(shared_ptr<Vertex> v, string lhsLabel, string rhsLabel);
        bool lhsJoin(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2);
        bool rhsJoin(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2);
        Graph* getLeftGraph() const;
        Graph* getRightGraph() const;
};

#endif              // RULE_H__
