#include "Edge.h"
#include "Vertex.h"

Edge::Edge(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, bool belongs) {
    // keep the vertices lexographically ordered
    if (*v1 < *v2) {
        this->a = v1;
        this->b = v2;
    } else {
        this->a = v2;
        this->b = v1;
    }
    // we can specify at creation time whether the 
    // edge is a member of the target graph G.
    this->belongs = belongs;
}

Edge::~Edge() {
    // do not delete member vertices; bad things would happen
}

bool operator==(const Edge& lhs, const Edge& rhs) {
    if (*(lhs.getFirst()) == *(rhs.getFirst()) && *(lhs.getSecond()) == *(rhs.getSecond())) {
        return true;
    } else if (*(lhs.getFirst()) == *(rhs.getSecond()) && *(lhs.getSecond()) == *(rhs.getFirst())) {
        return true;
    }
    return false;
}

bool operator<(const Edge& lhs, const Edge& rhs) {
    // vertex pair is ordered; compare element by element
    if (*(lhs.a) < *(rhs.a)) return true;
    if (*(lhs.a) == *(rhs.a) && *(lhs.b) < *(rhs.b)) return true;
    return false;
}

ostream& operator<<(ostream& out, const Edge& rhs) {
    out << "(" << rhs.a->getName() << ", " << rhs.b->getName() << ")";
    return out;
}

shared_ptr<Vertex> Edge::getFirst() const {
    return a;
}

shared_ptr<Vertex> Edge::getSecond() const {
    return b;
}
