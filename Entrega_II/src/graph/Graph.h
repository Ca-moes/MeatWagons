/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <map>
#include "MutablePriorityQueue.h"
#include "Path.h"
#include "prison/Prisoner.h"

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
	int tag; // 0, for normal ; 1, for relevant ; 2, for highways
	int dp;
	T info;
	vector<Edge<T> *> outgoing;
	vector<Edge<T>*> incoming;
    Edge<T>* addEdge(Vertex *dest, double w);
	Vertex(int id);
    Vertex(T info);

	bool visited;  // for path finding

    // A-Star
    double dist;
    double actualDist;
    Vertex<T> * path;

public:
    int queueIndex;

	int getID() const;
	int getTag() const;
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
    vector<Edge<T> *> getIncoming() const;
    double getCostTo(int dest_id) const;
    double getDist() const;
    void setTag(int tag);

    bool operator<(const Vertex &v2) const;
    bool operator>(const Vertex &v2) const;
    bool operator<=(const Vertex &v2) const;
    bool operator>=(const Vertex &v2) const;

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
 * Class POI
 * ================================================================================================
 */
template <class T>
class POI {
    string name;
    int id;

public:
    POI(string name, int id) ;
    string getName() const;
    int getID() const;

    string toString() const;
};



/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	unordered_map<int, int> vertexMap;
    vector<POI<T>*> pois;
    vector<int> highways;

	double maxX;
    double minX;
    double maxY;
    double minY;

    Vertex<T> * findVertex(const T &info) const;

    void dfsVisit(Vertex<T> *v, vector<int> & res) const;

    // ALT Algorithm
    vector<Vertex<T>*> landmarks;
    vector<map< Vertex<T>* , double>> fromLandmark;
    vector<map< Vertex<T>* , double>> toLandmark;
    double getEstimateCost(Vertex<T>* src, Vertex<T>* dest);
public:
	vector<Vertex<T>*> getVertexSet() const;
	vector<POI<T>*> getPOIs() const;
	vector<int> getHighways() const;
    void setHighways(vector<int> ids);

    void addVertex(Vertex<T> *vertex);
    Vertex<T> * addVertex (const int & id, const T &info, const int &tag);
    Vertex<T> * findVertex (const int &id) const;

	Edge<T> * addEdge (const int &source, const int &dest, double w);

    void addPOI(POI<T>* poi);
    POI<T> * addPOI (const string &name, const int &id);
    POI<T> * findPOI (const string &name);
    POI<T> * findPOI (const int &id);

    double getMaxX() {return this->maxX;}
    double getMinX() {return this->minX;}
    double getMaxY() {return this->maxY;}
    double getMinY() {return this->minY;}

    void reverseEdges();

    vector<int> dfs(const int & source) const;
    vector<int> bfs(const int & source) const;

    Path dijkstraShortestPath(const int &origin, const int &destination);
    void dijkstraShortestPath(const T &origin);
    Path aStarShortestPath(const int id_src, const int id_dest, function <double (pair<double, double>, pair<double, double>)> h);
    Path nearestAStarLength(const int id_src, const vector<int> &POIs, function <double (pair<double, double>, pair<double, double>)> h);
    Path nearestAStarTime(const int id_src, const vector<Prisoner*> &Prisoners, function <double (pair<double, double>, pair<double, double>)> h);
    Path nearestATL(const int id_src, const vector<int> &POIs);
    Path nearestDijkstra(const int id_src, const vector<int> &POIs);
    Path nearestNeighbourSearchAStar(const int id_src, vector<int> &POIs, vector<Prisoner*> &Prisoners, Path &Path, function <double (pair<double, double>, pair<double, double>)> h, bool time);
    Path nearestNeighbourSearchALT(const int id_src, vector<int> &POIs, Path &path);
    Path nearestNeighbourDijkstra(const int id_src, vector<int> &POIs, Path &path);
    Path ALTShortestPath(int id_src, int id_dest);

    void preComputeLandmarks(vector<int> id_landmarks);
};

/* ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

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
vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return this->incoming;
}

template<class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template<class T>
double Vertex<T>::getCostTo(int dest_id) const {
    for (auto e : outgoing) {
        if (e->dest->getID() == dest_id) {
            return e->getWeight();
        }
    }
    return -1;
}

template<class T>
int Vertex<T>::getTag() const {
    return tag;
}

template<class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template<class T>
bool Vertex<T>::operator<(const Vertex &v2) const {
    return this->dist < v2.dist;
}

template<class T>
bool Vertex<T>::operator>(const Vertex &v2) const {
    return v2 < *this;
}

template<class T>
bool Vertex<T>::operator<=(const Vertex &v2) const {
    return !(v2 < *this);
}

template<class T>
bool Vertex<T>::operator>=(const Vertex &v2) const {
    return !(*this < v2);
}

template<class T>
void Vertex<T>::setTag(int tag) {
    this->tag = tag;
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
 * Class POI
 * ================================================================================================
 */

template<class T>
POI<T>::POI(string name, int id) {
    this->name=name;
    this->id=id;
}

template<class T>
string POI<T>::getName() const {
    return this->name;
}

template<class T>
int POI<T>::getID() const {
    return this->id;
}

template<class T>
string POI<T>::toString() const {
    return name + " (" + to_string(id) + ")";
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template<class T>
void Graph<T>::addVertex(Vertex<T>* vertex) {
    vertexSet.push_back(vertex);
}

template<class T>
Vertex<T> *Graph<T>::addVertex(const int &id, const T &info, const int &tag) {
    Vertex<T> *v = findVertex(id);
    if (v != nullptr)
        return v;
    v = new Vertex<T>(id);
    v->id=id;
    v->info=info;
    v->tag=tag;
    if (vertexSet.empty()) {
        this->minY = v->info.second;
        this->minX = v->info.first;
        this->maxX = v->info.first;
        this->maxY = v->info.second;
    }
    else {
        if(v->info.first > maxX) maxX = v->info.first;
        else if(v->info.first < minX) minX = v->info.first;
        if(v->info.second > maxY) maxY = v->info.second;
        else if (v->info.second < minY) minY = v->info.second;
    }
    vertexSet.push_back(v);
    vertexMap.insert(make_pair(id, vertexSet.size() - 1));
    return v;
}

template<class T>
Edge<T> * Graph<T>::addEdge(const int &source, const int &dest, double w) {
    auto s = findVertex(source);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;
    else
        return s->addEdge(d, w);
}

template<class T>
Vertex<T>* Graph<T>::findVertex(const int & id) const {
    auto i = vertexMap.find(id);
    if (i == vertexMap.end()) return nullptr;
    return vertexSet.at(i->second);
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


template<class T>
vector<POI<T>*> Graph<T>::getPOIs() const{
    return pois;
}


template<class T>
POI<T>* Graph<T>::addPOI(const string &name, const int &id) {
    POI<T>* p = findPOI(name);
    if (p != nullptr)
        return p;
    p = new POI<T>(name,id);
    pois.push_back(p);
    return p;
}

template<class T>
void Graph<T>::addPOI(POI<T>* poi) {
    pois.push_back(poi);
}

template<class T>
POI<T>* Graph<T>::findPOI(const string &name) {
    for(auto p: pois){
        if(p->getName() == name)
            return p;
    }
    return nullptr;
}

template<class T>
POI<T>* Graph<T>::findPOI(const int &id) {
    for(auto p: pois){
        if (p->getID() == id)
            return p;
    }
    return nullptr;
}


/* ================================================================================================
 * Algorithms
 * ================================================================================================
 */

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<int> Graph<T>::dfs(const int & source) const {
    // DONE (7 lines)
    vector<int> res;

    for(Vertex<T> *vertex:this->vertexSet){
        vertex->visited=false;
    }
    Vertex<T>*vertex1 = findVertex(source);
    dfsVisit(vertex1,res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<int> & res) const {
    // DONE (7 lines)
    if(!v->visited){
        v->visited=true;
        res.push_back(v->id); //inserts the vertex
    }

    for(Edge<T> * edge:v->outgoing){
        if(!edge->dest->visited){
            dfsVisit(edge->dest,res);
        }
    }
}


/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<int> Graph<T>::bfs(const int & source) const {
    // DONE (22 lines)
    // HINT: Use the flag "visited" to mark newly discovered vertices .
    // HINT: Use the "queue<>" class to temporarily store the vertices.
    vector<int> res; queue<Vertex<T>*> aux;
    for(Vertex<T> *vertex:vertexSet){vertex->visited=false;} //no visited
    Vertex<T> *vertex= findVertex(source);  //Find Source Vertex
    aux.push(vertex);                       //Put in queue
    vertex->visited=true;                   //Mark as visited

    while(!aux.empty()){
        vertex=aux.front();                 //Get Vertex
        aux.pop();                          //Pop from auxiliary queue
        res.push_back(vertex->id);        //Put into info vector
        for(Edge<T> * edges: vertex->outgoing){    //Search for Edges
            if(!edges->dest->visited){       //If not previously visited
                aux.push(edges->dest);       //Put into queue for posterior processing
                edges->dest->visited=true;   //Mark as visited
            }
        }
    }
    return res;
}

//Dijkstra

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {

    for(Vertex<T>* vertex: vertexSet){
        vertex->dist=INT_MAX;
        vertex->path=NULL;
    }
    Vertex<T> * og = findVertex(origin);
    og->dist=0;
    MutablePriorityQueue<Vertex<T>> dijkstratqueue;
    dijkstratqueue.insert(og);
    Vertex<T>* temp;
    while(!dijkstratqueue.empty()){
        temp=dijkstratqueue.extractMin();
        for(Edge<T>* edge: temp->outgoing){
            if(edge->dest->getDist()>temp->getDist()+edge->weight){
                edge->dest->dist=temp->getDist()+edge->weight;
                edge->dest->path=temp;
                if(!dijkstratqueue.found(edge->dest))
                    dijkstratqueue.insert(edge->dest);
                else
                    dijkstratqueue.decreaseKey(edge->dest);
            }
        }
    }
}

template<class T>
Path Graph<T>::dijkstraShortestPath(const int &origin, const int &destination) {

    for(Vertex<T>* vertex: vertexSet){
        vertex->dist=INT_MAX;
        vertex->path=NULL;
    }
    Vertex<T> * og = findVertex(origin), *dest=findVertex(destination);
    og->dist=0;
    MutablePriorityQueue<Vertex<T>> dijkstratqueue;
    dijkstratqueue.insert(og);
    Vertex<T>* temp;
    while(!dijkstratqueue.empty()){
        temp = dijkstratqueue.extractMin();
        for(Edge<T>* edge: temp->outgoing){
            if(edge->dest->dist > temp->dist + edge->weight){
                edge->dest->dist = temp->dist + edge->weight;
                edge->dest->path = temp;
                if(!dijkstratqueue.found(edge->dest))
                    dijkstratqueue.insert(edge->dest);
                else
                    dijkstratqueue.decreaseKey(edge->dest);
            }
        }
    }
    vector<int> path;
    path.push_back(dest->id);
    Vertex<T>* vertex = dest;
    double length=0;

    while (vertex->path != NULL) {
        length+= vertex->path->getCostTo(vertex->id);
        vertex = vertex->path;
        path.emplace(path.begin(), vertex->id);
    }

    //cout << "Size: " << path.size() << " Length: "<<length<<" Begin: "<<path.front()<<" End: "<<path.back()<<endl;

    return Path(length,path);
}

//A-Star

#define ROAD_VEL_MS 50 * 1000 / 3600

template<class T>
Path Graph<T>::aStarShortestPath(const int id_src, const int id_dest, function<double (pair<double, double>, pair<double, double>)> h) {
    for (Vertex<T> *vert: vertexSet) {
        vert->dist = INT_MAX;
        vert->actualDist = 0;
        vert->path = NULL;
        vert->queueIndex = 0;
    }

    Vertex<T> *src = findVertex(id_src), *dest = findVertex(id_dest), *v;
    src->dist = h(src->info, dest->info) / ROAD_VEL_MS;
    MutablePriorityQueue<Vertex<T>> Q;
    Q.insert(src);

    int iter = 0;

    while (!Q.empty()){
        iter++;
        v = Q.extractMin();

        if (v == dest){
            break;
        }

        for (Edge<T> *w : v->outgoing){
            double newDist = v->actualDist + w->weight;
            double f = newDist + (h(w->dest->info, dest->info) / ROAD_VEL_MS);
            if (w->dest->dist > f){
                double d = w->dest->dist;
                w->dest->dist = f;
                w->dest->actualDist = newDist;
                w->dest->path = v;
                if (d == INT_MAX){
                    Q.insert(w->dest);
                }
                else {
                    Q.decreaseKey(w->dest);
                }
            }
        }
    }

    //cout << iter << endl;

    //cout << "iter: " << iter << endl;

    vector<int> path;
    path.push_back(dest->id);
    Vertex<T>* vertex = dest;
    double length=0;

    while (vertex->path != NULL) {
        length+= vertex->path->getCostTo(vertex->id);
        vertex = vertex->path;
        path.emplace(path.begin(), vertex->id);
    }

    //cout << "Size: " << path.size() << " Length: "<<length<<" Begin: "<<path.front()<<" End: "<<path.back()<<endl;

    return Path(length,path);
}

//Nearest Neighbour Search
template<class T>
Path Graph<T>::nearestAStarLength(const int id_src, const vector<int> &POIs, function <double (pair<double, double>, pair<double, double>)> h) {
    Path path = Path(INT_MAX,vector<int>());

    for(auto i: POIs){
        //cout<<"POI: "<<i<<endl;
        Path newPath = aStarShortestPath(id_src,i,h);
        if(newPath.getLength()<path.getLength()) {
            path = newPath;
            //cout<<"Nearest POI is: "<<i<<endl;
        }
    }
    return path;
}

template<class T>
Path Graph<T>::nearestAStarTime(const int id_src, const vector<Prisoner*> &Prisoners, function<double(pair<double, double>, pair<double, double>)> h) {
    Path path;
    //cout<<"Destiny: "<<Prisoners.at(0)->getDest()<<endl;
    path = aStarShortestPath(id_src,Prisoners.at(0)->getDest(),h);

    return path;
}


template<class T>
Path Graph<T>::nearestATL(const int id_src, const vector<int> &POIs) {
    Path path = Path(INT_MAX,vector<int>());

    for(auto i: POIs){
        //cout<<"POI: "<<i<<endl;
        Path newPath = ALTShortestPath(id_src,i);
        if(newPath.getLength()<path.getLength()) {
            path = newPath;
            //cout<<"Nearest POI is: "<<i<<endl;
        }
    }
    return path;
}

template<class T>
Path Graph<T>::nearestDijkstra(const int id_src, const vector<int> &POIs) {
    Path path = Path(INT_MAX,vector<int>());

    for(auto i: POIs){
        //cout<<"POI: "<<i<<endl;
        Path newPath = dijkstraShortestPath(id_src,i);
        if(newPath.getLength()<path.getLength()) {
            path = newPath;
            //cout<<"Nearest POI is: "<<i<<endl;
        }
    }
    return path;
}

template<class T>
Path Graph<T>::nearestNeighbourSearchAStar(const int id_src, vector<int> &POIs, vector<Prisoner*> &Prisoners, Path &path, function<double(pair<double, double>, pair<double, double>)> h, bool time) {
    //cout<<"POI's left: "<<POIs.size()<<endl;
    //cout<<"Prisoners' left: "<<Prisoners.size()<<endl;
    if(path.getPath().empty()){
        path.addNode(id_src);
    }
    if(POIs.empty()||Prisoners.empty()){
        return path;
    }
    Path next;
    if(!time)
        next = nearestAStarLength(id_src, POIs, h);
    else
        next = nearestAStarTime(id_src, Prisoners, h);

    path.joinPath(next);
    path.addPOI(path.getLastNode(), Time(path.getLength()));
    POIs.erase(find(POIs.begin(),POIs.end(),path.getLastNode()));
    Prisoners.erase(Prisoners.begin());

    return nearestNeighbourSearchAStar(path.getLastNode(), POIs, Prisoners, path, h,time);
}

template <class T>
Path Graph<T>::nearestNeighbourSearchALT(const int id_src, vector<int> &POIs, Path &path) {
    //cout<<"POI's left: "<<POIs.size()<<endl;
    if(path.getPath().empty()){
        path.addNode(id_src);
    }
    if(POIs.empty()){
        return path;
    }
    Path next= nearestATL(id_src, POIs);
    path.joinPath(next);
    POIs.erase(find(POIs.begin(),POIs.end(),path.getLastNode()));

    return nearestNeighbourSearchALT(path.getLastNode(), POIs, path);
}

template<class T>
Path Graph<T>::nearestNeighbourDijkstra(const int id_src, vector<int> &POIs, Path &path) {
    //cout<<"POI's left: "<<POIs.size()<<endl;
    if(path.getPath().empty()){
        path.addNode(id_src);
    }
    if(POIs.empty()){
        return path;
    }
    Path next= nearestDijkstra(id_src, POIs);
    path.joinPath(next);
    POIs.erase(find(POIs.begin(),POIs.end(),path.getLastNode()));

    return nearestNeighbourDijkstra(path.getLastNode(), POIs, path);
}

template<class T>
Path Graph<T>::ALTShortestPath(int id_src, int id_dest) {
    for (Vertex<T> *vert: vertexSet) {
        vert->dist = INT_MAX;
        vert->actualDist = 0;
        vert->path = NULL;
        vert->queueIndex = 0;
    }

    Vertex<T> *src = findVertex(id_src), *dest = findVertex(id_dest), *v;
    src->dist = getEstimateCost(src, dest);
    MutablePriorityQueue<Vertex<T>> Q;
    Q.insert(src);

    int iter = 0;

    while (!Q.empty()){
        iter++;
        v = Q.extractMin();

        if (v == dest){
            break;
        }

        for (Edge<T> *w : v->outgoing){
            double newDist = v->dist + w->weight;
            double f = newDist + getEstimateCost(w->dest, dest);
            if (w->dest->dist > f){
                double d = w->dest->dist;
                w->dest->dist = f;
                w->dest->actualDist = newDist;
                w->dest->path = v;
                if (d == INT_MAX){
                    Q.insert(w->dest);
                }
                else {
                    Q.decreaseKey(w->dest);
                }
            }
        }
    }

    vector<int> path;
    path.push_back(dest->id);
    Vertex<T>* vertex = dest;
    double length=0;

    while (vertex->path != NULL) {
        length+= vertex->path->getCostTo(vertex->id);
        vertex = vertex->path;
        path.emplace(path.begin(), vertex->id);
    }

    //cout << "Size: " << path.size() << " Length: "<<length<<" Begin: "<<path.front()<<" End: "<<path.back()<<endl;

    return Path(length,path);
}

template<class T>
double Graph<T>::getEstimateCost(Vertex<T>* src, Vertex<T>* dest) {
    double maxEstimate = 0;

    // Source equals Destiny
    if (src == dest)
        return maxEstimate;

    for (int i = 0; i < landmarks.size(); i++) {
        // Source is Landmark
        if (landmarks[i] == src)
            return fromLandmark.at(i).at(dest);

        // Destiny is Landmark
        if (landmarks[i] == dest)
            return toLandmark.at(i).at(src);
    }

    for (int i = 0; i < landmarks.size(); i++) {
        map<Vertex<T>*,double> from = fromLandmark.at(i);
        map<Vertex<T>*,double> to = toLandmark.at(i);
        double estimate = max(to.at(src) - to.at(dest), from.at(dest) - from.at(src));
        if (estimate != INT_MAX)
            maxEstimate = max(maxEstimate, estimate);
    }

    return maxEstimate;
}

template<class T>
void Graph<T>::preComputeLandmarks(vector<int> id_landmarks) {
    fromLandmark.clear();
    toLandmark.clear();
    landmarks.clear();

    Vertex<T>* v;
    for (int id : id_landmarks) {
        v = findVertex(id);
        landmarks.push_back(v);

        // From Landmark Distances
        this->dijkstraShortestPath(v->getInfo());
        map<Vertex<T>*,double> fromLandmarkDistances;
        for (Vertex<T> * ver : vertexSet) {
            fromLandmarkDistances.insert(make_pair(ver, ver->dist));
        }
        fromLandmark.push_back(fromLandmarkDistances);

        // To Landmark Distances
        reverseEdges();
        this->dijkstraShortestPath(v->getInfo());
        map<Vertex<T>*,double> toLandmarkDistances;
        for (Vertex<T> * ver : vertexSet) {
            toLandmarkDistances.insert(make_pair(ver, ver->dist));
        }
        toLandmark.push_back(toLandmarkDistances);
        reverseEdges();
    }
}

template<class T>
void Graph<T>::reverseEdges() {
    Vertex<T> * temp;
    for (Vertex<T>* v : vertexSet) {
        for (Edge<T> * e : v->outgoing) {
            temp = e->dest;
            e->dest = e->orig;
            e->orig = temp;
        }
        for (Edge<T> * e : v->incoming) {
            temp = e->dest;
            e->dest = e->orig;
            e->orig = temp;
        }
    }
}

template<class T>
vector<int> Graph<T>::getHighways() const {
    return highways;
}

template<class T>
void Graph<T>::setHighways(vector<int> ids) {
    highways = ids;
}




#endif /* GRAPH_H_ */
