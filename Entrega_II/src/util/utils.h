//
// Created by pedro on 05/05/2020.
//

#ifndef ENTREGA_II_UTILS_H
#define ENTREGA_II_UTILS_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "prison/Vehicle.h"
#include "graph/Graph.h"
#include <fstream>

using namespace std;

int chooseMenuOption(int maxOption);

int readInt(const string& msg);
string readString(const string& msg);

bool allVehiclesFull(vector<Vehicle*>& vehicles);
double euclidianDistance(pair<double, double> point1, pair<double, double> point2);
void compareALTandAStar(Graph<coord> graph, int id_src, const vector<int>& POIs,const vector<Prisoner*>& Prisoners);
void compareALTandDijkstra(Graph<coord> graph, int id_src, const vector<int>& POIs);
void compareAStarandDijkstra(Graph<coord> graph, const vector<int> POIs);
void compareDFSandBFS(const vector<Graph<coord>> graphs);

void constructGraphByPath(const Graph<coord>& graph, Graph<coord>& newgraph, vector<int> path);

void sortPrisonersByDeliveryTime(vector<Prisoner*> &prisoners);

void printPOIsTimeMap(const unordered_map<int, Time> &pois);

Time getDepartureTime(const unordered_map<int, Time> &POIsTimes, const vector<Prisoner*> &prisoners);

#endif //ENTREGA_II_UTILS_H
