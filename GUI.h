#ifndef GUI_H
#define GUI_H
#include <iostream>

#include "Graphs.h"
#include "Utilities.h"

using namespace std;

class GUI {
public:
    static void entryMessage(Graph* &graph) {
        while (true) {
            system("cls");
            string input;
            int choice = 0;
            cout << "1.Najkrotsza sciezka\n2.Drzewo rozpinajace\n3.Maksymalny przeplyw\nWybierz problem: ";
            cin >> input;

            try {
                choice = stoi(input);
                if (choice > 3 || choice == 0) throw invalid_argument("Wybierz mozliwa liczbe");
            } catch (invalid_argument& e) {
                cout << e.what() << endl;
                system("pause");
            }

            if (choice == 1) {
                algorythmMenu(graph, choice);
            }
            if (choice == 2) {

            }
            if (choice == 3) {

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
        graph = Utilities::createGraph(graphData);

        //Printing the graph representations (matrix and list)
        graph->printMatrix();
        graph->printList();

        //Dealocating memory from data graph list
        for (int i = 0; i <= graphData[0][0]; i++) {
            delete[] graphData[i];
        }
        delete[] graphData;
    }

    static void generateRandomGraphNonDirected(Graph* &graph, int choice) {
        string nodesInput, densityInput;
        int nodes, density;
        cout << "Podaj ilosc wiercholkow: ";
        cin >> nodesInput;
        cout << "Podaj gestosc w %: ";
        cin >> densityInput;

        try {
            nodes = stoi(nodesInput);
            density = stoi(densityInput);
            if (density > 100 || density < 0) throw invalid_argument("Dane musza byc w procentach");
        } catch (invalid_argument& e) {
            cout << e.what() << endl;
            return;
        }

        //Generating random non directed graph
        if (graph != nullptr) {
            delete graph;
            graph = nullptr;
        }
        Utilities::generateNonDirectedRandomGraph(graph, nodes, density, choice);
        graph->printMatrix();
        graph->printList();
    }

    static void algorythmMenu(Graph* &graph, int choice1) {
        while (true) {
            system("cls");
            string input;
            int choice = 0;
            if (choice1 == 1) {
                cout << "1.Wczytaj z pliku\n2.Wygeneruj losowy graf\n3.Wyswietl listowo i macierzowo\n4.Algorytm Djikstry\n5.Bellman-Ford\n6.Wyswietl wyniki\n7.Wyjdz\nWybierz opcje: ";
            }
            if (choice1 == 2) {
                cout << "1.Wczytaj z pliku\n2.Wygeneruj losowy graf\n3.Wyswietl listowo i macierzowo\n4.Algorytm Prima\n5.Algorytm Kruskala\n6.Wyswietl wyniki\n7.Wyjdz\nWybierz opcje: ";
            }
            if (choice1 == 3) {
                cout << "1.Wczytaj z pliku\n2.Wygeneruj losowy graf\n3.Wyswietl listowo\n4.Wyswietl macierzowo\n5.Algorytm Forda-Flukersona\n6.Wyswietl wyniki\n7.Wyjdz\nWybierz opcje: ";
            }
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
                if (choice1 == 1)
                generateRandomGraphNonDirected(graph, choice);
                system("pause");
            }
            if (choice == 7) {
                break;
            }
        }
    }
};

#endif
