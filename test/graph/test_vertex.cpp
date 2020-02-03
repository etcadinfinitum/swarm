#include "Vertex.h"
#include <cassert>

using namespace std;

// forward declarations
bool testCreationAndRenaming();
bool testEquality();

int main() {
    assert(testCreationAndRenaming());
    assert(testEquality());
    return 0;
}

bool testCreationAndRenaming() {
    Vertex* v1 = new Vertex();
    assert(v1->getName() == "");
    assert(v1->getLabel() == "");
    v1->setName("myName");
    assert(v1->getName() == "myName");
    v1->setLabel("myLabel");
    assert(v1->getLabel() == "myLabel");
    delete v1;
    return true;
}

bool testEquality() {
    Vertex* v1 = new Vertex();
    v1->setName("1");
    assert(*v1 == *v1);
    Vertex* v2 = new Vertex();
    v2->setName("2");
    assert(!(*v1 == *v2));
    Vertex* v3 = new Vertex();
    v3->setName("1");
    assert(*v1 == *v3);
    delete v1;
    delete v2;
    delete v3;
    return true;
}
