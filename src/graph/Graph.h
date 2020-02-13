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
        set<shared_ptr<Edge>>* edges;
        set<shared_ptr<Vertex>>* vertices;
    public:
        Graph();
        ~Graph();
        bool import(string filename);
        bool join(shared_ptr<Vertex>, shared_ptr<Vertex>, bool = true);
        bool separate(shared_ptr<Vertex>, shared_ptr<Vertex>);
        // TODO: operator overload for ostream
};

#endif          // GRAPH_H__
