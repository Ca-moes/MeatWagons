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

class Edge;
class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
class Vertex {
	int id;
	int tag;
	int dp;
	vector<Edge*> outgoing;
	vector<Edge*> incoming;
	Edge * addEdge(Vertex *dest, double w);
	Vertex(int id);

	bool visited;  // for path finding
	Edge *path; // for path finding

public:
	int getID() const;
	vector<Edge *> getAdj() const;
	friend class Graph;
};


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
class Edge {
	Vertex * orig;
	Vertex * dest;
	double weight;
	int id;
	Edge(Vertex *o, Vertex *d, double w);

public:
	double getWeight() const;
	Vertex *getDest() const;

	friend class Graph;
	friend class Vertex;
};


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
class Graph {
	vector<Vertex *> vertexSet;
	Vertex* findVertex(const int &id) const;
public:
	vector<Vertex *> getVertexSet() const;
	Vertex *addVertex(const int &id);
	Edge *addEdge(const int &sourc, const int &dest, double w);
};


#endif /* GRAPH_H_ */
