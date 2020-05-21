//
// Created by GoncaloAlves on 16/05/2020.
//

#ifndef ENTREGA_II_PATH_H
#define ENTREGA_II_PATH_H

#include <vector>
#include <unordered_map>

using namespace std;

class Path {
    vector<int> path;
    double path_length;

    // Map with POIs and the corresponding time to get to that node
    unordered_map<int, double> POIs;

public:
    Path();
    Path(double length, const vector<int> &path);

    double getLength() const;
    vector<int> getPath() const;
    int getLastNode() const;
    void joinPath(const Path &p);
    void addNode(const int &id);
};
#endif //ENTREGA_II_PATH_H
