//
// Created by pedro on 05/05/2020.
//

#ifndef ENTREGA_II_MENUS_H
#define ENTREGA_II_MENUS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "util/utils.h"
#include "prison/Prisoner.h"
#include "graph/Graph.h"

using namespace std;

int mainMenu();

void showCurrentPrisoners(vector<Prisoner*> vec);

template <class T>
void showPOIs(vector<POI<T>*> vec){
    cout<<"Point Of Interest (choose by ID)"<<endl;
    for(auto p:vec){
        cout<<p->toString()<<endl;
    }
}

template <class T>
void addPrisoner(vector<Prisoner*> &vec, Graph<T> graph) {
    string name;
    int age,destiny;
    bool error=false;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER" << endl;
    cout << "__________________________________________________\n" << endl;
    name=readString("Name: ");
    age=readInt("Age: ");
    showPOIs(graph.getPOIs());
    do{
        destiny=readInt("Destiny: ");
        if(graph.findPOI(destiny)== nullptr){
            error=true;
            cout << "Invalid POI!" << endl;
        }

    }while(error);
    vec.push_back(new Prisoner(vec.size()+1,name,age,destiny));
    cout << setw(23) << right << "PRISONER CREATED" << endl;
    cout << "__________________________________________________\n" << endl;
    system("pause");
}

#endif //ENTREGA_II_MENUS_H
