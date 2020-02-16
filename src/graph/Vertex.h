#include <string>

using namespace std;

#ifndef VERTEX_H__
#define VERTEX_H__

class Vertex {
    private:
        string label;
        string name;
    public:
        Vertex(string n = "");
        ~Vertex();
        void setLabel(string);
        void setName(string);
        string getName();
        string getLabel();
        friend bool operator==(const Vertex&, const Vertex&);
        friend bool operator<(const Vertex&, const Vertex&);
        friend ostream& operator<<(ostream&, const Vertex&);
};

#endif          // VERTEX_H__
