//
// Created by GoncaloAlves on 06/05/2020.
//

#include "GUI.h"


GUI::GUI(Graph<coord> &graph, int w, int h) : graph(graph), gv_w(w), gv_h(h) {
}

void GUI::setGraph(Graph<coord> &graph) { this->graph = graph; }

Graph<coord> GUI::getGraph() {
    return this->graph;
}

void GUI::show() {
    createGV();
    double yPercent, xPercent;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        yPercent = (vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05;
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
        gv->addNode(vertex->getID(), (int)(xPercent*gv_w), (int)(yPercent*gv_h));
        if(vertex->getTag()==1){
            gv->setVertexLabel(vertex->getID(), graph.findPOI(vertex->getID())->getName());
            gv->setVertexSize(vertex->getID(), 15);
            gv->setVertexColor(vertex->getID(),"RED");
        }
        else{
            gv->setVertexLabel(vertex->getID(),""/*to_string(vertex->getID())*/);
            gv->setVertexSize(vertex->getID(), 5);
        }

    }

    int id = 0;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        for (Edge<coord>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getID(), edge->getDest()->getID(), EdgeType::DIRECTED);
            gv->setEdgeLabel(id, ""/*to_string(edge->getWeight())*/);
            if (vertex->getTag() == 2 && edge->getDest()->getTag() == 2) {
                gv->setEdgeColor(id, "BLUE");
                gv->setEdgeThickness(id, 5);
            }
            id++;
        }
    }

    gv->rearrange();
    closeGV();
}


