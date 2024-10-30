#include <iostream>
#include "./models/Item.cpp"
#include "./tads/HeapSort.cpp"

using namespace std;

int main()
{
    int size, id, price, lowerPrices;
    cin >> size;
    HeapSort<Item> * maxHeap = new HeapSort<Item>(size);

    for (int i = 0; i < size; i++)
    {
        cin >> id;
        cin >> price;
        Item item(id, price);
        maxHeap->insert(item);
    }

    Item *items = maxHeap->sort();
    cin >> lowerPrices;
    int * ids = new int[size]();
    int index = 0;
    while (lowerPrices > 0) {
        id = items[index].id;
        if (ids[id] == 0) {
            cout << items[index].id  << '\n';
            ids[id] = 1;
            lowerPrices--;
        }
        index++;
    }

    return 0;
}
