#include "Vertex.h"
#include <string>

using namespace std;

Vertex::Vertex(string n) {
    this->label = "";
    this->name = n;
}

Vertex::~Vertex() {
}

void Vertex::setLabel(string l) {
    this->label = l;
}

void Vertex::setName(string name) {
    this->name = name;
}

string Vertex::getName() {
    return this->name;
}

string Vertex::getLabel() {
    return this->label;
}

bool operator==(const Vertex& lhs, const Vertex& rhs) {
    return lhs.name == rhs.name;
}

bool operator<(const Vertex& lhs, const Vertex& rhs) {
    return lhs.name < rhs.name;
}

ostream& operator<<(ostream& o, const Vertex& obj) {
    o << obj.name;
    return o;
}
