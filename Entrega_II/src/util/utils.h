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

int readInt(string msg);
string readString(string msg);

double euclidianDistance(pair<double, double> point1, pair<double, double> point2);
void compareALTandAStar(Graph<coord> graph, const int id_src, vector<int> &POIs, Path &path);
void compareALTandDijkstra(Graph<coord> graph, const int id_src, vector<int> &POIs, Path &path);
void compareAStarandDijkstra(Graph<coord> graph, const int id_src, vector<int> &POIs, Path &path);

#endif //ENTREGA_II_UTILS_H
