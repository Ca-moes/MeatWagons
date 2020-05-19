//
// Created by pedro on 05/05/2020.
//

#include "menus.h"

int mainMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "MAIN MENU" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << " 1 - Prisoner Menu" << endl;
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
    cout << endl << " 0 - Exit" << endl;
    cout << "__________________________________________________\n" << endl;
    return chooseMenuOption(3);
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

void removePrisoner(vector<Prisoner *> &vec) {
    showCurrentPrisoners(vec);
    cout << "0 - Exit\n\n";

    int index = chooseMenuOption(vec.size());

    if (index > 0)
        vec.erase(vec.begin() + index - 1);
}




