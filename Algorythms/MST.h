#ifndef MST_H
#define MST_H

#include "../Graphs.h"
#include "../DataStructures/MinHeap.h"
#include "../DataStructures/DisjointSet.h"

#define INF INT_MAX

class MSTAlgorithms {
public:
    static void primAlgorithm(Graph* graph, auto &timeMatrix, auto &timeList, int &sum, auto &mstSetResult) {
        int n = graph->getNodes();
        auto mstSet = new Edge*[n - 1];
        auto visited = new bool[n];
        MinHeap<Edge> minHeap(n*n);
        sum = 0;
        std::fill_n(visited, graph->getNodes(), false);

        auto start = std::chrono::high_resolution_clock::now();
        //Inserting dummy element at start
        minHeap.insertElement(Edge(-1, 0, 0));
        int setCounter = 0;
        //Iterating until the heap with edges is empty
        while (!minHeap.empty()) {
            //Creating variables for edge parameters
            auto edge = minHeap.getMinElement();
            int node = edge->getDestination();
            int weight = edge->getCapacity();

            //Checking if node is already in the mst
            if (visited[node]) {
                delete edge;
                continue;
            }
            //If not setting it to visited and adding the edge weight to the sum
            visited[node] = true;
            sum += weight;
            int src = edge->getSource();
            //Adding edge to the mstSert
            if (src != -1) {mstSet[setCounter++] = new Edge(src, node, weight);}
            //Iterating through edges of the current node
            for (int i = 0; i < n; i++) {
                int eWeight = graph->getAdjMatrix()[node][i];
                //If the edge exists and the node adjecent is not in visited add it to the heap
                if (eWeight != 0) {
                    if (!visited[i]) {
                        minHeap.insertElement(Edge(node, i, eWeight));
                    }
                }
            }
            delete edge;
        }

        auto end = std::chrono::high_resolution_clock::now();
        timeMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        for (int i = 0; i < n - 1; ++i) {
            mstSetResult[i] = new Edge(*mstSet[i]);
            delete mstSet[i];
        }

        delete[] mstSet;
        delete[] visited;
    }

    static void primAlgorithmList(Graph* graph, auto &timeList, int &sum, auto &mstSetResult) {
        int n = graph->getNodes();
        auto mstSet = new Edge*[n - 1];
        auto visited = new bool[n];
        MinHeap<Edge> minHeap(n*n);
        sum = 0;
        std::fill_n(visited, graph->getNodes(), false);
        auto start = std::chrono::high_resolution_clock::now();

        //Inserting dummy element at start
        minHeap.insertElement(Edge(-1, 0, 0));
        int setCounter = 0;
        //Iterating until the heap with edges is empty
        while (!minHeap.empty()) {
            //Creating variables for edge parameters
            auto edge = minHeap.getMinElement();
            int node = edge->getDestination();
            int weight = edge->getCapacity();

            //Checking if node is already in the mst
            if (visited[node]){ 
                delete edge;
                continue;
            }
            //If not setting it to visited and adding the edge weight to the sum
            visited[node] = true;
            sum += weight;
            int src = edge->getSource();
            //Adding edge to the mstSert
            if (src != -1) {mstSet[setCounter++] = new Edge(src, node, weight);}
            //Iterating through edges of the current node
            for (int i = 0; i < graph->getEdgeCounterList()[node]; i++) {
                int eWeight = graph->getAdjList()[node][i]->getCapacity();
                int neighbour = graph->getAdjList()[node][i]->getDestination();
                //If the edge exists and the node adjecent is not in visited add it to the heap
                if (eWeight != 0) {
                    if (!visited[neighbour]) {
                        minHeap.insertElement(Edge(node, neighbour, eWeight));
                    }
                }
            }
            delete edge;
        }
        auto end = std::chrono::high_resolution_clock::now();
        timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        for (int i = 0; i < n - 1; ++i) {
            mstSetResult[i] = new Edge(*mstSet[i]);
            delete mstSet[i];
        }

        delete[] mstSet;
        delete[] visited;
    }

    static void kruskalAlgorithm(Graph* graph, auto &timeMatrix, auto &timeList, int &sum, auto &mstSetResult) {
        int n = graph->getNodes();
        auto mstSet = new Edge*[n - 1];
        auto visited = new bool[n];
        MinHeap<Edge> edgeHeap(graph->getEdgeCounter());
        sum = 0;
        int setCounter = 0;
        std::fill_n(visited, graph->getNodes(), false);

        //Adding all edges into the list and sorting them at the same time
        if(!graph->getDirected()){
            for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    int weight = graph->getAdjMatrix()[i][j];
                    if (weight != 0) {
                        edgeHeap.insertElement(Edge(i, j, weight));
                    }
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int weight = graph->getAdjMatrix()[i][j];
                    if (weight != 0) {
                        edgeHeap.insertElement(Edge(i, j, weight));
                    }
                }
            }
        }
        
        //Creating disjoint set with max of n nodes
        DisjointSet dsSet(n);

        //Iterating through all edges in the sorted edges
        while (!edgeHeap.empty()){
            Edge* smallestEdge = edgeHeap.getMinElement();
            int u = smallestEdge->getSource();
            int v = smallestEdge->getDestination();
            int weight = smallestEdge->getCapacity();

            //Checking if they are in the same set if not unionising
            if (dsSet.find(u) != dsSet.find(v)) {
                sum += weight;
                mstSetResult[setCounter++] = new Edge(u, v, weight);
                dsSet.unionBySize(u, v);
            }

            delete smallestEdge;
        }

        delete[] visited;
        delete[] mstSet;
    }

    static void kruskalAlgorithmList(Graph* graph, auto &timeMatrix, auto &timeList, int &sum, auto &mstSetResult) {
        int n = graph->getNodes();
        auto mstSet = new Edge*[n - 1];
        auto visited = new bool[n];
        MinHeap<Edge> edgeHeap(graph->getEdgeCounter());
        sum = 0;
        int setCounter = 0;
        std::fill_n(visited, graph->getNodes(), false);

        //Adding all edges into the list and sorting them at the same time
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < graph->getEdgeCounterList()[i]; j++) {
                int weight = graph->getAdjList()[i][j]->getCapacity();
                int v = graph->getAdjList()[i][j]->getDestination();
                int u = graph->getAdjList()[i][j]->getSource();
                
                if (u < v) {
                    edgeHeap.insertElement(Edge(u, v, weight));
                }
            }
        }
        

        //Creating disjoint set with max of n nodes
        DisjointSet dsSet(n);

        while (!edgeHeap.empty()){
            Edge* smallestEdge = edgeHeap.getMinElement();
            int u = smallestEdge->getSource();
            int v = smallestEdge->getDestination();
            int weight = smallestEdge->getCapacity();

            //Checking if they are in the same set if not unionising
            if (dsSet.find(u) != dsSet.find(v)) {
                sum += weight;
                mstSetResult[setCounter++] = new Edge(u, v, weight);
                dsSet.unionBySize(u, v);
            }

            delete smallestEdge;
        }

        delete[] visited;
        delete[] mstSet;
    }

    static void printResult(Graph* graph, int sum, auto mstSet) {
        std::cout << sum << std::endl;
        for (int i = 0; i < graph->getNodes() - 1; i++) {
            std::cout << mstSet[i]->getSource() << " " << mstSet[i]->getDestination() << " " << mstSet[i]->getCapacity() << " " << std::endl;
        }
    }
};

#endif //MST_H


