//
// Created by andre_4mxog39 on 18/05/2020.
//

#include "Vehicle.h"

Vehicle::Vehicle(int capacity, int maxVelHighWay, int maxVelRoad) {
    this->capacity = capacity;
    this->maxVelHighWay = maxVelHighWay;
    this->maxVelRoad = maxVelRoad;
}

int Vehicle::getCapacity() {
    return 0;
}

void Vehicle::setCapacity(int capacity) {
    Vehicle::capacity = capacity;
}

int Vehicle::getMaxVelHighWay() const {
    return maxVelHighWay;
}

void Vehicle::setMaxVelHighWay(int maxVelHighWay) {
    Vehicle::maxVelHighWay = maxVelHighWay;
}

int Vehicle::getMaxVelRoad() const {
    return maxVelRoad;
}

void Vehicle::setMaxVelRoad(int maxVelRoad) {
    Vehicle::maxVelRoad = maxVelRoad;
}


void Vehicle::addPrisoner(Prisoner *prisoner) {
    this->prisoners.push_back(prisoner);
}

bool Vehicle::isAtMaxCapacity() {
    return this->capacity == this->prisoners.size();
}

const vector<Prisoner*> &Vehicle::getPrisoners() const{
    return prisoners;
}

void Vehicle::setPrisoners(const vector<Prisoner*> &prisoners) {
    Vehicle::prisoners = prisoners;
}

Car::Car(int capacity) : Vehicle(capacity, 120, 90) {
}

Car::~Car() {}

Bus::Bus(int capacity) : Vehicle(capacity, 100, 80) {
}

Bus::~Bus() {}

ostream& operator<<(ostream& os, const Vehicle& dt)
{
    os << dt.prisoners.size() << '/' << dt.capacity << " - " << dt.maxVelRoad << '/' << dt.maxVelHighWay;
    return os;
}

Vehicle::~Vehicle() {}
