//
// Created by pedro on 05/05/2020.
//

#ifndef ENTREGA_II_PRISONER_H
#define ENTREGA_II_PRISONER_H

#include <string>

using namespace std;

class Prisoner {
private:
    int id;
    string name;
    int age;
    int dest;

public:
    Prisoner(int id, string name, int age, int dest);

    int getID();
    string getName();
    int getAge();
    int getDest();
};


#endif //ENTREGA_II_PRISONER_H
