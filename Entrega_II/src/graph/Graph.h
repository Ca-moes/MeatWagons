/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
typedef pair<double, double> coord;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
	int id;
	int tag;
	int dp;
	T info;
	vector<Edge<T> *> outgoing;
	vector<Edge<T>*> incoming;
    Edge<T>* addEdge(Vertex *dest, double w);
	Vertex(int id);
    Vertex(T info);

	bool visited;  // for path finding
    Edge<T>*path; // for path finding

public:
	int getID() const;
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
	friend class Graph<T>;
};


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	Vertex<T> * orig;
	Vertex<T> * dest;
	double weight;
	int id;
	Edge(Vertex<T> *o, Vertex<T> *d, double w);

public:
	double getWeight() const;
	Vertex<T> *getDest() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	Vertex<T>* findVertex(const int &id) const;
    Vertex<T>* findVertex(const T &info) const;
public:
	vector<Vertex<T> *> getVertexSet() const;
	Vertex<T> *addVertex(const T &id);
	Edge<T> *addEdge(const int &sourc, const int &dest, double w);
};

template<class T>
Vertex<T>::Vertex(int id): id(id) {}

template<class T>
Vertex<T>::Vertex(T info): info(info) {}

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
template<class T>
Vertex<T> * Graph<T>::addVertex(const T &id) {
    Vertex<T> *v = findVertex(id);
    if (v != nullptr)
        return v;
    v = new Vertex<T>(id);
    v->id=vertexSet.size();
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

template<class T>
Vertex<T> *Graph<T>::findVertex(const T &info) const {
    for (auto v : vertexSet)
        if (v->info == info)
            return v;
    return nullptr;
}


#endif /* GRAPH_H_ */
