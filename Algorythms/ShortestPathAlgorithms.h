#ifndef SHORTESTPATHALGORYTHMS_H
#define SHORTESTPATHALGORYTHMS_H
#include <iostream>

#include "../Graphs.h"
#define INF INT_MAX

class ShortestPathAlgorithms {
    static void printPath(int node, int* &previous) {
        if (previous[node] == -1) {
            std::cout << node;
            return;
        }
        printPath(previous[node], previous);
        std::cout << " -> " << node;
    }

public:
    static void djikstraAlgorithm(Graph* graph, auto &timeMatrix, auto &timeList, int* &distance, int* &previous) {
        int nodes = graph->getNodes();
        bool* visited = new bool[nodes]{false};
        distance = new int[graph->getNodes()];
        previous = new int[graph->getNodes()];
        auto start = std::chrono::high_resolution_clock::now();

        std::fill_n(distance, graph->getNodes(), INF);
        std::fill_n(previous, graph->getNodes(), -1);
        distance[graph->getStartingNode()] = 0;

        for (int i = 0; i < nodes; i++) {
            //Getting current node
            int nodeIndex = -1;
            int shortestDistance = INT_MAX;
            for (int j = 0; j < nodes; j++) {
                if (!visited[j] && shortestDistance > distance[j]) {
                    shortestDistance = distance[j];
                    nodeIndex = j;
                }
            }

            //No reacheable nodes
            if (nodeIndex == -1) {break;}
            //Setting current node as visited
            visited[nodeIndex] = true;

            //Looping through the adjecent nodes
            for (int v = 0; v < nodes; v++) {
                int weight = graph->getAdjMatrix()[nodeIndex][v];

                //Adding weight to the neighbours and updating previous list
                if (weight > 0 && !visited[v] && distance[nodeIndex] != INT_MAX && distance[nodeIndex] + weight < distance[v]) {
                    distance[v] = distance[nodeIndex] + weight;
                    previous[v] = nodeIndex;
                }
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        timeMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        //Resetting the values
        for (int i = 0; i < nodes; i++) {previous[i] = -1;}
        for (int i = 0; i < nodes; i++) {visited[i] = false;}
        for (int i = 0; i < nodes; i++) {distance[i] = INT_MAX;}
        distance[graph->getStartingNode()] = 0;
        start = std::chrono::high_resolution_clock::now();
        //Same algorythm just changing the type of representation
        for (int i = 0; i < nodes; i++) {
            int nodeIndex = -1;
            int shortestDistance = INT_MAX;
            for (int j = 0; j < nodes; j++) {
                if (!visited[j] && shortestDistance > distance[j]) {
                    shortestDistance = distance[j];
                    nodeIndex = j;
                }
            }

            if (nodeIndex == -1) {break;}
            visited[nodeIndex] = true;

            for (int v = 0; v < graph->getEdgeCounterList()[nodeIndex]; v++) {
                int neighbor = graph->getAdjList()[nodeIndex][v]->getDestination();
                int weight = graph->getAdjList()[nodeIndex][v]->getCapacity();

                if (weight > 0 && !visited[neighbor] && distance[nodeIndex] != INT_MAX && distance[nodeIndex] + weight < distance[neighbor]) {
                    distance[neighbor] = distance[nodeIndex] + weight;
                    previous[neighbor] = nodeIndex;
                }
            }
        }
        end = std::chrono::high_resolution_clock::now();
        timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        printResultDistance(graph, nodes, distance);
        printResultPath(graph, nodes, distance, previous);

        delete[] visited;
    }

    static void Ford_BellmanAlgorithm(Graph* graph, auto &timeMatrix, auto &timeList, int* &distance, int* &previous) {
        distance = new int[graph->getNodes()];
        previous = new int[graph->getNodes()];
        //Setting up the table
        std::fill_n(distance, graph->getNodes(), INF);
        std::fill_n(previous, graph->getNodes(), -1);
        distance[graph->getStartingNode()] = 0;

        auto start = std::chrono::high_resolution_clock::now();
        //Iterating Vertex - 1 times to avoid negative loops
        for (int i = 0; i < graph->getNodes() - 1; i++) {
            for (int u = 0; u < graph->getNodes(); u++) {
                for (int v = 0; v < graph->getNodes(); v++) {
                    //Getting the weight of the edge to add
                    int weight = graph->getAdjMatrix()[u][v];
                    //Checking if the edge exists, if the path to the node is known and if the path is shorter
                    if (distance[u] != INF && weight != 0 && distance[v] > distance[u] + weight) {
                        distance[v] = distance[u] + weight;
                        previous[v] = u;
                    }
                }
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        timeMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        //Setting up the table
        std::fill_n(distance, graph->getNodes(), INF);
        std::fill_n(previous, graph->getNodes(), -1);
        distance[graph->getStartingNode()] = 0;

        start = std::chrono::high_resolution_clock::now();
        //Iterating Vertex - 1 times to avoid negative loops
        for (int i = 0; i < graph->getNodes() - 1; i++) {
            for (int u = 0; u < graph->getNodes(); u++) {
                for (int j = 0; j < graph->getEdgeCounterList()[u]; j++) {
                    //Getting the weight of the edge to add
                    int v = graph->getAdjList()[u][j]->getDestination();
                    int weight = graph->getAdjList()[u][j]->getCapacity();
                    //Checking if the edge exists, if the path to the node is known and if the path is shorter
                    if (distance[u] != INF && weight != 0 && distance[v] > distance[u] + weight) {
                        distance[v] = distance[u] + weight;
                        previous[v] = u;
                    }
                }
            }
        }
        end = std::chrono::high_resolution_clock::now();
        timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        printResultDistance(graph, graph->getNodes(), distance);
        printResultPath(graph, graph->getNodes(), distance, previous);
    }

    static void changeNegativeToPositive(Graph* graph) {
        //Changing negative value to its absolute in matrix
        for (int i = 0; i < graph->getNodes(); i++) {
            for (int j = 0; j < graph->getNodes(); j++) {
                if (graph->getAdjMatrix()[i][j] < 0) {
                    graph->getAdjMatrix()[i][j] = abs(graph->getAdjMatrix()[i][j]);
                }
            }
        }

        //Changing negative values to its absolute in list
        for (int i = 0; i < graph->getNodes(); i++) {
            for (int j = 0; j < graph->getEdgeCounterList()[i]; j++) {
                if (graph->getAdjList()[i][j]->getCapacity() < 0) {
                    graph->getAdjList()[i][j]->setCapacity(abs(graph->getAdjList()[i][j]->getCapacity()));
                }
            }
        }
    }

    static void printResultDistance(Graph* &graph, int nodes, int* &distance) {
        std::cout << "Odleglosc od: " << graph->getStartingNode() << ", do kolejnych sasiadow: " << std::endl;
        for (int i = 0; i < nodes; i++) {
            std::cout << i << ": ";
            if (distance[i] == INT_MAX)
                std::cout << "unreachable\n";
            else
                std::cout << distance[i] << "\n";
        }
    }

    static void printResultPath(Graph* &graph, int nodes, int* &distance, int* &previous) {
        std::cout << "Sciezka od: " << graph->getStartingNode() << ", do kolejnych wierzcholkow" << std::endl;
        for (int i = 0; i < nodes; i++) {
            std::cout << i << ": ";
            if (distance[i] == INT_MAX) {
                std::cout << "unreachable\n";
            } else {
                printPath(i, previous);
                std::cout << "\n";
            }
        }
    }
};

#endif //SHORTESTPATHALGORYTHMS_H
