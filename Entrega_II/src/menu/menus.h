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

int prisonerMenu();

int GraphMenu();

int GraphOpsMenu();

void showCurrentPrisoners(vector<Prisoner*> vec);

void removePrisoner(vector<Prisoner*> &vec);

template <class T>
void showPOIs(vector<POI<T>*> vec){
    cout<<"Point Of Interest (choose by ID)"<<endl;
    for(auto p:vec){
        cout<<p->toString()<<endl;
    }
}

template <class T>
void addPrisoner(vector<Prisoner*> &vec, Graph<T> &graph) {
    string name;
    int age,destiny;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER" << endl;
    cout << "__________________________________________________\n" << endl;
    name=readString("Name: ");
    age=readInt("Age: ");
    destiny = choosePlace(graph.getPOIs(), "DESTINY", graph);
    graph.addPOI("Node " + to_string(destiny), {destiny});
    vec.push_back(new Prisoner(vec.size()+1,name,age,destiny));
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER CREATED" << endl;
    cout << "__________________________________________________\n" << endl;
    system("pause");
}

template <class T>
int choosePlace(vector<POI<T>*> POIs, string str, const Graph<coord>& graph) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << str << endl;
    cout << "__________________________________________________\n" << endl;

    for (int i = 0; i < POIs.size(); i++) {
        cout << i + 1 << " - " << POIs[i]->getName() << endl;
    }
    cout << "\n" << POIs.size() + 1 << " - Choose Node ID" << endl;
    cout << "\n0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;

    int placeID = chooseMenuOption(POIs.size() + 1);

    if (placeID == POIs.size() + 1) {
        do {
            placeID = readInt("ID number: ");
        } while (graph.findVertex(placeID) == nullptr);
    }
    else if (placeID > 0)
        placeID = POIs[placeID - 1]->getIDs()[0];

    return placeID;
}

Graph<coord> chooseGraph(vector<Graph<coord>> graphVec);

#endif //ENTREGA_II_MENUS_H
