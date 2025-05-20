#ifndef SORTEDEDGELIST_H
#define SORTEDEDGELIST_H
#include <iostream>
#include <ostream>

template<typename T>
class SortedEdgeList {
    T** edgeList;
    int size;
    int initialCapacity;

    //Function to sort newly added element by insertion sort
    void sortArray(int arrSize) {
        for (int i = 1; i < arrSize; i++) {
            T* key = edgeList[i];
            int j = i - 1;

            while (j >= 0 && edgeList[j]->getCapacity() < key->getCapacity()) {
                edgeList[j + 1] = edgeList[j];
                j--;
            }

            edgeList[j + 1] = key;
        }
    }

public:
    SortedEdgeList(int cap) {
        initialCapacity = cap;
        edgeList = new T*[initialCapacity];
        size = 0;
    }

    ~SortedEdgeList() {
        for (int i = 0; i < size; i++) {
            delete edgeList[i];
        }
        delete[] edgeList;
    }

    void addEdge(const T &edge) {
        if (size >= initialCapacity) {
            std::cout<<"Overflow"<<std::endl;
            return;
        }

        edgeList[size] = new T(edge);
        size++;
        sortArray(size);
    }

    T* removeEdge(int index) {
        T* returnVal = edgeList[index];
        for (int i = index; i < size - 1; i++) {
            edgeList[i] = edgeList[i + 1];
        }
        edgeList[size - 1] = nullptr;
        size--;
        sortArray(size);
        return returnVal;
    }

    T* getSmallestElement() {
        if (size <= 0) return nullptr;

        T* copy = new T(*edgeList[size - 1]);
        delete edgeList[size - 1];
        edgeList[size - 1] = nullptr;
        size--;
        return copy;
    }
    void printEdges() {
        std::cout<<"Edges: " << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "Src: " << edgeList[i]->getSource() << " Dest: " << edgeList[i]->getDestination() << " Weight: " << edgeList[i]->getCapacity() << std::endl;
        }
    }

    bool isEmpty() {
        if (size != 0) {
            return false;
        }
        return true;
    }
};

#endif //SORTEDEDGELIST_H
