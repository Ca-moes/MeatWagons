//
// Created by pedro on 05/05/2020.
//

#ifndef ENTREGA_II_MENUS_H
#define ENTREGA_II_MENUS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <prison/Vehicle.h>
#include "util/utils.h"
#include "prison/Prisoner.h"
#include "graph/Graph.h"

using namespace std;

int mainMenu();

int prisonerMenu();

int GraphMenu();

int GraphOpsMenu();

void showCurrentPrisoners(vector<Prisoner*> vec);

void showCurrentVehicles(vector<Vehicle *> vector);

void removePrisoner(vector<Prisoner*> &vec, vector<Vehicle *> &vehiclesVec);

Vehicle *addVehicle(vector<Vehicle *> &vector);

void removeVehicle(vector<Vehicle *> &vector);

void changePrisonersVehicle(vector<Prisoner *> &prisonersVec, vector<Vehicle *> &vehiclesVec);

template <class T>
void showPOIs(vector<POI<T>*> vec){
    cout<<"Point Of Interest (choose by ID)"<<endl;
    for(auto p:vec){
        cout<<p->toString()<<endl;
    }
}

template <class T>
void addPrisoner(vector<Prisoner*> &vec, Graph<T> graph, vector<Vehicle*>& vehicles) {
    string name;
    int age, destiny;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER" << endl;
    cout << "__________________________________________________\n" << endl;
    name = readString("Name: ");
    age = readInt("Age: ");
    destiny = choosePlace(graph.getPOIs(), "DESTINY", graph);
    Prisoner *prisoner = new Prisoner(vec.size() + 1, name, age, destiny);
    vec.push_back(prisoner);
    graph.addPOI("Node " + to_string(destiny), {destiny});
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER CREATED" << endl;
    cout << "__________________________________________________\n" << endl;
    // TODO está vazio ou todos os veiculos cheios
    if (vehicles.empty() || allVehiclesFull(vehicles)) {
        cout << "No vehicles available" << endl;
        Vehicle *vehicle = addVehicle(vehicles);
        vehicle->addPrisoner(prisoner);
        cout << "Added Prisoner to new Vehicle!" << endl;

    } else {
        cout << "Choose existing vehicle or create a new one?\n1 - Existing\n2 - New one" << endl;
        int menuop = chooseMenuOption(2);
        if (menuop == 2) {
            Vehicle *vehicle = addVehicle(vehicles);
            vehicle->addPrisoner(prisoner);
        } else if (menuop == 1) {
            showCurrentVehicles(vehicles);
            int menuop2 = chooseMenuOption(vehicles.size());
            if (menuop2 != 0) {
                Vehicle *vehicle = vehicles[menuop2 - 1];
                vehicle->addPrisoner(prisoner);
                cout << "Added Prisoner to existing Vehicle!" << endl;
            }
        }

    }
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
