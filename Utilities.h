#ifndef UTILITIES_H
#define UTILITIES_H
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <random>


#include "Graphs.h"


class Utilities {
    static void createNonDirectedGraph(Graph* &graph, int nodes, int pDensity, bool** &isInSpanningTree, bool** &edgesList, int minCap, int maxCap) {
        //Number of edges based on number of nodes and density percentage
        int maxEdges = (nodes*(nodes-1))/2;
        int edges = (int)(pDensity * maxEdges / 100.0);
        int edgeCounter = 0;
        std::random_device rd;
        std::mt19937 gen(rd());

        //Allocating memory
        graph = new Graph(edges, nodes, 0, 0);

        //Creating spanning tree
        for (int i = 0; i < nodes - 1; i++) {
            int cap = std::uniform_int_distribution<>(minCap, maxCap)(gen);
            graph->addEdge(i, i + 1, cap);
            graph->addEdge(i + 1, i, cap);
            edgesList[i][i+1] = true;
            edgesList[i+1][i] = true;
            isInSpanningTree[i][i+1] = true;
            isInSpanningTree[i+1][i] = true;
            edgeCounter++;
        }

        //Creating random edges
        while (edgeCounter < edges) {
            int randomNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
            int randomNextNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
            int cap = std::uniform_int_distribution<>(minCap, maxCap)(gen);
            //Check for loops and exisitng edges
            if (randomNode == randomNextNode || edgesList[randomNode][randomNextNode]|| edgesList[randomNextNode][randomNode]) continue;

            graph->addEdge(randomNode, randomNextNode, cap);
            graph->addEdge(randomNextNode, randomNode, cap);
            //Adding edge to list
            edgesList[randomNode][randomNextNode] = true;
            edgesList[randomNextNode][randomNode] = true;
            edgeCounter++;
        }
    }

    static void createDirectedGraph(Graph* &graph, int nodes, int pDensity, bool** &isInSpanningTree, bool** &edgesList, int minCap, int maxCap) {
        int maxEdges = nodes*(nodes-1);
        int edges = (int)round(maxEdges * pDensity / 100.0);
        int edgeCounter = 0;
        std::random_device rd;
        std::mt19937 gen(rd());

        //Allocating memory
        graph = new Graph(edges, nodes, 0, 0);

        for (int i = 0; i < nodes - 1; i++) {
            int cap = std::uniform_int_distribution<>(minCap, maxCap)(gen);
            graph->addEdge(i, i + 1, cap);
            edgesList[i][i+1] = true;
            isInSpanningTree[i][i+1] = true;
            edgeCounter++;
        }

        //Creating random edges
        while (edgeCounter < edges) {
            int randomNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
            int randomNextNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
            int cap = std::uniform_int_distribution<>(minCap, maxCap)(gen);
            //Check for loops and exisitng edges
            if (randomNode == randomNextNode || edgesList[randomNode][randomNextNode]) continue;

            graph->addEdge(randomNode, randomNextNode, cap);
            //Adding edge to list
            edgesList[randomNode][randomNextNode] = true;
            edgeCounter++;
        }
    }

public:
    static Graph* createGraph(int** data) {
        int edges = data[0][0], nodes = data[0][1], startingNode = data[0][2], endingNode = data[0][3];
        auto graphTest = new Graph(edges, nodes, startingNode, endingNode);
        //If the file structure is mst create non directed graph
        if (startingNode == -1 && endingNode == -1) {
            for (int i = 1; i <= edges; ++i) {
                graphTest->addEdge(data[i][0], data[i][1], data[i][2]);
                graphTest->addEdge(data[i][1], data[i][0], data[i][2]);
            }
        //Create directed graph
        } else {
            for (int i = 1; i <= edges; ++i) {
                graphTest->addEdge(data[i][0], data[i][1], data[i][2]);
            }
        }
        return graphTest;
    }

