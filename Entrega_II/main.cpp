#include <iostream>

#include "menu/menus.h"
#include "graph/Graph.h"
#include "src/util/Parser.h"
#include "src/gui/GUI.h"

using namespace std;

int main() {
    vector<Prisoner*> vec;
    int op;
    int num = 0;

    //Graph<coord> graph = parseMap("../Mapas-20200420/GridGraphs/GridGraphs/16x16/nodes.txt", "../Mapas-20200420/GridGraphs/GridGraphs/16x16/edges.txt");
    //Graph<coord> graph = parseMap("../Mapas-20200420/Porto/nodes_x_y_porto.txt", "../Mapas-20200420/Porto/edges_porto.txt");
    Graph<coord> graph = parseMap("../Mapas-20200420/Fafe/nodes_x_y_fafe.txt", "../Mapas-20200420/Fafe/edges_fafe.txt");

    GUI gui = GUI(graph, 1900, 1000);

    while ((op = mainMenu()) != 0) {
        switch (op) {
            case 1:
                vec.push_back(new Prisoner(num, "Novo Prisioneiro", 10, 1));
                num++;
                break;
            case 2:
                if (num > 0) {
                    num--;
                    vec.erase(vec.begin() + num);
                }
                break;
            case 3:
                showCurrentPrisoners(vec);
                break;
            case 4:
                gui.show();
                break;
            default:
                break;
        }
    }

    return 0;
}
