#include <iostream>
#include <prison/Vehicle.h>


#include "menu/menus.h"
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
    vector<Prisoner*> prisonerVec;
    vector<Vehicle*> vehiclesVec;

    int op,op2;

    Graph<coord> full,strong;
    parseMap(full, "porto_full", false);
    parseMap(strong, "porto_strong", false);
    vector<Graph<coord>> graphVec = {full, strong};
    Graph<coord> graphSelect=chooseGraph(graphVec);;
    //parseMap(graph, "16x16", true);
    //parseMap(graphSelect, "8x8", true);
    //parseMap(graph, "4x4", true);

    //parseMap(graph, "braga", false);
    //parseMap(graph, "fafe", false);
    //parseMap(graph, "maia", false);

    // Testar Conectividade e eliminar nodes nao necessarios
    Graph<coord> graphconnecteddfs;
    constructGraphByPath(graphSelect, graphconnecteddfs, graphSelect.dfs(1));
    Graph<coord> graphconnectedbfs;
    constructGraphByPath(graphSelect, graphconnectedbfs, graphSelect.bfs(1));

    //vector<int> landmarks = {37213, 27053, 41814, 29229};
    //graphSelect.preComputeLandmarks(landmarks);

    //Choose Graph
    Graph<coord> graph=graphSelect;

    Path path;
    vector<int> pois;
    vector<vector<int>> pathsToDisplay;
    vector<int> conect;
    cout << "Waiting";
    GUI fullMap = GUI(graph, 1900, 1000);
    cout << ".";
    //GUI pathGui = GUI(graph, 1900, 1000);
    //cout << ".";
    GUI dfsMap = GUI(graphconnecteddfs,1900,1000);
    cout << ".\n";
    GUI bfsMap = GUI(graphconnectedbfs,1900,1000);
    cout << ".\n";

    // Choose Origin
    int originID = choosePlace(graph.getPOIs(), "ORIGIN", graph), newOrigin;
    if (originID == 0) return 0;


    while ((op = mainMenu()) != 0) {
        switch (op) {
            case 1:
                while((op2=prisonerMenu())!=0){
                    switch(op2) {
                        case 1:
                            addPrisoner(prisonerVec, graph, vehiclesVec);
                            break;
                        case 2:
                            removePrisoner(prisonerVec, vehiclesVec);
                            break;
                        case 3:
                            showCurrentPrisoners(prisonerVec);
                            system("pause");
                            break;
                        case 4:
                            addVehicle(vehiclesVec);
                            break;
                        case 5:
                            removeVehicle(vehiclesVec);
                            break;
                        case 6:
                            cout << "__________________________________________________\n" << endl;
                            cout << setw(23) << right << "List of Vehicles" << endl;
                            cout << "__________________________________________________\n" << endl;
                            showCurrentVehicles(vehiclesVec);
                            system("pause");
                            break;
                        case 7:
                            changePrisonersVehicle(prisonerVec, vehiclesVec);
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 2:
                while((op2=GraphMenu())!=0){
                    switch(op2) {
                        case 1:
                            graph=chooseGraph(graphVec);
                            system("pause");
                            break;
                        case 2:
                            showPOIs(graph.getPOIs());
                            system("pause");
                            break;
                        case 3:
                            fullMap.show();
                            break;
                        case 4:
                            path=Path();
                            pois = getPrisonersDestinies(prisonerVec);
                            path = graph.nearestNeighbourSearchAStar(originID, pois, path, euclidianDistance);
                            cout << "Minimum Time: " << path.getLength() << "s" << endl << "Nodes in Path: " << path.getPath().size() << endl;
                            fullMap.showPath(path.getPath());
                            break;
                        case 5:
                            path=Path();
                            pois = getPrisonersDestinies(prisonerVec);
                            path = graph.nearestNeighbourSearchAStar(originID, pois, path, euclidianDistance);
                            cout << "Minimum Time: " << path.getLength() << "s" << endl << "Nodes in Path: " << path.getPath().size() << endl;
                            fullMap.showPathInMap(path.getPath());
                            break;
                        case 6:
                            newOrigin = choosePlace(graph.getPOIs(), "ORIGIN", graph);
                            if (newOrigin != 0) originID = newOrigin;
                            break;
                        case 7:
                            dfsMap.show();
                            break;
                        case 8:
                            bfsMap.show();
                            break;
                        default:
                            break;
                    }
                }
                break;

            case 3:
                while((op2=GraphOpsMenu())!=0){
                    switch(op2) {
                        case 1:
                            pois = getPrisonersDestinies(prisonerVec);
                            compareALTandAStar(graph, originID, pois);
                            system("pause");
                            break;
                        case 2:
                            pois = getPrisonersDestinies(prisonerVec);
                            compareALTandDijkstra(graph, originID, pois);
                            system("pause");
                            break;
                        case 3:
                            pois = getPrisonersDestinies(prisonerVec);
                            compareAStarandDijkstra(graph, originID, pois);
                            system("pause");
                            break;
                        case 4:
                            compareDFSandBFS(graph, originID);
                            system("pause");
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }

    return 0;
}


