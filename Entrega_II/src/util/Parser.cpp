//
// Created by GoncaloAlves on 06/05/2020.
//


#include "Parser.h"

void parseMap(Graph<coord> &graph, const string &location, bool grid) {

    string node_file;
    string edge_file;

    if (grid) {
        node_file = "../Mapas/GridGraphs/GridGraphs/" + location + "/nodes.txt";
        edge_file = "../Mapas/GridGraphs/GridGraphs/" + location + "/edges.txt";
    }
    else {
        node_file = "../Mapas/" + location + "/nodes_x_y_" + location + ".txt";
        edge_file = "../Mapas/" + location + "/edges_" + location + ".txt";

    }
    parseTag(graph, location);
    string line;

    ifstream node;
    node.open(node_file);
    if (!node.is_open()) { cout<<"Couldn't open node file\n"; }

    getline(node, line);
    int num_nodes = stoi(line);

    for (int i = 0; i < num_nodes; i++) {
        getline(node, line);
        stringstream ss(line);
        string temp;
        int id, tag; double x, y;
        getline(ss,temp,'(');
        getline(ss,temp,',');
        id=stoi(temp);
        getline(ss,temp,',');
        x=stod(temp);
        getline(ss,temp,',');
        y=stod(temp);
        //cout<<id<<"\t"<<x<<"\t"<<y<<"\t"<<endl;
        tag=0;
        for(auto p : graph.getPOIs()){
            for(auto id_poi : p->getIDs())
                if(id_poi==id)
                    tag=1;
        }
        graph.addVertex(id,make_pair(x, y),tag);

    }
    cout<<"Done Nodes\n";
    node.close();

    ifstream edge;
    edge.open(edge_file);

    if (!edge.is_open()) { cout<<"Couldn't open edge file"; }

    getline(edge, line);
    int num_edges = stoi(line);
    for (int i = 0; i < num_edges; i++) {
        getline(edge, line);
        stringstream ss(line);
        string temp;
        int o, d;

        getline(ss,temp,'(');
        getline(ss,temp,',');
        o=stoi(temp);
        getline(ss,temp,',');
        d=stoi(temp);
        //cout<<o<<"\t"<<graph.findVertex(o)->getInfo().first<<"\t"<<graph.findVertex(o)->getInfo().second<<endl;
        //cout<<d<<"\t"<<graph.findVertex(d)->getInfo().first<<"\t"<<graph.findVertex(d)->getInfo().second<<endl;
        double weight = euclidianDistance(graph.findVertex(o)->getInfo(),graph.findVertex(d)->getInfo());
        //cout<<weight<<endl;
        graph.addEdge(o, d, weight);
        if (grid)
            graph.addEdge(d, o, weight);
    }
    cout<<"Done Edges\n";
    edge.close();
}

void parseTag(Graph<coord> &graph, const string &location) {
    string tag_file = "../Mapas/Tags/tags_"+location+".txt";
    string line;

    ifstream tag;
    tag.open(tag_file);
    if (!tag.is_open()) { cout<<"Couldn't open tag file\n"; }

    while(!tag.eof()){
        getline(tag, line);
        string name = line;
        getline(tag, line);
        int num_tags = stoi(line);
        vector<int> ids;
        for (int i = 0; i < num_tags; i++) {
            getline(tag, line);
            int id=stoi(line);
            ids.push_back(id);

        }
        graph.addPOI(name,ids);

    }

    cout<<"Done Tags\n";
    tag.close();

}
