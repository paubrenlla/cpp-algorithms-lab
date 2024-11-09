#ifndef ITERATOR
#define ITERATOR

#include <cassert>

template <class T>
class Iterator
{
private:
    T* current;

public:
    Iterator(T* head) : current(head) {}

    bool hasNext() 
    {
        return current != NULL;
    }

    T next() 
    {
        T* temp = current;
        current = current->siguiente;
        return *temp;
    }
};

#endif
