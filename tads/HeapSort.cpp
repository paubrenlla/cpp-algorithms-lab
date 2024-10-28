#ifndef HEAP_SORT
#define HEAP_SORT
#include <string>
using namespace std;

template <class T>
class HeapSort
{
private:
    int getLeftChild(int parentIndex) {
      return  2 * parentIndex + 1;
    }

    int getRightChild(int parentIndex) {
        return  2 * parentIndex + 2;
    }

    void heapify(int array[], int n, int i)
    {
        int temp, maximum, left_index, right_index;

        // currently assuming i postion to
        // be holding the largest value
        maximum = i;

        right_index = this->getRightChild(i);

        left_index = this->getLeftChild(i);

        // if left index value is grater than the current index
        // value
        if (left_index < n && array[left_index] > array[maximum]) {
            maximum = left_index;
        }
        // if right index value is grater than the current index
        // value
        if (right_index < n && array[right_index] > array[maximum]) {
            maximum = right_index;
        }

        // checking if we needed swaping the elements or not
        if (maximum != i) {
            temp = array[i];
            array[i] = array[maximum];
            array[maximum] = temp;
            heapify(array, n, maximum);
        }
    }

public:
    HeapSort(T array[], int size) {
      int temp;
        for (int index = size / 2 - 1; index >= 0; index--) {
            heapify(array, size, index);
        }

        for (int i = size - 1; i > 0; i--) {
            temp = array[0];
            array[0] = array[i];
            array[i] = temp;
            heapify(array, i, 0);
        }
    }
};

#endif
