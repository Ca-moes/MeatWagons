#include <iostream>

#include "menu/menus.h"
#include "graph/Graph.h"
#include "src/util/Parser.h"
#include "src/gui/GUI.h"

using namespace std;

int main() {
    vector<Prisoner*> vec;
    int op;

    Graph<coord> graph;
    parseMap(graph, "16x16", true);
    //parseMap(graph, "8x8", true);
    //parseMap(graph, "4x4", true);
    //parseMap(graph, "braga", false);
    //parseMap(graph, "fafe", false);
    //parseMap(graph, "maia", false);
    Path path;
    vector<int> pois;
    GUI fullMap = GUI(graph, 1900, 1000);
    GUI pathGui = GUI(graph, 1900, 1000);

    // Choose Origin
    int originID = choosePlace(graph.getPOIs(), "ORIGIN"), newOrigin;
    if (originID == 0) return 0;

    while ((op = mainMenu()) != 0) {
        switch (op) {
            case 1:
                addPrisoner(vec,graph);
                break;
            case 2:
                removePrisoner(vec);
                break;
            case 3:
                showCurrentPrisoners(vec);
                system("pause");
                break;
            case 4:
                showPOIs(graph.getPOIs());
                system("pause");
                break;
            case 5:
                fullMap.show();
                //fullMap.showPath(graph.bfs(coord(0.0,0.0)));
                //fullMap.showPath(graph.dfs());
                //fullMap.showPath(graph.aStarShortestPath(0, 288, euclidianDistance).getPath());
                break;
            case 6:
                path=Path();
                pois = getPrisonersDestinies(vec);
                pathGui.showPath(graph.nearestNeighbourSearch(originID, originID, pois, path, euclidianDistance).getPath());
                break;
            case 7:
                path=Path();
                pois = getPrisonersDestinies(vec);
                pathGui.showPathInMap(graph.nearestNeighbourSearch(originID, originID, pois, path, euclidianDistance).getPath());
                break;
            case 8:
                newOrigin = choosePlace(graph.getPOIs(), "ORIGIN");
                if (newOrigin != 0) originID = newOrigin;
                break;
            default:
                break;
        }
    }

    return 0;
}
