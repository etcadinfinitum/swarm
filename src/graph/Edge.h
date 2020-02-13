#include "Vertex.h"
#include <iostream>
#include <memory>

using namespace std;

#ifndef EDGE_H__
#define EDGE_H__

class Edge {
    private:
        shared_ptr<Vertex> a;
        shared_ptr<Vertex> b;
        bool belongs;
    public:
        Edge(shared_ptr<Vertex>, shared_ptr<Vertex>, bool belongs = true);
        ~Edge();
        friend bool operator==(const Edge& lhs, const Edge& rhs);
        friend bool operator<(const Edge&, const Edge&);
        friend ostream& operator<<(ostream&, const Edge&);
        shared_ptr<Vertex> getFirst() const;
        shared_ptr<Vertex> getSecond() const;
};

#endif          // EDGE_H__
