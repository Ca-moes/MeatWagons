//
// Created by GoncaloAlves on 06/05/2020.
//


#include "Parser.h"

Graph<coord> parseMap(const string &node_file, const string &edge_file) {
    Graph<coord> graph;
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
        int id,x, y;
        getline(ss,temp,'(');
        getline(ss,temp,',');
        id=stoi(temp);
        getline(ss,temp,',');
        x=stoi(temp);
        getline(ss,temp,',');
        y=stoi(temp);
        graph.addVertex(make_pair(x, y));

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
        graph.addEdge(o, d, 1);
        graph.addEdge(d, o, 1);
    }
    cout<<"Done Edges\n";
    edge.close();

    return graph;
}