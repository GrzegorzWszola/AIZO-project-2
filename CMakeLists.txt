cmake_minimum_required(VERSION 3.28.3)
project(AIZO_Projekt_2)

set(CMAKE_CXX_STANDARD 20)

if(MINGW)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

add_executable(AIZO_Projekt_2 main.cpp
        GUI.h
        Utilities.h
        Graphs.h
        Algorythms/ShortestPathAlgorithms.h
        Algorythms/MST.h
        DataStructures/MinHeap.h
        DataStructures/DisjointSet.h
)