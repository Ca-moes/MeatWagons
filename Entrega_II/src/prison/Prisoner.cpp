//
// Created by pedro on 05/05/2020.
//


#include "Prisoner.h"

Prisoner::Prisoner(int id, string name, int age, int dest) {
    this->id = id;
    this->name = name;
    this->age = age;
    this->dest = dest;
}

int Prisoner::getID() {
    return this->id;
}

string Prisoner::getName() {
    return this->name;
}

int Prisoner::getAge() {
    return this->age;
}

int Prisoner::getDest() {
    return this->dest;
}

vector<int> getPrisonersDestinies(vector<Prisoner*> vec){
    vector<int> des;
    for(auto p:vec){
        if(find(des.begin(),des.end(),p->getDest())==des.end())
            des.push_back(p->getDest());
    }
    return des;
}