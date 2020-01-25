#include "Edge.h"
#include "Vertex.h"

Edge::Edge(Vertex* a, Vertex* b, bool belongs) {
    this->a = a;
    this->b = b;
    // we can specify at creation time whether the 
    // edge is a member of the target graph G.
    this->belongs = belongs;
}

Edge::~Edge() {
    // do not delete member vertices; bad things would happen
}

bool operator==(const Edge& lhs, const Edge& rhs) {
    if (lhs.getFirst() == rhs.getFirst() && lhs.getSecond() == rhs.getSecond()) {
        return true;
    } else if (lhs.getFirst() == rhs.getSecond() && lhs.getSecond() == rhs.getFirst()) {
        return true;
    }
    return false;
}

Vertex* Edge::getFirst() const {
    return a;
}

Vertex* Edge::getSecond() const {
    return b;
}
