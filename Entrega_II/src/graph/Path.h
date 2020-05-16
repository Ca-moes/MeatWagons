//
// Created by GoncaloAlves on 16/05/2020.
//

#ifndef ENTREGA_II_PATH_H
#define ENTREGA_II_PATH_H

#include <vector>

using namespace std;

class Path{
    vector<int> path;
    double path_length;

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
