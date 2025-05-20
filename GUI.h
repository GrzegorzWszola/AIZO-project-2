#ifndef GUI_H
#define GUI_H

#include <chrono>
#include <iostream>
#include <cstdlib>  // dla system()

#include "Graphs.h"
#include "Utilities.h"
#include "Algorythms/ShortestPathAlgorithms.h"
#include "Algorythms/MST.h"

using namespace std;

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
    #define PAUSE_SYSTEM "pause"
#else
    #define CLEAR_SCREEN "clear"
#endif

void clearScreen() {
    system(CLEAR_SCREEN);
}

void pause() {
#ifdef _WIN32
    system(PAUSE_SYSTEM);
#else
    cin.ignore();
    cout << "Nacisnij Enter aby kontynuowac...";
    cin.get();
#endif
}

class GUI {
public:
    static void entryMessage(Graph* &graph) {
        while (true) {
            clearScreen();
            string input;
            chrono::milliseconds timeMatrix, timeList;
            int choice = 0;
            cout << "1. Najkrotsza sciezka\n2. Drzewo rozpinajace\n3. Maksymalny przeplyw\n4. Wyjdz\nWybierz problem: ";
            cin >> input;

            try {
                choice = stoi(input);
                if (choice > 4 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
            } catch (invalid_argument& e) {
                cout << e.what() << endl;
                pause();
            }

            if (choice == 1) algorythmMenuShortest(graph, timeMatrix, timeList);
            if (choice == 2) algorythmMenuMST(graph, timeMatrix, timeList);
            if (choice == 3) {
                // TODO: Maksymalny przeplyw
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
            clearScreen();
            int choice = 0;
            cout << "1. Wczytaj z pliku\n2. Wygeneruj losowy graf\n3. Wyswietl listowo i macierzowo\n4. Algorytm Djikstry\n5. Bellman-Ford\n6. Wyswietl wyniki\n7. Wyjdz\nWybierz opcje: ";
            cin >> input;

            try {
                choice = stoi(input);
                if (choice > 7 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
            } catch (invalid_argument& e) {
                cout << e.what() << endl;
                pause();
                continue;
            }

            if (choice == 1) {
                readFromFileGUI(graph);
                pause();
            }
            if (choice == 2) {
                generateRandomGraphMenu(graph, directed);
                graph->printMatrix();
                graph->printList();
                pause();
            }
            if (choice == 3) {
                if (graph != nullptr) {
                    graph->printMatrix();
                    graph->printList();
                } else {
                    cout << "Please generate graph first!";
                }
                pause();
            }
            if (choice == 4) {
                if (graph == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    pause();
                    continue;
                }
                cout << "Zmieniamy wartosci na dodatnie, poniewaz w algorytmie Djikstry nie moze byc ujemnych wartosci krawedzi\n";
                ShortestPathAlgorithms::changeNegativeToPositive(graph);
                graph->printMatrix();
                graph->printList();

                if (graph->getStartingNode() == -1) {
                    string startInput;
                    cout << "Podaj wierzcholek startowy: ";
                    cin >> startInput;
                    try {
                        int start = stoi(startInput);
                        if (start < 0 || start >= graph->getNodes()) throw invalid_argument("Wierzcholek musi byc w grafie");
                        graph->setStartingNode(start);
                    } catch (invalid_argument& e) {
                        cout << e.what() << endl;
                    }
                }

                delete[] distance;
                delete[] previous;
                distance = previous = nullptr;

                ShortestPathAlgorithms::djikstraAlgorithm(graph, timeMatrix, timeList, distance, previous);
                ShortestPathAlgorithms::printResultDistance(graph, graph->getNodes(), distance);
                ShortestPathAlgorithms::printResultPath(graph, graph->getNodes(), distance, previous);
                pause();
            }

            if (choice == 5) {
                if (graph == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    pause();
                    continue;
                }

                if (graph->getStartingNode() == -1) {
                    string startInput;
                    cout << "Podaj wierzcholek startowy: ";
                    cin >> startInput;
                    try {
                        int start = stoi(startInput);
                        if (start < 0 || start >= graph->getNodes()) throw invalid_argument("Wierzcholek musi byc w grafie");
                        graph->setStartingNode(start);
                    } catch (invalid_argument& e) {
                        cout << e.what() << endl;
                    }
                }

                delete[] distance;
                delete[] previous;
                distance = previous = nullptr;

                ShortestPathAlgorithms::Ford_BellmanAlgorithm(graph, timeMatrix, timeList, distance, previous);
                ShortestPathAlgorithms::printResultDistance(graph, graph->getNodes(), distance);
                ShortestPathAlgorithms::printResultPath(graph, graph->getNodes(), distance, previous);
                pause();
            }

            if (choice == 6) {
                if (distance != nullptr) ShortestPathAlgorithms::printResultDistance(graph, graph->getNodes(), distance);
                if (previous != nullptr) ShortestPathAlgorithms::printResultPath(graph, graph->getNodes(), distance, previous);
                else cout << "Brak wynikow.";
                pause();
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
            clearScreen();
            int choice = 0;
            bool directed = false;
            string input;
            if (mstSet == nullptr && graph != nullptr) {
                mstSet = new Edge*[graph->getNodes()]();
            }

            cout << "1. Wczytaj z pliku\n2. Wygeneruj losowy graf\n3. Wyswietl listowo i macierzowo\n4. Algorytm Prima\n5. Algorytm Kruskala\n6. Wyswietl wyniki\n7. Wyjdz\nWybierz opcje: ";
            cin >> input;

            try {
                choice = stoi(input);
                if (choice > 7 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
            } catch (invalid_argument& e) {
                cout << e.what() << endl;
                pause();
                continue;
            }

            if (choice == 1) {
                readFromFileGUI(graph);
                directed = isDirectedMatrix(graph);
                pause();
            }
            if (choice == 2) {
                while (true) {
                    generateRandomGraphMenu(graph, directed);
                    if (directed) {
                        cout << "Graf musi byc nieskierowany dla MST!";
                        continue;
                    }
                    break;
                }
                graph->printMatrix();
                graph->printList();
                pause();
            }
            if (choice == 3) {
                if (graph != nullptr) {
                    graph->printMatrix();
                    graph->printList();
                } else {
                    cout << "Najpierw stworz graf";
                }
                pause();
            }
            if (choice == 4) {
                if (directed) {
                    cout << "Graf musi byc nieskierowany";
                    pause();
                    continue;
                }
                if (mstSet == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    pause();
                    continue;
                }

                for (int i = 0; i < graph->getNodes(); ++i) {
                    delete mstSet[i];
                    mstSet[i] = nullptr;
                }

                // MSTAlgorithms::primAlgorithm(graph, timeMatrix, timeList, sum, mstSet);
                MSTAlgorithms::primAlgorithmList(graph, timeList, sum, mstSet);
                MSTAlgorithms::printResult(graph, sum, mstSet);
                pause();
            }

            if (choice == 5) {
                if (directed) {
                    cout << "Graf musi byc nieskierowany";
                    pause();
                    continue;
                }
                if (mstSet == nullptr) {
                    cout << "Stworz lub wczytaj graf\n";
                    pause();
                    continue;
                }

                for (int i = 0; i < graph->getNodes(); ++i) {
                    delete mstSet[i];
                    mstSet[i] = nullptr;
                }

                // MSTAlgorithms::kruskalAlgorithm(graph, timeMatrix, timeList, sum, mstSet);
                MSTAlgorithms::kruskalAlgorithmList(graph, timeMatrix, timeList, sum, mstSet);
                MSTAlgorithms::printResult(graph, sum, mstSet);
                pause();
            }

            if (choice == 6) {
                if (graph != nullptr && mstSet != nullptr) {
                    MSTAlgorithms::printResult(graph, sum, mstSet);
                }
                pause();
            }

            if (choice == 7) {
                delete[] mstSet;
                break;
            }
        }
    }

    static void readFromFileGUI(Graph* &graph) {
        string path;
        cout << "Podaj sciezke do pliku: ";
        cin >> path;

        int** graphData = Utilities::readFile(path);
        if (graph != nullptr) delete graph;
        graph = Utilities::createGraphFromFile(graphData);

        graph->printMatrix();
        graph->printList();

        int rows = graphData[0][0];
        for (int i = 0; i <= rows; ++i) delete[] graphData[i];
        delete[] graphData;
    }

    static void generateRandomGraphMenu(Graph* &graph, bool &directed) {
        string nodesInput, densityInput;
        char directedInput;
        int nodes, density;

        cout << "Podaj ilosc wierzcholkow: ";
        cin >> nodesInput;
        cout << "Podaj gestosc w %: ";
        cin >> densityInput;
        cout << "Czy skierowany [y/n]: ";
        cin >> directedInput;

        try {
            nodes = stoi(nodesInput);
            density = stoi(densityInput);
            if (density < 0 || density > 100) throw invalid_argument("Gestosc w % (0-100)");

            directed = (tolower(directedInput) == 'y');
        } catch (invalid_argument& e) {
            cout << e.what() << endl;
            return;
        }

        if (graph != nullptr) delete graph;
        directed ?
            Utilities::generateDirectedRandomGraph(graph, nodes, density) :
            Utilities::generateNonDirectedRandomGraph(graph, nodes, density);
    }

    static bool isDirectedMatrix(Graph* graph) {
        int nodes = graph->getNodes();
        int** matrix = graph->getAdjMatrix();

        for (int u = 0; u < nodes; ++u) {
            for (int v = 0; v < nodes; ++v) {
                if (matrix[u][v] != matrix[v][u]) return true;
            }
        }
        return false;
    }
};

#endif
