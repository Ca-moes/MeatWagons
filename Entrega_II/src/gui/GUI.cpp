//
// Created by GoncaloAlves on 06/05/2020.
//

#include "GUI.h"


GUI::GUI(Graph<coord> &graph, int w, int h) : graph(graph), gv_w(w), gv_h(h) {
    this->gv = new GraphViewer(w, h, false);
}

void GUI::setGraph(Graph<coord> &graph) { this->graph = graph; }

void GUI::show() {
    gv->createWindow(gv_w, gv_h);
    int id = 0;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        gv->addNode(id, vertex->getInfo().first, vertex->getInfo().second);
        gv->setVertexLabel(id, to_string(vertex->getID()));
        id++;
    }
    id = 0;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        for (Edge<coord>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getID(), edge->getDest()->getID(), EdgeType::DIRECTED);
            //gv->setEdgeLabel(id, to_string(edge->getWeight()));
            id++;
        }
    }
}