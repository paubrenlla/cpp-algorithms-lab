#ifndef ITERATOR_IMP
#define ITERATOR_IMP

#include "Iterator.h"
#include <cassert>

template <class T>
class IteratorImp : public Iterator<T>
{
private:
    const T collection;
    size_t index;

public:
    IteratorImp(const T col) 
        : collection(col), index(0) {}

    bool hasNext() override
    {
        return index < collection.size();
    }

    T next() override
    {
        return collection[index++]; 
    }
};

#endif
