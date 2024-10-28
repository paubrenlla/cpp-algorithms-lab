#ifndef HEAP_H
#define HEAP_H

template <class T>
class Heap
{
public:
 virtual ~Heap() = default;

 /**
   * Insert new value in the heap.
   * @pre The heap is not full.
   */
   virtual void insert(T value) = 0;

    /**
     * Returns the value at the root.
     * @pre The heap is not empty.
     */
    virtual T top() = 0;

    /**
     * Returns the top element and delete from top.
     * @pre Heap not empty.
     */
    virtual void remove() = 0;
};

#endif