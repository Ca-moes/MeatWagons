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
#include "utils.h"
using namespace std;
void parseMap(Graph<coord> &graph, const string &location);
void parseTag(Graph<coord> &graph,const string &tag_file);
#endif //ENTREGA_II_PARSER_H
