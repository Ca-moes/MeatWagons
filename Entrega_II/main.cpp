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

    Graph<coord> graph;
    //parseMap(graph, "porto", false);
    parseMap(graph, "16x16", true);
    //parseMap(graph, "8x8", true);
    //parseMap(graph, "4x4", true);
    //parseMap(graph, "braga", false);
    //parseMap(graph, "fafe", false);
    //parseMap(graph, "maia", false);

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
                //gui.show();
                //gui.showPath(graph.bfs(coord(0.0,0.0)));
                //gui.showPath(graph.dfs());
                break;
            default:
                break;
        }
    }

    return 0;
}
