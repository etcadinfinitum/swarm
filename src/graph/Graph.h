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
        Graph(const Graph& other);
        ~Graph();
        bool import(string filename);
        bool join(shared_ptr<Vertex>, shared_ptr<Vertex>, bool = true);
        bool separate(shared_ptr<Vertex>, shared_ptr<Vertex>);
        bool containsEdge(shared_ptr<Edge>);
        bool containsVertex(shared_ptr<Vertex>);
        bool addVertex(shared_ptr<Vertex>);
        pair<Graph*, Graph*>* splitTree(shared_ptr<Edge> e);
        Graph& operator=(const Graph& rhs);
        friend ostream& operator<<(ostream&, const Graph&);
        set<shared_ptr<Vertex>>* getVertices();
        set<shared_ptr<Edge>>* getEdges();
};

#endif          // GRAPH_H__
