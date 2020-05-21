//
// Created by pedro on 05/05/2020.
//

#ifndef ENTREGA_II_PRISONER_H
#define ENTREGA_II_PRISONER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <util/Time.h>

using namespace std;

class Prisoner {
private:
    int id;
    string name;
    int age;
    int dest;
    Time deliveryTime;

public:
    Prisoner(int id, string name, int age, int dest, Time deliveryTime);

    int getID();
    string getName();
    int getAge();
    int getDest();
    Time getDeliveryTime() const;
};

vector<int> getPrisonersDestinies(vector<Prisoner*> vec);

#endif //ENTREGA_II_PRISONER_H
