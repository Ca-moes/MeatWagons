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
    Graph<coord> getGraph()
    ;
    void show();
    void showNodes(vector<int> ids);
    void showPath(vector<int> path);
    void showPath2(vector<vector<int>> paths);
    void showPathInMap(Path shortestPath);
    void showMultiplePathsInMap(vector<Path> shortestPath);
    void clearPath(vector<int> path);
    void clearGraph();

    void clearPaths(vector<vector<int>> vector);

    void createGV();
    void closeGV();
    void deleteGV();
    void clearEdges(int numEdges);
    void clearAllGraphNodes();
};


#endif //ENTREGA_II_GUI_H
