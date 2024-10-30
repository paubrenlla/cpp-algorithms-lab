#include <cassert>

#include "Heap.h"
#ifndef HEAP_SORT
#define HEAP_SORT
using namespace std;

template <class T>
class HeapSort: public Heap<T> {
private:
    int size{};
    int lastElement;
    T* elements;
    bool isFull () {
        return this->lastElement > this->size;
    }

    bool empty () {
        return this->lastElement == 0;
    }

    int getParentIndex(int childIndex) {
        return  (childIndex -1 ) / 2;
    }

    int getLeftChild(int parentIndex) {
        return  2 * parentIndex + 1;
    }

    int getRightChild(int parentIndex) {
        return  2 * parentIndex + 2;
    }

    void swap(int parentIndex, int childIndex) {
        T aux = this->elements[parentIndex];
        this->elements[parentIndex] = this->elements[childIndex];
        this->elements[childIndex] = aux;
    }

    void bubbleUp(int index) {
        if (index > 0) {
            int parentIndex = this->getParentIndex(index);
            T parent = this->elements[parentIndex];
            T child = this->elements[index];
            if (child > parent) {
                this->swap(parentIndex, index);
                this->bubbleUp(parentIndex);
            }
        }
    }

    void heapify(int size, int parentIndex)
    {
        int maximum = parentIndex;
        int rightIndex = this->getRightChild(parentIndex);
        int leftIndex = this->getLeftChild(parentIndex);

        if (leftIndex < size && this->elements[leftIndex] > this->elements[maximum]) {
            maximum = leftIndex;
        }

        if (rightIndex < size && this->elements[rightIndex] > this->elements[maximum]) {
            maximum = rightIndex;
        }

        if (maximum != parentIndex) {
            this->swap(parentIndex, maximum);
            heapify(size, maximum);
        }
    }

public:
    HeapSort(int size) {
        this->elements = new T[size];
        this->size = size;
        this->lastElement = 0;
    }

    void insert(T value) override {
        assert(!this->isFull());
        this->elements[this->lastElement] = value;
        this->bubbleUp(this->lastElement);
        ++this->lastElement;
    };

    T top() override {
        assert(!this->empty());
        return this->elements[0];
    }

    void remove() override {}

    T* sort() {
        assert(!this->empty());
        for (int i = this->size - 1; i > 0; i--) {
            T aux = this->elements[0];
            this->elements[0] = this->elements[i];
            this->elements[i] = aux;
            heapify(i, 0);
        }
        return this->elements;
    }
};

#endif