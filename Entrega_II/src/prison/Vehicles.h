//
// Created by andre_4mxog39 on 18/05/2020.
//

#ifndef ENTREGA_II_VEHICLES_H
#define ENTREGA_II_VEHICLES_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "prison/Prisoner.h"
using namespace std;

class Vehicle {
private:
    int capacity;
    int maxVelHighWay;
    int maxVelRoad;
    vector<Prisoner> prisoners;
public:
    Vehicle(int capacity, int maxVelHighWay, int maxVelRoad);

    int getCapacity();
    void setCapacity(int capacity);
    int getMaxVelHighWay() const;
    void setMaxVelHighWay(int maxVelHighWay);
    int getMaxVelRoad() const;
    void setMaxVelRoad(int maxVelRoad);
    const vector<Prisoner> &getPrisoners() const;
    void setPrisoners(const vector<Prisoner> &prisoners);

    void addPrisoner(Prisoner prisoner);
    bool isAtMaxCapacity();
};

class Car : public Vehicle
{
public:
    Car(int capacity1);
};

class Bus : public Vehicle
{
public:
    Bus(int capacity1);
};

#endif //ENTREGA_II_VEHICLES_H
