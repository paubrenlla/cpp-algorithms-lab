#include <iostream>
#include "./models/Item.cpp"

using namespace std;

int getLeftChild(int parentIndex) {
    return  2 * parentIndex + 1;
}

int getRightChild(int parentIndex) {
    return  2 * parentIndex + 2;
}

void heapify(Item array[], int n, int i)
{
    Item temp;
    int maximum, left_index, right_index;

    // currently assuming i postion to
    // be holding the largest value
    maximum = i;

    right_index = getRightChild(i);

    left_index = getLeftChild(i);

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

void heapSort(Item array[], int size) {
    Item temp;
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


int main()
{
    int size, id, price;
    cin >> size;
    Item *items = new Item[size]();

    for (int i = 0; i < size; i++)
    {
        cin >> id;
        cin >> price;
        Item item(id, price);
        items[i] = item;
    }

    printf("Original Array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", items[i].id);
    }

    heapSort(items, size);

    printf("Array after performing heap sort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", items[i].id);
    }

    return 0;
}