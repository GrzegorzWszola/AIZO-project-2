cmake_minimum_required(VERSION 3.30)
project(AIZO_Projekt_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(AIZO_Projekt_2 main.cpp
        GUI.h
        Utilities.h
        Graphs.h
        Algorythms/ShortestPathAlgorithms.h
        Algorythms/MST.h
        DataStructures/MinHeap.h
        DataStructures/SortedEdgeList.h
)
