//
// Created by pedro on 05/05/2020.
//

#include "Graph.h"

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
/*
template<class T>
Vertex<T>::Vertex(int id): id(id) {}

template<class T>
Edge<T>* Vertex<T>::addEdge(Vertex<T> *dest, double w) {
    Edge<T> * e = new Edge<T>(this, dest, w);
    this->outgoing.push_back(e);
    dest->incoming.push_back(e);
    return e;
}

template<class T>
int Vertex<T>::getID() const {
    return this->id;
}

template<class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
    return this->outgoing;
}

template<class T>
T Vertex<T>::getInfo() const {
    return this->info;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
/*
template<class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w){}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
Vertex<T>* Edge<T>::getDest() const {
    return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
/*
template<class T>
Vertex<T> * Graph<T>::addVertex(const T &id) {
    Vertex<T> *v = findVertex(id);
    if (v != nullptr)
        return v;
    v = new Vertex<T>(id);
    vertexSet.push_back(v);
    return v;
}

template<class T>
Edge<T> * Graph<T>::addEdge(const int &sourc, const int &dest, double w) {
    auto s = findVertex(sourc);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;
    else
        return s->addEdge(d, w);
}

template<class T>
Vertex<T>* Graph<T>::findVertex(const int & id) const {
    for (auto v : vertexSet)
        if (v->id == id)
            return v;
    return nullptr;
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}
*/

