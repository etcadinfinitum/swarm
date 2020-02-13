#include <utility>  // std::pair, std::make_pair
#include <string>
#include <set>
#include <fstream>  // std::ifstream
#include <memory>   // std::shared_ptr, std::make_shared
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

Graph::Graph() {
    this->edges = new set<shared_ptr<Edge>>();
    this->vertices = new set<shared_ptr<Vertex>>();
}

/**
 * The Graph and Edge classes use smart pointers to manage 
 * shared memory space; hence, only top-level objects are 
 * destroyed in the Graph destructor.
 */
Graph::~Graph() {
    delete edges;
    delete vertices;
}

/**
 * A utility method for building a partially-connected 
 * graph based on a schematic described in a text file.
 *
 * The current implementation requires the text file 
 * to contain delimited pairs of vertices, one per line.
 * The default delimiter is '*'.
 *
 * The vertices are expected to be uniquely named, and 
 * when constructing edges, existing vertices will be 
 * searched for a matching name before creating a new 
 * vertex.
 *
 * For example, a text file could contain the following 
 * contents:
 * A*X
 * X*Y
 * Y*A
 * This schematic constructs a 3-node cycle.
 */
bool Graph::import(string filename) {
    string line;
    int lineNum = 1;
    string delim = "*";
    ifstream graphFile(filename);
    if (graphFile.is_open()) {
        while (getline(graphFile, line)) {
            // split line by edge delimiter
            // NOTE: assuming that the line doesn't have any whitespace; 
            // use a strip function if desired.
            if (line.find(delim) == string::npos) {
                // no delimiter found; invalid format
                cerr << "Error parsing line " << lineNum<< " in import file " << filename;
                cerr << ". Line was: " << line << endl;
            }
            string first = line.substr(0, line.find(delim));
            string second = line.substr(line.find(delim) + 1, string::npos);
            // search for vertices by name
            shared_ptr<Vertex> f;
            shared_ptr<Vertex> s;
            set<shared_ptr<Vertex>>::iterator it;
            for (it = this->vertices->begin(); it != this->vertices->end(); ++it) {
                if ((*it)->getName() == first) f = *it;
                if ((*it)->getName() == second) s = *it;
            }
            // if v doesn't exist, create it
            if (!f) {
                f = make_shared<Vertex>(first);
                this->vertices->insert(f);
            }
            if (!s) {
                s = make_shared<Vertex>(second);
                this->vertices->insert(s);
            }
            // create new Edge
            this->join(f, s);
        }
        graphFile.close();
    } else { 
        cout << "Unable to open file" << endl;
        return false;
    }
    return true;
}

bool Graph::join(shared_ptr<Vertex> a, shared_ptr<Vertex> b, bool belongs) {
    if (!a || !b) return false;
    this->vertices->insert(a);
    this->vertices->insert(b);
    shared_ptr<Edge> e = make_shared<Edge>(a, b, belongs);
    bool found = false;
    set<shared_ptr<Edge>>::iterator it;
    for (it = this->edges->begin(); it != this->edges->end(); ++it) {
        if (*e == *(*it)) {
            found = true;
        }
    }
    if (found) {
        return false;
    }
    this->edges->insert(e);
    return true;
}

bool Graph::separate(shared_ptr<Vertex> a, shared_ptr<Vertex> b) {
    if (!a || !b) return false;
    bool found = false;
    shared_ptr<Edge> e = make_shared<Edge>(a, b, false);
    set<shared_ptr<Edge>>::iterator it;
    for (it = this->edges->begin(); it != this->edges->end(); ++it) {
        if (*e == *(*it)) {
            this->edges->erase(it);
            found = true;
            break;
        }
    }
    return found;
}
