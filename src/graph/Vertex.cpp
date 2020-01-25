#include "Vertex.h"
#include <string>

using namespace std;

Vertex::Vertex() {
    this->label = "";
    this->name = "";
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