void GUI::showNodes(vector<int> ids) {
    createGV();
    double yPercent, xPercent;

    for (int id : ids) {
        Vertex<coord>* vertex = graph.findVertex(id);
        yPercent = (vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05;
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
        gv->addNode(vertex->getID(), (int)(xPercent*gv_w), (int)(yPercent*gv_h));
        if(vertex->getTag()==1){
            gv->setVertexLabel(vertex->getID(), graph.findPOI(vertex->getID())->getName());
            gv->setVertexSize(vertex->getID(), 15);
            gv->setVertexColor(vertex->getID(),"RED");
        }
        else{
            gv->setVertexLabel(vertex->getID(),""/*to_string(vertex->getID())*/);
            gv->setVertexSize(vertex->getID(), 5);
        }

    }

    int edgeId = 0;
    for (int id : ids) {
        Vertex<coord>* vertex = graph.findVertex(id);
        for (Edge<coord>* edge : vertex->getAdj()) {
            if (find(ids.begin(), ids.end(), edge->getDest()->getID()) != ids.end()) {
                gv->addEdge(edgeId, vertex->getID(), edge->getDest()->getID(), EdgeType::DIRECTED);
                gv->setEdgeLabel(edgeId, ""/*to_string(edge->getWeight())*/);
                if (vertex->getTag() == 2 && edge->getDest()->getTag() == 2) {
                    gv->setEdgeColor(edgeId, "BLUE");
                    gv->setEdgeThickness(edgeId, 5);
                }
                edgeId++;
            }
        }
    }

    gv->rearrange();

    closeGV();
}

void GUI::showPath(vector<int> path) {
    if (path.size() == 1) path.push_back(path[0]);

    createGV();

    double yPercent, xPercent;

    for (int i = 0; i < path.size() - 1; i++) {
        Vertex<coord>* a = graph.findVertex(path.at(i));
        Vertex<coord>* b = graph.findVertex(path.at(i+1));

        //cout<<"A: "<<a->getID()<<" B: "<<b->getID()<<endl;

        yPercent = (a->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05;
        xPercent = (a->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
        if(a->getTag()==1){
            gv->setVertexLabel(i, graph.findPOI(a->getID())->getName());
            gv->setVertexColor(i,"RED");
            gv->setVertexSize(i, 15);
        }
        gv->addNode(i, (int)(xPercent*gv_w), (int)(yPercent*gv_h));

        gv->setVertexLabel(i, to_string(a->getID()));

        yPercent = (b->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05;
        xPercent = (b->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
        if(b->getTag()==1){
            gv->setVertexLabel(i+1, graph.findPOI(b->getID())->getName());
            gv->setVertexColor(i+1,"RED");
            gv->setVertexSize(i+1, 15);

        }
        gv->addNode(i + 1, (int)(xPercent*gv_w), (int)(yPercent*gv_h));

        gv->setVertexLabel(i+1, to_string(b->getID()));

        gv->addEdge(i, i, i+1, EdgeType::DIRECTED);
    }

    gv->setVertexColor(0, "RED");
    gv->setVertexSize(0, 15);
    gv->setVertexColor(path.size() - 1, "RED");
    gv->setVertexSize(path.size() - 1, 15);

    gv->rearrange();

    closeGV();
}

/*void GUI::showPath2(vector<vector<int>> paths) {
    double yPercent, xPercent;
    string color;

    for (int j = 0; j < paths.size(); ++j) {
        // Caso nó de destino e fim seja o mesmo
        if (paths.size() == 1) paths.push_back(paths[0]);

        int idverj = j + 1;
        gv->createWindow(gv_w, gv_h);

        // Para cada nó do path
        for (int i = 0; i < paths[j].size() - 1; i++) {
            gv->defineVertexColor("GRAY");
            gv->defineVertexSize(5);
            gv->defineEdgeCurved(false);

            Vertex<coord>* a = graph.findVertex(paths[j].at(i));
            Vertex<coord>* b = graph.findVertex(paths[j].at(i+1));

            int idveri = i + 1; // para nodes ficarem com id's diferentes entre paths e não serem todos 0 na primeira iteração
            cout<<"A: "<<a->getID()<<" B: "<<b->getID()<<endl;

            yPercent = 1.0 - ((a->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
            xPercent = (a->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
            if(a->getTag()==1){
                gv->setVertexLabel(idveri*idverj, graph.findPOI(a->getID())->getName());
                gv->setVertexColor(idveri*idverj,"RED");
                gv->setVertexSize(idveri*idverj, 15);
            }
            gv->addNode(idveri*idverj, (int)(xPercent*gv_w), (int)(yPercent*gv_h));

            yPercent = 1.0 - ((b->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
            xPercent = (b->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;
            if(b->getTag()==1){
                gv->setVertexLabel(idveri*idverj+1, graph.findPOI(b->getID())->getName());
                gv->setVertexColor(idveri*idverj+1,"RED");
                gv->setVertexSize(idveri*idverj+1, 15);

            }
            gv->addNode(idveri*idverj + 1, (int)(xPercent*gv_w), (int)(yPercent*gv_h));

            gv->addEdge(idveri*idverj, idveri*idverj, idveri*idverj+1, EdgeType::DIRECTED);
            if (idverj == 1) gv->setEdgeColor(i, "BLUE");
            else if (idverj == 2) gv->setEdgeColor(i, "RED");
            else if (idverj == 3) gv->setEdgeColor(i, "PINK");

        }

        gv->setVertexColor(idverj, "GREEN");
        gv->setVertexSize(idverj, 15);
        gv->setVertexColor(paths[j].size() * idverj, "RED");
        gv->setVertexSize(paths[j].size() * idverj, 15);
    }

    gv->rearrange();

    cout << "Press Enter to exit graph viewer." << endl;
    int character = getchar();
    if (character == '\n') // enter key is pressed
        clearPaths(paths);
    else
        cin.ignore(1000, '\n');
}*/

void GUI::showPathInMap(Path shortestPath) {
    createGV();
    double yPercent, xPercent;
    vector<int> path = shortestPath.getPath();

    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        yPercent = (vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05;
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getID(), (int)(xPercent*gv_w), (int)(yPercent*gv_h));

        //gv->setVertexLabel(vertex->getID(),to_string(vertex->getID()));
        gv->setVertexSize(vertex->getID(), 5);
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
    gv->setVertexLabel(path[0], graph.findPOI(path[0])->getName());
    gv->setVertexColor(path[0], "GREEN");
    gv->setVertexSize(path[0], 15);

    unordered_map<int, Time> POIs = shortestPath.getPOIsTimes();

    for (int i = 0; i < path.size() - 1; i++) {
        if (POIs.find(path[i]) != POIs.end()) {
            gv->setVertexLabel(path[i], graph.findPOI(path[i])->getName());
            gv->setVertexSize(path[i], 15);
            gv->setVertexColor(path[i],"YELLOW");
        }
        gv->addEdge(id, path[i], path[i+1], EdgeType::DIRECTED);
        //gv->setEdgeLabel(id, to_string(a->getCostTo(b->getID())));
        gv->setEdgeColor(id, "ORANGE");
        gv->setEdgeThickness(id, 10);
        id++;
    }

    gv->setVertexLabel(path[path.size() - 1], graph.findPOI(path[path.size() - 1])->getName());
    gv->setVertexSize(path[path.size() - 1], 15);
    gv->setVertexColor(path[path.size() - 1],"YELLOW");

    gv->rearrange();
    closeGV();

}

void GUI::showMultiplePathsInMap(vector<Path> shortestPaths) {
    createGV();
    double yPercent, xPercent;
    vector<string> colours = {"ORANGE","MAGENTA","CYAN","GREEN","YELLOW","BLUE","RED","GRAY","PINK","BLACK","LIGHT_GRAY"};

    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        yPercent = (vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05;
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getID(), (int)(xPercent*gv_w), (int)(yPercent*gv_h));

        //gv->setVertexLabel(vertex->getID(),to_string(vertex->getID()));
        gv->setVertexSize(vertex->getID(), 5);
    }

    int id = 0;
    for (Vertex<coord>* vertex : graph.getVertexSet()) {
        for (Edge<coord>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getID(), edge->getDest()->getID(), EdgeType::UNDIRECTED);
            gv->setEdgeThickness(id, 0.5);
            id++;
        }
    }
    int colour=0;
    for(auto shortestPath: shortestPaths) {
        vector<int> path = shortestPath.getPath();
        if (path.size() == 1) path.push_back(path[0]);
        gv->setVertexLabel(path[0], graph.findPOI(path[0])->getName());
        gv->setVertexColor(path[0], "GREEN");
        gv->setVertexSize(path[0], 15);

        unordered_map<int, Time> POIs = shortestPath.getPOIsTimes();

        for (int i = 0; i < path.size() - 1; i++) {
            if (POIs.find(path[i]) != POIs.end()) {
                gv->setVertexLabel(path[i], graph.findPOI(path[i])->getName());
                gv->setVertexSize(path[i], 15);
                gv->setVertexColor(path[i], "YELLOW");
            }
            gv->addEdge(id, path[i], path[i + 1], EdgeType::DIRECTED);
            //gv->setEdgeLabel(id, to_string(a->getCostTo(b->getID())));
            gv->setEdgeColor(id, colours[colour]);
            gv->setEdgeThickness(id, 10);
            id++;
        }
        colour = (colour==colours.size()-1) ? 0 : colour+1;

        gv->setVertexLabel(path[path.size() - 1], graph.findPOI(path[path.size() - 1])->getName());
        gv->setVertexSize(path[path.size() - 1], 15);
        gv->setVertexColor(path[path.size() - 1], "YELLOW");
    }
    gv->rearrange();
    closeGV();

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

void GUI::clearPaths(vector<vector<int>> paths) {
    for (int j = 0; j < paths.size(); ++j) {
        int idverj = j + 1;
        for(int i=0;i<paths.at(j).size();i++){
            int idveri = i + 1;

            gv->removeEdge(idverj * idveri);
            gv->removeNode(idverj * idveri);
        }
    }

    gv->closeWindow();
}

void GUI::clearEdges(int numEdges) {
    for (int i = 0; i < numEdges; i++)
        gv->removeEdge(i);
}

void GUI::clearAllGraphNodes() {
    for(auto v: graph.getVertexSet())
        gv->removeNode(v->getID());
}

void GUI::deleteGV() {
    if(gv!= nullptr){
        gv->closeWindow();
        delete(gv);
    }
}

void GUI::createGV() {
    this->gv = new GraphViewer(gv_w, gv_h, false);
    gv->createWindow(gv_w, gv_h);
    gv->defineVertexColor("GRAY");
    gv->defineVertexSize(5);
    gv->defineEdgeCurved(false);
}

void GUI::closeGV() {
    cout << "Press Enter to exit graph viewer." << endl;
    int character = getchar();
    if (character == '\n') { // enter key is pressed
        deleteGV();
    }
    else
        cin.ignore(1000, '\n');
}
