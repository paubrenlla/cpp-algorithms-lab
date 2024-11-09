#ifndef MINHEAP_H
#define MINHEAP_H

class MinHeap
{
public:

    // pre:
    // post: 
    virtual void eliminarTope() = 0;

    // pre: 
    // post: 
    virtual int tope() = 0;

    // pre: 
    // post: 
    virtual void insertar(int el) = 0;

    // pre: 
    // post: 
    virtual bool estaLleno() = 0;

    // pre: 
    // post: 
    virtual bool estaVacio() = 0;
    
};

#endif