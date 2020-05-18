#include <iostream>


#include "menu/menus.h"
#include "graph/Graph.h"
#include "src/util/Parser.h"
#include "src/gui/GUI.h"

using namespace std;

/* NOTAS
 *
 * A função de comparar não funciona decentemente porque o grafo é muito pequeno
 *
 * As landmarks que estão em baixo são uma coisa temporária. Aquela funcao preComputeLandmraks demora demasiado tempo
 * para a executarmos sempre que iniciamos o programa (com os grids nao, mas com mapas de portugal vai demorar), ou seja,
 * quando tivermos os mapas, corremos esta função uma vez e guardamos num ficheiro ou assim a informação.
 * As landmarks devem ser pontos escolhidos por exemplo nas extremidades do grafo, ou seja, quando tivermos os mapas a serio vamos
 * ter que encontrar pontos que possam funcionar como landmarks, executar a funcao com esses pontos, e guardar a informação para esse mapa
 *
 * */

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

    // Testar Conectividade e eliminar nodes nao necessarios

    vector<int> landmarks = {0, 16, 272, 288};
    graph.preComputeLandmarks(landmarks);

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
                pathGui.showPath(graph.nearestNeighbourSearchAStar(originID, originID, pois, path, euclidianDistance).getPath());
                break;
            case 7:
                path=Path();
                pois = getPrisonersDestinies(vec);
                //pathGui.showPathInMap(graph.nearestNeighbourSearchAStar(originID, originID, pois, path, euclidianDistance).getPath());
                pathGui.showPathInMap(graph.nearestNeighbourSearchALT(originID, originID, pois, path).getPath());
                break;
            case 8:
                newOrigin = choosePlace(graph.getPOIs(), "ORIGIN");
                if (newOrigin != 0) originID = newOrigin;
                break;
            case 9:
                path = Path();
                pois = getPrisonersDestinies(vec);
                compareALTandAStar(graph, originID, pois, path);
                break;
            case 10:
                path = Path();
                pois = getPrisonersDestinies(vec);
                compareALTandDijkstra(graph, originID, pois, path);
                break;
            case 11:
                path = Path();
                pois = getPrisonersDestinies(vec);
                compareAStarandDijkstra(graph, originID, pois, path);
                break;
            default:
                break;
        }
    }

    return 0;
}

