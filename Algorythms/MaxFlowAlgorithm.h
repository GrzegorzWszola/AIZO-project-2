#ifndef MAXFLOWALGORITHM_H
#define MAXFLOWALGORITHM_H

#include "../Graphs.h"
#define INF INT_MAX

class MaxFlowAlgorithm {
    static void DFS(Graph* graph) {
        int n = graph->getNodes();
        auto visited = new int[n];
        std::fill_n(visited, n, 0);


    }

public:
    static void FordFulkerson(Graph* graph, auto &timeMatrix, auto &timeList, auto &distance, auto &previous) {
        int source = graph->getStartingNode();
        int sink = graph->getEndingNode();


    }
};

#endif //MAXFLOWALGORITHM_H
