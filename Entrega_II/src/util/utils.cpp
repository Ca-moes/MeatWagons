//
// Created by pedro on 05/05/2020.
//

#include "utils.h"

int chooseMenuOption(int maxOption) {
    int op;

    do {
        op = readInt("Choose an option: ");
        if (op > maxOption || op < 0)
            cout << "Invalid Input. Invalid option." << endl;
    } while(op > maxOption || op < 0);

    return op;
}

int readInt(string msg) {
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

        if (!error && line == "") {
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

string readString(string msg) {
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


double euclidianDistance(pair<double, double> point1, pair<double, double> point2) {
    return sqrt(pow((point1.first - point2.first), 2) + pow((point1.second - point2.second), 2));
}

void compareALTandAStar(Graph<coord> graph, const int id_src, vector<int> &POIs, Path &path) {
    auto t1 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchALT(id_src, id_src, POIs, path);
    auto t2 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchAStar(id_src, id_src, POIs, path, euclidianDistance);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationALT = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
    auto durationAStar = std::chrono::duration_cast<std::chrono::nanoseconds>( t3 - t2 ).count();

    cout << "Ran ALT Search in " << durationALT << " nanoseconds" << endl;
    cout << "Ran A-Star Search in " << durationAStar << " nanoseconds" << endl;
}

void compareALTandDijkstra(Graph<coord> graph, const int id_src, vector<int> &POIs, Path &path) {
    auto t1 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchALT(id_src, id_src, POIs, path);
    auto t2 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourDijkstra(id_src, id_src, POIs, path);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationALT = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::nanoseconds>( t3 - t2 ).count();

    cout << "Ran ALT Search in " << durationALT << " nanoseconds" << endl;
    cout << "Ran Dijkstra Search in " << durationDijkstra << " nanoseconds" << endl;
}

void compareAStarandDijkstra(Graph<coord> graph, const int id_src, vector<int> &POIs, Path &path) {
    auto t1 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourSearchAStar(id_src, id_src, POIs, path, euclidianDistance);
    auto t2 = chrono::high_resolution_clock::now();
    graph.nearestNeighbourDijkstra(id_src, id_src, POIs, path);
    auto t3 = chrono::high_resolution_clock::now();

    auto durationAStar = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::nanoseconds>( t3 - t2 ).count();

    cout << "Ran AStar Search in " << durationAStar << " nanoseconds" << endl;
    cout << "Ran Dijkstra Search in " << durationDijkstra << " nanoseconds" << endl;
}
