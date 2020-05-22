//
// Created by GoncaloAlves on 16/05/2020.
//

#ifndef ENTREGA_II_PATH_H
#define ENTREGA_II_PATH_H

#include <vector>
#include <unordered_map>
#include <util/Time.h>

using namespace std;

class Path {
    vector<int> path;
    double path_length;

    // Map with POIs and the corresponding cumulative time to get to that node
    unordered_map<int, Time> POIs;

public:
    Path();
    Path(double length, const vector<int> &path);

    double getLength() const;
    vector<int> getPath() const;
    int getLastNode() const;
    unordered_map<int, Time> getPOIsTimes() const;

    void joinPath(const Path &p);
    void addNode(const int &id);
    void addPOI(const int &id, const Time &time);
};
#endif //ENTREGA_II_PATH_H
