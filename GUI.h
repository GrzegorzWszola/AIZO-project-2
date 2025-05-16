#ifndef GUI_H
#define GUI_H
#include <chrono>
#include <iostream>

#include "Graphs.h"
#include "Utilities.h"
#include "Algorythms/ShortestPathAlgorithms.h"
#include "Algorythms/MST.h"

using namespace std;

class GUI {
public:
    static void entryMessage(Graph* &graph) {
        while (true) {
            system("cls");
            string input;
            std::chrono::milliseconds timeMatrix, timeList;
            int choice = 0;
            cout << "1.Najkrotsza sciezka\n2.Drzewo rozpinajace\n3.Maksymalny przeplyw\n4.Wyjdz\nWybierz problem: ";
            cin >> input;

            try {
                choice = stoi(input);
                if (choice > 4 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
            } catch (invalid_argument& e) {
                cout << e.what() << endl;
                system("pause");
            }

            if (choice == 1) {
                algorythmMenuShortest(graph, timeMatrix, timeList);
            }
            if (choice == 2) {
                algorythmMenuMST(graph, timeMatrix, timeList);
            }
            if (choice == 3) {

            }
            if (choice == 4) break;
        }
    }

    static void algorythmMenuShortest(Graph* &graph, auto &timeMatrix, auto &timeList) {
        int* distance = nullptr;
        int* previous = nullptr;
        bool directed;
        string input;
        while (true) {
            system("cls");
            int choice = 0;
            cout << "1.Wczytaj z pliku\n2.Wygeneruj losowy graf\n3.Wyswietl listowo i macierzowo\n4.Algorytm Djikstry\n5.Bellman-Ford\n6.Wyswietl wyniki\n7.Wyjdz\nWybierz opcje: ";
            cin >> input;

            try {
                choice = stoi(input);
                if (choice > 7 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
            } catch (invalid_argument& e) {
                cout << e.what() << endl;
                system("pause");
                continue;
            }

            if (choice == 1) {
                readFromFileGUI(graph);
                system("pause");
            }
            if (choice == 2) {
                generateRandomGraphMenu(graph, directed);
                graph->printMatrix();
                graph->printList();
                system("pause");
            }
            if (choice == 3) {
                if (graph != nullptr) {
                    graph->printMatrix();
                    graph->printList();
                } else {
                    cout << "Please generate graph first!";
                    system("pause");
                    continue;
                }
                system("pause");
            }
            if (choice == 4) {
                if (graph == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    system("pause");
                    continue;
                }
                //Changing negative values for Djikstra algorythm
                cout << "Zmieniamy wartosci na ujemne, poniewaz w algorytmie Djikstry nie moze byc ujemnych wartosci krawedzi\n";
                ShortestPathAlgorithms::changeNegativeToPositive(graph);
                graph->printMatrix();
                graph->printList();
                //Getting starting node if not present
                if (graph->getStartingNode() == -1) {
                    string startInput;
                    cout << "Podaj wierzcholeks startowy: ";
                    cin >> startInput;
                    try {
                        int start = stoi(startInput);
                        if (start < 0 || start > graph->getNodes()) throw invalid_argument("Wierzcholek startowy musi byc w grafie");
                        graph->setStartingNode(start);
                    } catch (invalid_argument& e) {
                        cout << e.what() << endl;
                    }
                }
                if (distance != nullptr && distance != nullptr) {
                    delete[] distance;
                    delete[] previous;
                }
                ShortestPathAlgorithms::djikstraAlgorithm(graph, timeMatrix, timeList, distance, previous);
                cout << "Czas na reprezentacje macierzowa: " << timeMatrix.count() << "ms\n";
                cout << "Czas na reprezentacje listowa: " << timeList.count() << "ms\n";
                system("pause");
            }

            if (choice == 5) {
                if (graph == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    system("pause");
                    continue;
                }
                if (graph->getStartingNode() == -1) {
                    string startInput;
                    cout << "Podaj wierzcholeks startowy: ";
                    cin >> startInput;
                    try {
                        int start = stoi(startInput);
                        if (start < 0 || start > graph->getNodes()) throw invalid_argument("Wierzcholek startowy musi byc w grafie");
                        graph->setStartingNode(start);
                    } catch (invalid_argument& e) {
                        cout << e.what() << endl;
                    }
                }
                if (distance != nullptr && distance != nullptr) {
                    delete[] distance;
                    delete[] previous;
                }
                ShortestPathAlgorithms::Ford_BellmanAlgorithm(graph, timeMatrix, timeList, distance, previous);
                system("pause");
            }
            if (choice == 6) {
                if (distance != nullptr) ShortestPathAlgorithms::printResultDistance(graph, graph->getNodes(), distance);
                if (previous != nullptr) ShortestPathAlgorithms::printResultPath(graph, graph->getNodes(), distance, previous);
                else cout << "Nie ma jeszcze wynikow";
                system("pause");
                continue;
            }
            if (choice == 7) {
                delete[] distance;
                delete[] previous;
                break;
            }
        }
    }

    static void algorythmMenuMST(Graph* &graph, auto &timeMatrix, auto &timeList) {
        int sum = 0;
        Edge** mstSet = nullptr;
        while (true) {
            system("cls");
            int choice = 0;
            bool directed = false;
            string input;
            if (mstSet == nullptr && graph != nullptr) {
                mstSet = new Edge*[graph->getNodes()];
                for (int i = 0; i < graph->getNodes(); i++) {
                    mstSet[i] = nullptr;
                }
            }

            cout << "1.Wczytaj z pliku\n2.Wygeneruj losowy graf\n3.Wyswietl listowo i macierzowo\n4.Algorytm Prima\n5.Algorytm Kruskala\n6.Wyswietl wyniki\n7.Wyjdz\nWybierz opcje: ";
            cin >> input;
            try {
                choice = stoi(input);
                if (choice > 7 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
            } catch (invalid_argument& e) {
                cout << e.what() << endl;
                system("pause");
            }

            if (choice == 1) {
                readFromFileGUI(graph);
                directed = isDirectedMatrix(graph);
                system("pause");
            }
            if (choice == 2) {
                while (true) {
                    generateRandomGraphMenu(graph, directed);
                    if (directed) {
                        cout << "Graf musi byc nieskierowany w przypadku mst!";
                        continue;
                    }
                    break;
                }
                graph->printMatrix();
                graph->printList();
                system("pause");
            }
            if (choice == 3) {
                if (graph != nullptr) {
                    graph->printMatrix();
                    graph->printList();
                } else {
                    cout << "Najpierw stworz graf";
                    system("pause");
                    continue;
                }
                system("pause");
            }
            if (choice == 4) {
                if (directed) {
                    cout << "Prosze podac graf nieskierowany";
                    system("pause");
                    continue;
                }
                if (mstSet == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    system("pause");
                    continue;
                }
                for (int i = 0; i < graph->getNodes(); i++) {
                    if (mstSet[i] != nullptr) {
                        delete mstSet[i];
                    }
                }

                MSTAlgorithms::primAlgorithm(graph, timeMatrix, timeList, sum, mstSet);
                MSTAlgorithms::printResult(graph, sum, mstSet);
                // for (int i = 0; i < graph->getNodes(); i++) {
                //     if (mstSet[i] != nullptr) {
                //         delete mstSet[i];
                //     }
                // }
                // MSTAlgorithms::primAlgorithmList(graph, timeList, sum, mstSet);
                // MSTAlgorithms::printResult(graph, sum, mstSet);
            }
            if (choice == 5) {
                if (directed) {
                    cout << "Prosze podac graf nieskierowany";
                    system("pause");
                    continue;
                }
                if (mstSet == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    system("pause");
                    continue;
                }
                for (int i = 0; i < graph->getNodes(); i++) {
                    if (mstSet[i] != nullptr) {
                        delete mstSet[i];
                    }
                }

                MSTAlgorithms::kruskalAlgorithm(graph, timeMatrix, timeList, sum, mstSet);
                MSTAlgorithms::printResult(graph, sum, mstSet);
                // for (int i = 0; i < graph->getNodes(); i++) {
                //     if (mstSet[i] != nullptr) {
                //         delete mstSet[i];
                //     }
                // }
                // MSTAlgorithms::kruskalAlgorithmList(graph, timeList, sum, mstSet);
                // MSTAlgorithms::printResult(graph, sum, mstSet);
            }
            if (choice == 6) {
                if (graph != nullptr && mstSet != nullptr) {
                    MSTAlgorithms::printResult(graph, sum, mstSet);
                }
            }
            if (choice == 7) {
                delete[] mstSet;
                break;
            }
        }
    }

    static void algorythmMenuBellmanFort(Graph* &graph, auto &timeMatrix, auto &timeList) {
        int* distance = nullptr;
        int* previous = nullptr;
        bool directed;
        string input;
        while (true) {
            system("cls");
            int choice = 0;
            cout << "1.Wczytaj z pliku\n2.Wygeneruj losowy graf\n3.Wyswietl listowo\n4.Wyswietl macierzowo\n5.Bellman-Ford\n6.Wyswietl wyniki\n7.Wyjdz\nWybierz opcje: ";
            cin >> input;

            try {
                choice = stoi(input);
                if (choice > 7 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
            } catch (invalid_argument& e) {
                cout << e.what() << endl;
                system("pause");
                continue;
            }

            if (choice == 1) {
                readFromFileGUI(graph);
                system("pause");
            }
            if (choice == 2) {
                generateRandomGraphMenu(graph, directed);
                graph->printMatrix();
                graph->printList();
                system("pause");
            }
            if (choice == 3) {
                if (graph != nullptr) {
                    graph->printList();
                } else {
                    cout << "Please generate graph first!";
                    system("pause");
                    continue;
                }
                system("pause");
            }
            if (choice == 4) {
                if (graph != nullptr) {
                    graph->printMatrix();
                } else {
                    cout << "Please generate graph first!";
                    system("pause");
                    continue;
                }
                system("pause");
            }
            if (choice == 5) {
                if (graph == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    system("pause");
                    continue;
                }
                if (!directed) {
                    cout << "Graf musi być skierowany\n";
                    system("pause");
                    continue;
                }
                if (distance != nullptr && distance != nullptr) {
                    delete[] distance;
                    delete[] previous;
                }


                system("pause");
            }
            if (choice == 6) {

            }
            if (choice == 7) {
                delete[] distance;
                delete[] previous;
                break;
            }
        }
    }

    static void readFromFileGUI(Graph* &graph) {
        string path;
        cout << "Podaj sciezke do pliku: ";
        cin >> path;

        //Reading file and creating graph
        int **graphData = Utilities::readFile(path);
        if (graph != nullptr) {
            delete graph;
            graph = nullptr;
        }
        graph = Utilities::createGraphFromFile(graphData);

        //Printing the graph representations (matrix and list)
        graph->printMatrix();
        graph->printList();

        int rowsToDelete = graphData[0][0];
        //Dealocating memory from data graph list
        for (int i = 0; i <= rowsToDelete; i++) {
            delete[] graphData[i];
        }
        delete[] graphData;
    }

    static void generateRandomGraphMenu(Graph* &graph, bool &directed) {
        string nodesInput, densityInput;
        char directedInput;
        int nodes, density;
        cout << "Podaj ilosc wiercholkow: ";
        cin >> nodesInput;
        cout << "Podaj gestosc w %: ";
        cin >> densityInput;
        cout << "Czy skierowany[y/n]: ";
        cin >> directedInput;

        try {
            nodes = stoi(nodesInput);
            density = stoi(densityInput);
            if (density > 100 || density < 0) throw invalid_argument("Dane musza byc w procentach");

            if ((char)tolower(directedInput) == 'y'){directed = true;}
            else if ((char)tolower(directedInput) == 'n'){directed = false;}
            else throw invalid_argument("Podaj y lub n jako parametry");
        } catch (invalid_argument& e) {
            cout << e.what() << endl;
            return;
        }

        //Generating random non directed graph
        if (graph != nullptr) {
            delete graph;
            graph = nullptr;
        }
        if (directed) {
            Utilities::generateDirectedRandomGraph(graph, nodes, density);
        } else {
            Utilities::generateNonDirectedRandomGraph(graph, nodes, density);
        }
    }

    static bool isDirectedMatrix(Graph* graph) {
        int nodes = graph->getNodes();
        int** matrix = graph->getAdjMatrix();

        for (int u = 0; u < nodes; ++u) {
            for (int v = 0; v < nodes; ++v) {
                if (matrix[u][v] != matrix[v][u]) {
                    return true; // Graph is directed
                }
            }
        }
        return false; // Graph is undirected
    }
};

#endif
