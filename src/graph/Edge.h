#include "Vertex.h"
#include <iostream>

using namespace std;

#ifndef EDGE_H__
#define EDGE_H__

class Edge {
    private:
        Vertex* a;
        Vertex* b;
        bool belongs;
    public:
        Edge(Vertex*, Vertex*, bool belongs = true);
        ~Edge();
        friend bool operator==(const Edge& lhs, const Edge& rhs);
        friend bool operator<(const Edge&, const Edge&);
        friend ostream& operator<<(ostream&, const Edge&);
        Vertex* getFirst() const;
        Vertex* getSecond() const;
};

#endif          // EDGE_H__
