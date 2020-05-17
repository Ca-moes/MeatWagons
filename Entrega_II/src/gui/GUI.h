//
// Created by GoncaloAlves on 06/05/2020.
//

#ifndef ENTREGA_II_GUI_H
#define ENTREGA_II_GUI_H

#include "../graphviewer/graphviewer.h"
#include "graph/Graph.h"
using namespace std;

class GUI{
private:
    Graph<coord> graph;
    GraphViewer * gv;
    int gv_w;
    int gv_h;
public:
    GUI(Graph<coord> &graph,int w,int h);
    void setGraph(Graph<coord> &graph);
    void show();
    void showPath(vector<int> path);
    void showPathInMap(vector<int> path);
    void clearPath(vector<int> path);
};
#endif //ENTREGA_II_GUI_H
