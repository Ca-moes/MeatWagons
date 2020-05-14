//
// Created by GoncaloAlves on 06/05/2020.
//


#include "Parser.h"

void parseMap(Graph<coord> &graph, const string &node_file, const string &edge_file) {
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
        int id; double x, y;
        getline(ss,temp,'(');
        getline(ss,temp,',');
        id=stoi(temp);
        getline(ss,temp,',');
        x=stod(temp);
        getline(ss,temp,',');
        y=stod(temp);
        //cout<<id<<"\t"<<x<<"\t"<<y<<"\t"<<endl;
        graph.addVertex(id,make_pair(x, y));

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
        //graph.addEdge(d, o, weight);
    }
    cout<<"Done Edges\n";
    edge.close();
}