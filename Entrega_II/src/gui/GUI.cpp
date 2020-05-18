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
    gv->defineVertexColor("GRAY");
    gv->defineEdgeCurved(false);
    double yPercent, xPercent;

    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        yPercent = 1.0 - ((vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getID(), (int)(xPercent*gv_w), (int)(yPercent*gv_h));
        if(vertex->getTag()==1){
            gv->setVertexLabel(vertex->getID(), graph.findPOI(vertex->getID())->getName());
            gv->setVertexSize(vertex->getID(), 15);
            gv->setVertexColor(vertex->getID(),"RED");
        }
        else{
            gv->setVertexLabel(vertex->getID(),to_string(vertex->getID()));
            gv->setVertexSize(vertex->getID(), 5);
        }

    }

    int id = 0;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        for (Edge<coord>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getID(), edge->getDest()->getID(), EdgeType::DIRECTED);
            //gv->setEdgeLabel(id, to_string(edge->getWeight()));
            if (vertex->getTag() == 2 && edge->getDest()->getTag() == 2) {
                gv->setEdgeColor(id, "BLUE");
                gv->setEdgeThickness(id, 5);
            }
            id++;
        }
    }

    gv->rearrange();

    cout << "Press Enter to exit graph viewer." << endl;
    int character = getchar();
    if (character == '\n')	// enter key is pressed
        gv->closeWindow();
    else
        cin.ignore(1000, '\n');
}

void GUI::showPath(vector<int> path) {
    if (path.size() == 1) path.push_back(path[0]);

    gv->defineVertexColor("GRAY");
    gv->defineVertexSize(5);
    gv->defineEdgeCurved(false);
    gv->createWindow(gv_w, gv_h);

    double yPercent, xPercent;

    for (int i = 0; i < path.size() - 1; i++) {
        Vertex<coord>* a = graph.findVertex(path.at(i));
        Vertex<coord>* b = graph.findVertex(path.at(i+1));

        cout<<"A: "<<a->getID()<<" B: "<<b->getID()<<endl;

        yPercent = 1.0 - ((a->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
        xPercent = (a->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
        if(a->getTag()==1){
            gv->setVertexLabel(i, graph.findPOI(a->getID())->getName());
            gv->setVertexColor(i,"RED");
            gv->setVertexSize(i, 15);
        }
        gv->addNode(i, (int)(xPercent*gv_w), (int)(yPercent*gv_h));

        //gv->setVertexLabel(i, to_string(a->getID()));

        yPercent = 1.0 - ((b->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
        xPercent = (b->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
        if(b->getTag()>0){
            gv->setVertexLabel(i+1, graph.findPOI(b->getID())->getName());
            gv->setVertexColor(i+1,"RED");
            gv->setVertexSize(i+1, 15);

        }
        gv->addNode(i + 1, (int)(xPercent*gv_w), (int)(yPercent*gv_h));
        //gv->setVertexLabel(i+1, to_string(b->getID()));

        gv->addEdge(i, i, i+1, EdgeType::DIRECTED);
        //gv->setEdgeLabel(i, to_string(a->getCostTo(b->getID())));

    }

    gv->setVertexColor(0, "RED");
    gv->setVertexSize(0, 15);
    gv->setVertexColor(path.size() - 1, "RED");
    gv->setVertexSize(path.size() - 1, 15);

    gv->rearrange();

    cout << "Press Enter to exit graph viewer." << endl;
    int character = getchar();
    if (character == '\n') // enter key is pressed
        clearPath(path);
    else
        cin.ignore(1000, '\n');
}

void GUI::showPathInMap(vector<int> path) {
    gv->createWindow(gv_w, gv_h);
    gv->defineVertexColor("GRAY");
    gv->defineEdgeCurved(false);
    double yPercent, xPercent;

    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        yPercent = 1.0 - ((vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getID(), (int)(xPercent*gv_w), (int)(yPercent*gv_h));
        if (vertex->getTag()==1) {
            gv->setVertexLabel(vertex->getID(), graph.findPOI(vertex->getID())->getName());
            gv->setVertexSize(vertex->getID(), 15);
            gv->setVertexColor(vertex->getID(),"RED");
            for (int id : path)
                if (vertex->getID() == graph.findVertex(id)->getID())
                    gv->setVertexColor(vertex->getID(),"YELLOW");

            if (vertex->getID() == graph.findVertex(path[0])->getID())
                gv->setVertexColor(vertex->getID(),"GREEN");
        }
        else{
            gv->setVertexLabel(vertex->getID(),to_string(vertex->getID()));
            gv->setVertexSize(vertex->getID(), 5);
        }
    }

    int id = 0;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        for (Edge<coord>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getID(), edge->getDest()->getID(), EdgeType::UNDIRECTED);
            gv->setEdgeThickness(id, 0.5);
            id++;
        }
    }

    if (path.size() == 1) path.push_back(path[0]);

    for (int i = 0; i < path.size() - 1; i++) {
        gv->addEdge(id, graph.findVertex(path[i])->getID(), graph.findVertex(path[i+1])->getID(), EdgeType::DIRECTED);
        gv->setEdgeColor(id, "ORANGE");
        gv->setEdgeThickness(id, 10);
        id++;
    }

    gv->rearrange();

    cout << "Press Enter to exit graph viewer." << endl;
    int character = getchar();
    if (character == '\n') { // enter key is pressed
        clearGraph();
    }
    else
        cin.ignore(1000, '\n');
}

void GUI::clearPath(vector<int> path) {
    for(int i=0;i<path.size();i++){
        gv->removeEdge(i);
        gv->removeNode(i);
    }
    gv->closeWindow();
}

void GUI::clearGraph() {
    int id =0;
    for(auto v: graph.getVertexSet()){
        for (auto e : v->getAdj()) {
            gv->removeEdge(id);
            id++;
        }
    }
    id=0;
    for(auto v: graph.getVertexSet()){
        gv->removeNode(id);
        id++;
    }
    gv->closeWindow();
}
