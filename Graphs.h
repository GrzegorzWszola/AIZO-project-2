#ifndef GRAPHS_H
#define GRAPHS_H
#include <iostream>

class Edge {
    int source;
    int destination;
    int capacity;

public:
    Edge(int src, int dest, int cap) {
        source = src;
        destination = dest;
        capacity = cap;
    }

    Edge(const Edge &edge) {
        source = edge.source;
        destination = edge.destination;
        capacity = edge.capacity;
    }

    int getDestination() {return destination;}
    int getCapacity() {return capacity;}
    int getSource() {return source;}
    void setCapacity(int cap) {capacity = cap;}

};

class Graph {
    int edges;
    int nodes;
    int** adjMatrix;
    Edge*** adjList;
    int* edgeCounter;
    int startingNode;
    int endingNode;
    bool directed;

public:
    Graph(int numberEdges, int numberNodes, int sNode, int eNode, bool directedI) {
        edges = numberEdges;
        nodes = numberNodes;
        startingNode = sNode;
        endingNode = eNode;
        adjMatrix = new int*[nodes];
        for (int i = 0; i < nodes; ++i) {
            adjMatrix[i] = new int[nodes]{0};
        }
        adjList = new Edge**[nodes];
        for (int i = 0; i < nodes; ++i) {
            adjList[i] = new Edge*[nodes];
        }
        edgeCounter = new int[nodes]{0};
        directed = directedI;
    }

    void addEdge(int source, int destination, int capacity) {
        //Adding edge to matrix
        adjMatrix[source][destination] = capacity;

        //Adding edge to list
        adjList[source][edgeCounter[source]] = new Edge{source, destination, capacity};
        edgeCounter[source]++;
    }

    void removeEdge(int source, int destination) {
        // Usunięcie z macierzy sąsiedztwa
        adjMatrix[source][destination] = 0;

        // Usunięcie z listy sąsiedztwa
        for (int i = 0; i < edgeCounter[source]; ++i) {
            if (adjList[source][i] && adjList[source][i]->getDestination() == destination) {
                delete adjList[source][i];
                // Przesuń elementy w lewo
                for (int j = i; j < edgeCounter[source] - 1; ++j) {
                    adjList[source][j] = adjList[source][j + 1];
                }
                adjList[source][edgeCounter[source] - 1] = nullptr;
                edgeCounter[source]--;
                break;
            }
        }
    }

    void printMatrix() {
        std::cout << "Reprezentacja macierzowa: " << std::endl;
        for (int i = 0; i <= nodes; i++) {
            for (int j = 0; j <= nodes; j++) {
                if (i == 0 && j == 0) {
                    std::cout << "  ";
                }else if (i == 0) {
                    printf("___%2d", j-1);
                } else if (j == 0) {
                    printf("%2d|", i-1);
                } else {
                    printf(" %3d ", adjMatrix[i-1][j-1]);
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void printList() {
        std::cout << "Reprezentacja listowa(\'wierzcholek\':\'pojemnosc/waga\'):" << std::endl;
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j <= edgeCounter[i]; j++) {
                if (j == 0) {
                    printf("%2d|", i);
                } else {
                    printf("%2d:%2d ", adjList[i][j-1]->getDestination(), adjList[i][j-1]->getCapacity());
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void setStartingNode(int value) {
        if (value < 0 || value > nodes) {throw std::invalid_argument("Wybierz wartosc pomiedzy 0 a liczbą wierzcholkow");}
        startingNode = value;
    }

    void setEndingNode(int value) {
        if (value < 0 || value > nodes) {throw std::invalid_argument("Wybierz wartosc pomiedzy 0 a liczbą wierzcholkow");}
        endingNode = value;
    }

    int getStartingNode() const {return startingNode;}
    int getEndingNode() {return endingNode;}
    int** getAdjMatrix() {return adjMatrix;}
    Edge*** getAdjList() {return adjList;}
    int getNodes() {return nodes;}
    int* getEdgeCounterList(){return edgeCounter;}
    int getEdgeCounter() {
        int returnValue = 0;
        for (int i = 0; i < nodes; i++) {
            returnValue += edgeCounter[i];
        }
        if (!directed) {
            return returnValue/2;
        }
        return returnValue;
    }

    ~Graph() {
        for (int i = 0; i < nodes; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;

        for (int i = 0; i < nodes; ++i) {
            for (int j = 0; j < edgeCounter[i]; ++j) {
                delete adjList[i][j];
            }
            delete[] adjList[i];
        }
        delete[] adjList;
        delete[] edgeCounter;
    }
};


#endif
