//
// Created by GoncaloAlves on 16/05/2020.
//

#include "Path.h"

Path::Path() {
    this->path_length = 0;
    this->path = vector<int>();
}

Path::Path(double length, const vector<int> &path) {
    this->path_length=length;
    this->path=path;
}

double Path::getLength() const {
    return this->path_length;
}

vector<int> Path::getPath() const {
    return this->path;
}

int Path::getLastNode() const {
    return this->path.back();
}

void Path::joinPath(const Path &p) {
    this->path_length+=p.getLength();
    this->path.insert(path.end(),p.path.begin()+1,p.path.end());
}

void Path::addNode(const int &id) {
    this->path.push_back(id);
}

