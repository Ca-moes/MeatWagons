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
#include "graph/Graph.h"

using namespace std;

int chooseMenuOption(int maxOption);

int readInt(const string& msg);
string readString(const string& msg);

double euclidianDistance(pair<double, double> point1, pair<double, double> point2);
void compareALTandAStar(Graph<coord> graph, int id_src, const vector<int>& POIs);
void compareALTandDijkstra(Graph<coord> graph, int id_src, const vector<int>& POIs);
void compareAStarandDijkstra(Graph<coord> graph, int id_src, const vector<int>& POIs);
void compareDFSandBFS(Graph<coord> graph, const int id_src);

void constructGraphByPath(const Graph<coord>& graph, Graph<coord>& newgraph, vector<int> path);

#endif //ENTREGA_II_UTILS_H
