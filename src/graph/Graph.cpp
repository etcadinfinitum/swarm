#include <utility>  // std::pair, std::make_pair
#include <string>
#include <set>
#include <fstream>  // std::ifstream
#include <memory>   // std::shared_ptr, std::make_shared
#include <queue>
#include <iostream>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

Graph::Graph() {
    this->edges = new set<shared_ptr<Edge>>();
    this->vertices = new set<shared_ptr<Vertex>>();
}

/**
 * Copy constructor for graph class.
 */
Graph::Graph(const Graph& other) {
    this->edges = new set<shared_ptr<Edge>>();
    this->vertices = new set<shared_ptr<Vertex>>();
    set<shared_ptr<Vertex>>::iterator it;
    for (it = other.vertices->begin(); it != other.vertices->end(); ++it) {
        // make copy of shared pointer
        shared_ptr<Vertex> v(*it);
        this->vertices->insert(v);
    }
    set<shared_ptr<Edge>>::iterator iter;
    for (iter = other.edges->begin(); iter != other.edges->end(); ++iter) {
        shared_ptr<Edge> e(*iter);
        this->edges->insert(e);
    }
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

/**
 * This method forms an edge between the provided vertices.
 *
 * It does not allow: MULTIGRAPH properties or SELF-CONNECTED vertices.
 *
 * Returns: T/F indicating whether unique edge was added to graph.
 */
bool Graph::join(shared_ptr<Vertex> a, shared_ptr<Vertex> b, bool belongs) {
    if (!a || !b) return false;
    // do not allow self-connection
    if (*(a.get()) == *(b.get())) return false;
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

/**
 * Assignment Operator Overload for Graph.cpp
 * USED FOR "DEEP" COPYING A GRAPH.
 *
 * This method preserves all Vertex* and Edge* objects (i.e. no copies 
 * of these objects are created).
 */
Graph& Graph::operator=(const Graph& rhs) {
    set<shared_ptr<Vertex>>::iterator it;
    for (it = rhs.vertices->begin(); it != rhs.vertices->end(); ++it) {
        // make copy of shared pointer
        shared_ptr<Vertex> v(*it);
        this->vertices->insert(v);
    }
    set<shared_ptr<Edge>>::iterator iter;
    for (iter = rhs.edges->begin(); iter != rhs.edges->end(); ++iter) {
        shared_ptr<Edge> e(*iter);
        this->edges->insert(e);
    }
    return *this;
}

bool Graph::containsEdge(shared_ptr<Edge> e) {
    set<shared_ptr<Edge>>::iterator it;
    for (it = this->edges->begin(); it != this->edges->end(); ++it) {
        if (*((*it).get()) == *(e.get())) {
            return true;
        }
    }
    return false;
}

bool Graph::containsVertex(shared_ptr<Vertex> v) {
    set<shared_ptr<Vertex>>::iterator it;
    for (it = this->vertices->begin(); it != this->vertices->end(); ++it) {
        if (*((*it).get()) == *(v.get())) {
            return true;
        }
    }
    return false;
}

bool Graph::addVertex(shared_ptr<Vertex> v) {
    if (this->containsVertex(v)) {
        return false;
    }
    this->vertices->insert(v);
    return true;
}

/**
 * This method is used to split a tree along the indicated edge into 
 * its two disparate components.
 *
 * Precondition: the this object is a spanning tree with no cycles.
 */
pair<Graph*, Graph*>* Graph::splitTree(shared_ptr<Edge> e) {
    Graph* g1 = new Graph();
    Graph* g2 = new Graph();
    if (!(this->containsEdge(e))) {
        cerr << "Attempting to split graph along edge " << *e
             << " which does not exist in graph." << endl;
        delete g1;
        delete g2;
        return nullptr;
    }
    queue<shared_ptr<Vertex>> q1;
    queue<shared_ptr<Vertex>> q2;
    q1.push(e->getFirst());
    q2.push(e->getSecond());
    // fan out from vertex in q1; check for edges which contain v1, call join in g1 if found, otherwise add vertex only
    while (!q1.empty()) {
        shared_ptr<Vertex> v = q1.front();
        q1.pop();
        set<shared_ptr<Edge>>::iterator it;
        for (it = this->edges->begin(); it != this->edges->end(); ++it) {
            // edge case: edge found is the edge being split along
            if (*((*it).get()) == *(e.get())) continue;
            // edge case: edge has already been added to g1
            if (g1->containsEdge(*it)) continue;
            if (*((*it)->getFirst()) == *v) {
                g1->join(v, (*it)->getSecond());
                q1.push((*it)->getSecond());
            } else if (*((*it)->getSecond()) == *v) {
                g1->join(v, (*it)->getFirst());
                q1.push((*it)->getFirst());
            }
        }
        g1->addVertex(v);
    }
    // repeat for q2/g2
    while (!q2.empty()) {
        shared_ptr<Vertex> v = q2.front();
        q2.pop();
        set<shared_ptr<Edge>>::iterator it;
        for (it = this->edges->begin(); it != this->edges->end(); ++it) {
            // edge case: edge found is the edge being split along
            if (*((*it).get()) == *(e.get())) continue;
            // edge case: edge has already been added to g1
            if (g2->containsEdge(*it)) continue;
            if (*((*it)->getFirst()) == *v) {
                g2->join(v, (*it)->getSecond());
                q2.push((*it)->getSecond());
            } else if (*((*it)->getSecond()) == *v) {
                g2->join(v, (*it)->getFirst());
                q2.push((*it)->getFirst());
            }
        }
        g2->addVertex(v);
    }
    return new pair<Graph*, Graph*>(g1, g2);
}

ostream& operator<<(ostream& out, const Graph& obj) {
    out << "Vertices by name: ";
    set<shared_ptr<Vertex>>::iterator iter;
    for (iter = obj.vertices->begin(); iter != obj.vertices->end(); ++iter) {
        out << *((*iter).get()) << ", ";
    }
    out << "\n";
    out << "Edges by name: ";
    set<shared_ptr<Edge>>::iterator it;
    for (it = obj.edges->begin(); it != obj.edges->end(); ++it) {
        out << *((*it).get()) << ", ";
    }
    out << "\n";
    return out;
}

set<shared_ptr<Vertex>>* Graph::getVertices() {
    return this->vertices;
}

set<shared_ptr<Edge>>* Graph::getEdges() {
    return this->edges;
}
