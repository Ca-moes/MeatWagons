//
// Created by pedro on 05/05/2020.
//

#include "utils.h"

/**
 * Retorna um numero i : 0 <= i <= maxOption
 * @param maxOption
 * @return Número que leu em forma de _int_
 */
int chooseMenuOption(int maxOption) {
    int op;

    do {
        op = readInt("Choose an option: ");
        if (op > maxOption || op < 0)
            cout << "Invalid Input. Invalid option." << endl;
    } while(op > maxOption || op < 0);

    return op;
}

int readInt(const string& msg) {
    string line;
    int num = 0;
    bool error;

    do
    {
        cout << msg;
        getline(cin, line);

        error = any_of(line.begin(), line.end(), ::isalpha); //Ver se tem alguma letra

        if (error)
            cout << "Invalid Input. Can not have letters." << endl;

        if (!error && line.empty()) {
            error = true;
            cout << "Empty Input. " << endl;
        }

        if (!error) {
            for (auto x : line) {
                if (isspace(x)) {
                    error = true;
                    break;
                }
            }
            if (error)
                cout << "Invalid Input. Can not have spaces." << endl;
        }

        if (!error) {
            try {
                num = stoi(line);
            }
            catch (invalid_argument&) { //Ver se tem caracter especial
                error = true;
                cout << "Invalid Input. Can not have special characters." << endl;
            }
            catch (out_of_range&) { //Ver se o numero e demasiado grande
                error = true;
                cout << "Invalid Input. Number is to big." << endl;
            }
        }

        if (!error && line.size() != to_string(stoi(line)).size()) {
            for (auto x : line) {
                if (ispunct(x)) {
                    error = true;
                    break;
                }
            }
            if (error)
                cout << "Invalid Input. Can not have special characters." << endl;
        }

    } while (error);

    num = stoi(line);
    return num;
}

string readString(const string& msg) {
    string line;
    bool error;
    size_t t;
    do
    {
        error = false;
        cout << msg;
        getline(cin, line);

        t = line.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -\n"); //Ver se tem algum caracter inválido
        if(t!=line.npos) error=true;
        if (error)
            cout << "Invalid Input. Can not have invalid characters." << endl;

        if (!error && line.empty()) {
            error = true;
            cout << "Empty Input. " << endl;
        }

    } while (error);

    return line;
}

bool allVehiclesFull(vector<Vehicle*>& vehicles){
    //TODO
    for (int i = 0; i < vehicles.size(); ++i) {
        if (!vehicles[i]->isAtMaxCapacity())
            return false;
    }
    return true;
}

double euclidianDistance(pair<double, double> point1, pair<double, double> point2) {
    return sqrt(pow((point1.first - point2.first), 2) + pow((point1.second - point2.second), 2));
}

void compareALTandAStar(Graph<coord> graph, const int id_src, const vector<int>& POIs,const vector<Prisoner*>& Prisoners) {
    Path path1, path2;
    vector<int> p1 = POIs, p2 = POIs;
    vector<Prisoner*>pr=Prisoners;
    auto t1 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchALT(id_src, p1, path1);
    auto t2 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchAStar(id_src, p2,pr, path2, euclidianDistance,false);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationALT = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

    cout << "Ran ALT Search in " << durationALT << " microseconds" << endl;
    cout << "Ran A-Star Search in " << durationAStar << " microseconds" << endl;
}

void compareALTandDijkstra(Graph<coord> graph, const int id_src, const vector<int>& POIs) {
    Path path1, path2;
    vector<int> p1 = POIs, p2 = POIs;
    auto t1 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchALT(id_src, p1, path1);
    auto t2 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourDijkstra(id_src, p2, path2);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationALT = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

    cout << "Ran ALT Search in " << durationALT << " microseconds" << endl;
    cout << "Ran Dijkstra Search in " << durationDijkstra << " microseconds" << endl;
}

void compareAStarandDijkstra(Graph<coord> graph, const int id_src, const vector<int>& POIs,const vector<Prisoner*>& Prisoners) {
    Path path1, path2;
    vector<int> p1 = POIs, p2 = POIs;
    vector<Prisoner*>pr=Prisoners;
    auto t1 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchAStar(id_src, p1, pr,path1, euclidianDistance,false);
    auto t2 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourDijkstra(id_src, p2, path2);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

    cout << "Ran AStar Search in " << durationAStar << " microseconds" << endl;
    cout << "Ran Dijkstra Search in " << durationDijkstra << " microseconds" << endl;
}

void compareDFSandBFS(Graph<coord> graph, const int id_src) {
    Path path1, path2;
    auto t1 = chrono::high_resolution_clock::now();
    graph.dfs(id_src);
    auto t2 = chrono::high_resolution_clock::now();
    graph.bfs(id_src);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationDFS = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto durationBFS = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();

    cout << "Ran DFS in " << durationDFS << " microseconds" << endl;
    cout << "Ran BFS in " << durationBFS << " microseconds" << endl;
}

void constructGraphByPath(const Graph<coord>& graph, Graph<coord>& newgraph, vector<int> path){

    Vertex<coord> * v1, *v2;
    for (int i = 0; i < path.size() - 1; i++) {
        v1 = graph.findVertex(path[i]);
        v2 = graph.findVertex(path[i+1]);
        newgraph.addVertex(v1->getID(),v1->getInfo(),v1->getTag());
        for(Edge<coord> * e : v1->getAdj()) {
            if (e->getDest() == v2) {
                newgraph.addVertex(v2->getID(),v2->getInfo(),v2->getTag());
                newgraph.addEdge(v1->getID(), v2->getID(), e->getWeight());
                break;
            }
        }
    }

    for(auto poi: graph.getPOIs()){
        newgraph.addPOI(poi);
    }
}


void sortPrisonersByDeliveryTime(vector<Prisoner*> &prisoners) {
    sort(prisoners.begin(), prisoners.end(), [](const Prisoner* left, const Prisoner* right) {
        return left->getDeliveryTime() < right->getDeliveryTime();
    });
}

void printPOIsTimeMap(const unordered_map<int, Time> &pois) {
    for (auto p : pois) {
        cout << "ID: " << p.first << " | Time to get there: " << p.second.toString(true) << endl;
    }
}

Time getDepartureTime(const unordered_map<int, Time> &POIsTimes, const vector<Prisoner*> &prisoners) {
    cout << "Prisoner: " << prisoners[0]->getName() << " -> Node " << prisoners[0]->getDest() << " ( Time to get there: " <<  POIsTimes.at(prisoners[0]->getDest()).toString(true) << ")" << endl;
    Time departureTime(prisoners[0]->getDeliveryTime() - POIsTimes.at(prisoners[0]->getDest()));
    Time temp;

    for (int i = 1; i < prisoners.size(); i++) {
        cout << "Prisoner: " << prisoners[i]->getName() << " -> Node " << prisoners[i]->getDest() << " ( Time to get there: " <<  POIsTimes.at(prisoners[i]->getDest()).toString(true) << ")" << endl;
        temp = departureTime + POIsTimes.at(prisoners[i]->getDest());
        if (temp < prisoners[i]->getDeliveryTime())
            continue;
        else
            departureTime = departureTime - (temp - prisoners[i]->getDeliveryTime());
    }

    return departureTime;
}
