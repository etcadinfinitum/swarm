#include <utility>  // std::pair, std::make_pair
#include <string>
#include <set>
#include <fstream>  // std::ifstream
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

Graph::Graph() {
    this->edges = new set<Edge*>();
    this->vertices = new set<Vertex*>();
}

Graph::~Graph() {
    set<Edge*>::iterator it;
    for (it = this->edges->begin(); it != this->edges->end(); ++it) {
        delete *it;
    }
    set<Vertex*>::iterator iter;
    for (iter = this->vertices->begin(); iter != this->vertices->end(); ++iter) {
        delete *iter;
    }
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
            Vertex* f = nullptr;
            Vertex* s = nullptr;
            set<Vertex*>::iterator it;
            for (it = this->vertices->begin(); it != this->vertices->end(); ++it) {
                if ((*it)->getName() == first) f = *it;
                if ((*it)->getName() == second) s = *it;
            }
            // if v doesn't exist, create it
            if (f = nullptr) {
                f = new Vertex();
                f->setName(first);
                this->vertices->insert(f);
            }
            if (s == nullptr) {
                s = new Vertex();
                s->setName(second);
                this->vertices->insert(s);
            }
            // create new Edge
            Edge* e = new Edge(s, f);
            this->edges->insert(e);
        }
        graphFile.close();
    } else { 
        cout << "Unable to open file";
        return false;
    }
    return true;
}

bool Graph::join(Vertex* a, Vertex* b, bool belongs) {
    if (a == nullptr || b == nullptr) {
        cerr << "Graph::join(): One or both of the"
             << " vertices are nullptrs." << endl;
        return false;
    }
    Edge* e = new Edge(a, b, belongs);
    this->edges->insert(e);
    return true;
}

bool Graph::separate(Vertex* a, Vertex* b) {
    bool found = false;
    Edge* e = new Edge(a, b, false);
    set<Edge*>::iterator it;
    for (it = this->edges->begin(); it != this->edges->end(); ++it) {
        // compare pointer values for now; may try to check name/label later?
        if (e == *it) this->edges->erase(it);
        found = true;
    }
    delete e;
    return found;
}