    static int** readFile(std::string fileName) {
        if (!fileName.empty() && fileName.front() == '"' && fileName.back() == '"') {
            fileName = fileName.substr(1, fileName.length() - 2);
        }
        std::ifstream file(fileName);
        std::string line, edges;
        std::string tempString;
        int** list;

        if (!file) {
            std::cout << "Nie mozna otworzyc pliku!\n";
        }

        std::getline(file, line);
        std::istringstream iss(line);
        iss >> tempString;
        list = new int*[std::stoi(tempString) + 1];
        list[0] = new int[4];
        list[0][0] = std::stoi(tempString);
        for (int i = 1; i < std::stoi(tempString)+1; i++) {
            list[i] = new int[3];
        }

        int i = 1;
        while (iss >> tempString) {
            list[0][i] = std::stoi(tempString);
            i++;
        }
        if (i == 2) {
            list[0][2] = -1;
            list[0][3] = -1;
        }
        if (i == 3) {
            list[0][3] = -1;
        }

        i = 1;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> list[i][0] >> list[i][1] >> list[i][2];
            i++;
        }
        return list;
    }

    static void generateNonDirectedRandomGraph(Graph* &graph, int nodes, int pDensity, int choice) {
        bool** edgesList = new bool*[nodes];
        for (int i = 0; i < nodes; i++) {
            edgesList[i] = new bool[nodes]{false};
        }
        bool** inSpanningTree = new bool*[nodes];
        for (int i = 0; i < nodes; i++) {
            inSpanningTree[i] = new bool[nodes]{false};
        }

        int maxCap, minCap;
        if (choice == 1) {}

        //If density is 99% remove 1% from full graph
        if (pDensity == 99) {
            pDensity = 100;
            std::random_device rd;
            std::mt19937 gen(rd());

            //Creating full graph
            createNonDirectedGraph(graph, nodes, pDensity, inSpanningTree, edgesList, minCap, maxCap);
            int maxEdges = (nodes * (nodes - 1)) / 2;
            //Calculating edges to remove
            int edgesToRemove = (int)(maxEdges / 100.0);
            int j = 0;
            while (j < edgesToRemove) {
                int randomNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
                int randomNextNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
                //Check if edge is not part of spanning tree to not delete important nodes
                if (inSpanningTree[randomNode][randomNextNode] || inSpanningTree[randomNextNode][randomNode]) continue;
                //Check to see if the edge exists within the graph
                if (!edgesList[randomNode][randomNextNode] || !edgesList[randomNextNode][randomNode]) continue;
                graph->removeEdge(randomNode, randomNextNode);
                graph->removeEdge(randomNextNode, randomNode);
                edgesList[randomNode][randomNextNode] = false;
                edgesList[randomNextNode][randomNode] = false;
                j++;
            }
        } else {
            createNonDirectedGraph(graph, nodes, pDensity, inSpanningTree, edgesList, minCap, maxCap);
        }
        //Deallocating memory
        for (int i = 0; i < nodes; i++) {
            delete[] edgesList[i];
        }
        delete[] edgesList;
        for (int i = 0; i < nodes; i++) {
            delete[] inSpanningTree[i];
        }
        delete[] inSpanningTree;
    }

    static void generateDirectedRandomGraph(Graph* &graph, int nodes, int pDensity, int choice) {
        bool** edgesList = new bool*[nodes];
        for (int i = 0; i < nodes; i++) {
            edgesList[i] = new bool[nodes]{false};
        }
        bool** inSpanningTree = new bool*[nodes];
        for (int i = 0; i < nodes; i++) {
            inSpanningTree[i] = new bool[nodes]{false};
        }

        int maxCap, minCap;
        if (choice == 1) {}

        //If density is 99% remove 1% from full graph
        if (pDensity == 99) {
            pDensity = 100;
            std::random_device rd;
            std::mt19937 gen(rd());

            //Creating full graph
            createDirectedGraph(graph, nodes, pDensity, inSpanningTree, edgesList, minCap, maxCap);
            int maxEdges = (nodes * (nodes - 1)) / 2;
            //Calculating edges to remove
            int edgesToRemove = (int)(maxEdges / 100.0);
            int j = 0;
            while (j < edgesToRemove) {
                int randomNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
                int randomNextNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
                //Check if edge is not part of spanning tree to not delete important nodes
                if (inSpanningTree[randomNode][randomNextNode] || inSpanningTree[randomNextNode][randomNode]) continue;
                //Check to see if the edge exists within the graph
                if (!edgesList[randomNode][randomNextNode] || !edgesList[randomNextNode][randomNode]) continue;
                graph->removeEdge(randomNode, randomNextNode);
                edgesList[randomNode][randomNextNode] = false;
                j++;
            }
        } else {
            createDirectedGraph(graph, nodes, pDensity, inSpanningTree, edgesList, minCap, maxCap);
        }
        //Deallocating memory
        for (int i = 0; i < nodes; i++) {
            delete[] edgesList[i];
        }
        delete[] edgesList;
        for (int i = 0; i < nodes; i++) {
            delete[] inSpanningTree[i];
        }
        delete[] inSpanningTree;
    }
};

#endif
