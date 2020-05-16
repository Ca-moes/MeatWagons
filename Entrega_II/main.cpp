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
    Path path;
    vector<int> pois;
    GUI gui = GUI(graph, 1900, 1000);

    while ((op = mainMenu()) != 0) {
        switch (op) {
            case 1:
                addPrisoner(vec,graph);
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
                showPOIs(graph.getPOIs());
                system("pause");
                break;
            case 5:
                //gui.show();
                //gui.showPath(graph.bfs(coord(0.0,0.0)));
                //gui.showPath(graph.dfs());
                //gui.showPath(graph.aStarShortestPath(0, 288, euclidianDistance).getPath());
                path=Path();
                pois= getPrisonersDestinies(vec);
                gui.showPath(graph.nearestNeighbourSearch(0,288,pois,path,euclidianDistance).getPath());
                break;
            default:
                break;
        }
    }

    return 0;
}
