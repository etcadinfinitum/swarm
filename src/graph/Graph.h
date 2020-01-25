#include <set>
#include <string>
#include <iostream>
#include "Edge.h"
#include "Vertex.h"

using namespace std;

#ifndef GRAPH_H__
#define GRAPH_H__

class Graph {
    private:
        set<Edge*>* edges;
        set<Vertex*>* vertices;
    public:
        Graph();
        ~Graph();
        bool import(string filename);
        bool join(Vertex*, Vertex*, bool = true);
        bool separate(Vertex*, Vertex*);
        // TODO: operator overload for copy, ostream
};

#endif          // GRAPH_H__
