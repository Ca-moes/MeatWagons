//
// Created by GoncaloAlves on 06/05/2020.
//

#ifndef ENTREGA_II_PARSER_H
#define ENTREGA_II_PARSER_H

#include <string>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include "graph/Graph.h"
using namespace std;
Graph<coord> parseMap(const string &node_file, const string &edge_file);

#endif //ENTREGA_II_PARSER_H
