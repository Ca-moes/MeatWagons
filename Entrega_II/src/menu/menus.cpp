//
// Created by pedro on 05/05/2020.
//

#include "menus.h"

int mainMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "MAIN MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Prisoner/Vehicle Menu" << endl;
    cout << " 2 - Graph Visualization" << endl;
    cout << " 3 - Algorithm Comparison" << endl;
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;

    return chooseMenuOption(3);
}

int prisonerMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONER MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Add Prisoner" << endl;
    cout << " 2 - Remove Prisoner" << endl;
    cout << " 3 - See Current Prisoners" << endl;
    cout << " 4 - Add Vehicle" << endl;
    cout << " 5 - Remove Vehicle" << endl;
    cout << " 6 - Display Vehicles" << endl;
    cout << " 7 - Change Prisoner's Vehicle" << endl;
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;
    return chooseMenuOption(7);
}

int GraphMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "GRAPH MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Show Current POI'S" << endl;
    cout << " 2 - Show Graph" << endl;
    cout << " 3 - Show Best Path" << endl;
    cout << " 4 - Show Best Path in Map" << endl;
    cout << " 5 - Change Origin Point" << endl;
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;
    return chooseMenuOption(5);
}

int GraphOpsMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "ALGORITHMS MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Compare ALT with A-Star" << endl;
    cout << " 2 - Compare ALT with Dijkstra" << endl;
    cout << " 3 - Compare Dijkstra with A-Star" << endl;
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;
    return chooseMenuOption(3);
}

void showCurrentPrisoners(vector<Prisoner*> vec) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "PRISONERS" << endl;
    cout << "__________________________________________________\n" << endl;
    if (!vec.empty())
        for (Prisoner * p : vec)
            cout << "Name: " << p->getName() << " (" << p->getID() << ")\tAge: " << p->getAge() << "\tDestination: " << p->getDest() << endl;
    else
        cout << "No prisoners to transport." << endl;
    cout << "__________________________________________________\n" << endl;
}

void removePrisoner(vector<Prisoner *> &vec, vector<Vehicle *> &vehiclesVec) {
    showCurrentPrisoners(vec);
    cout << "0 - Exit\n\n";

    int index = chooseMenuOption(vec.size());

    if (index > 0){
        Prisoner* prisoner = vec.at(index-1);
        vec.erase(vec.begin() + index - 1);
        int indexx = 0;
        for (int i = 0; i < vehiclesVec.size(); i++) {
            auto it = std::find_if(vehiclesVec[i]->getPrisoners().begin(),
                                   vehiclesVec[i]->getPrisoners().end(),
                                   [&](auto p) { return p->getID() == prisoner->getID(); });
            if (it != vehiclesVec[i]->getPrisoners().end()){
                indexx = i;
                break;
            }
        }
        vehiclesVec.at(indexx)->removePrisoner(prisoner);
    }
}

Vehicle *addVehicle(vector<Vehicle *> &vector) {
    cout << "Choose type of Vehicle:\n1 - Car\n2 - Bus" << endl;
    int menuop = chooseMenuOption(2);
    while (menuop == 0) menuop = chooseMenuOption(2);
    if(menuop == 1) {
        cout << "Choose capacity (1 or 2)\n";
        int cap = chooseMenuOption(2);
        if (cap != 0) {
            Car *car = new Car(cap);
            vector.push_back(car);
            cout << "Vehicle created!\n";
            return car;
        }

    }
    else if (menuop == 2){
        cout << "Choose capacity (1 to 10)\n";
        int cap = chooseMenuOption(10);
        if (cap != 0) {
            Bus *bus = new Bus(cap);
            vector.push_back(bus);
            cout << "Vehicle created!\n";
            return bus;
        };
    }

    return nullptr;
}

void removeVehicle(vector<Vehicle *> &vector) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Vehicles" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "Only Vehicles with no Prisoners can be removed.\n" << endl;
    showCurrentVehicles(vector);
    int menuop2 = chooseMenuOption(vector.size());
    if (menuop2 != 0) {
        if (vector.at(menuop2-1)->getPrisoners().empty()){
            vector.erase(vector.begin() + menuop2 - 1);
            cout << "Removed successfully!" << endl;
        } else {
            cout << "Vehicle is not empty!" << endl;
        }
        system("pause");
    }

}
void showCurrentVehicles(vector<Vehicle *> vector) {
    if (vector.empty())
        cout << "No available Vehicles" << endl;
    else {
        cout << "ID - Type of Vehicle - used places/capacity - Speed on Roads/Speed on Highways" << endl;
        for (int i = 0; i < vector.size(); ++i) {
            string type = dynamic_cast<Car*>(vector[i]) != nullptr ? "Car" : "Bus";
            cout << " " << i + 1 << " - " << type << " - " << *vector[i] << endl;
        }
    }
    cout << "__________________________________________________\n" << endl;
}

void changePrisonersVehicle(vector<Prisoner *> &prisonersVec, vector<Vehicle *> &vehiclesVec) {
    if (vehiclesVec.size() > 1) {
        showCurrentPrisoners(prisonersVec);
        if (!prisonersVec.empty()) {
            int index = chooseMenuOption(prisonersVec.size()), indexToReject, index2;

            if (index > 0) {
                Prisoner *prisoner = prisonersVec.at(index - 1);
                cout << "Change to which Vehicle?" << endl;
                cout << "ID - Type of Vehicle - used places/capacity - Speed on Roads/Speed on Highways" << endl;
                for (int i = 0; i < vehiclesVec.size(); i++) {
                    string type = dynamic_cast<Car *>(vehiclesVec[i]) != nullptr ? "Car" : "Bus";

                    auto it = std::find_if(vehiclesVec[i]->getPrisoners().begin(),
                                           vehiclesVec[i]->getPrisoners().end(),
                                           [&](auto p) { return p->getID() == prisoner->getID(); });

                    if (it == vehiclesVec[i]->getPrisoners().end())
                        cout << " " << i + 1 << " - " << type << " - " << *vehiclesVec[i] << endl;
                    else indexToReject = i + 1;

                    do {
                        index2 = chooseMenuOption(vehiclesVec.size());
                    } while (index2 == indexToReject);

                    if (!vehiclesVec.at(indexToReject - 1)->removePrisoner(prisoner))
                        cout << "Erro a remover Prisioneiro" << endl;
                    vehiclesVec.at(index2 - 1)->addPrisoner(prisoner);

                    cout << "Change made!" << endl;
                }
                cout << "0 - Exit\n\n";
            } else cout << "No prisoners available" << endl;
        } else cout << "No available Vehicles to switch to" << endl;
    }
}
