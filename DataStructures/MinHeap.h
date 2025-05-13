#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>

template<typename T>
class MinHeap {
    T** heapArr;
    int size;
    int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    //Function to rebuild heap after inserting element
    void heapifyUp(int i) {
        while (i != 0 && heapArr[parent(i)]->getCapacity() > heapArr[i]->getCapacity()) {
            std::swap(heapArr[i], heapArr[parent(i)]);
            i = parent(i);
        }
    }

    //Function to rebuild heap after taking min element
    void heapifyDown(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;

        if (left < size && heapArr[left]->getCapacity() < heapArr[smallest]->getCapacity())
            smallest = left;
        if (right < size && heapArr[right]->getCapacity() < heapArr[smallest]->getCapacity())
            smallest = right;

        if (smallest != i) {
            std::swap(heapArr[i], heapArr[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap(int cap) {
        this->capacity = cap;
        heapArr = new T*[cap];
        size = 0;
    }

    ~MinHeap() {
        for (int i = 0; i < size; i++) {
            delete heapArr[i];
        }
        delete[] heapArr;
    }

    //Function to get min value from heap
    T* getMinElement() {
        if (size <= 0) {
            throw std::runtime_error("Heap is empty");
        }
        if (size == 1)
            return heapArr[--size];

        T* root = heapArr[0];
        heapArr[0] = heapArr[--size];
        heapifyDown(0);
        return root;
    }

    //Function for inserting elements to min heap
    void insertElement(const T &value) {
        if (size == capacity) {
            std::cout << "Heap overflow\n";
            return;
        }

        heapArr[size] = new T(value);
        heapifyUp(size);
        size++;
    }

    bool empty() {
        if (size == 0) return true;
        return false;
    }

};

#endif //MINHEAP_H
