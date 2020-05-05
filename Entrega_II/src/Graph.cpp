//
// Created by pedro on 05/05/2020.
//

#include "Graph.h"

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

Vertex::Vertex(int id): id(id) {
}

Edge * Vertex::addEdge(Vertex *dest, double w) {
    Edge * e = new Edge(this, dest, w);
    this->outgoing.push_back(e);
    dest->incoming.push_back(e);
    return e;
}

int Vertex::getID() const {
    return this->id;
}

vector<Edge *> Vertex::getAdj() const {
    return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */

Edge::Edge(Vertex *o, Vertex *d, double w): orig(o), dest(d), weight(w){}

double Edge::getWeight() const {
    return weight;
}

Vertex* Edge::getDest() const {
    return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */

Vertex * Graph::addVertex(const int &id) {
    Vertex *v = findVertex(id);
    if (v != nullptr)
        return v;
    v = new Vertex(id);
    vertexSet.push_back(v);
    return v;
}

Edge * Graph::addEdge(const int &sourc, const int &dest, double w) {
    auto s = findVertex(sourc);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;
    else
        return s->addEdge(d, w);
}

Vertex* Graph::findVertex(const int & id) const {
    for (auto v : vertexSet)
        if (v->id == id)
            return v;
    return nullptr;
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


