
#ifndef MINHEAP
#define MINHEAP
#include <cassert>

class MinHeap
{
private:
    int* arr;
    int posTope;
    int capacidad;

    void swap(int p1, int p2)
    {
        int aux = this->arr[p1];
        this->arr[p1] = this->arr[p2];
        this->arr[p2] = aux;
    }

    void flotar(int pos)
    {
        if (pos > 1)
        {
            int posPadre = pos / 2;
            if (this->arr[pos] < this->arr[posPadre])
            {
                this->swap(posPadre, pos);
                this->flotar(posPadre);
            }
        }
    }

    void hundir(int pos)
    {
        int posHijoIzq = pos * 2;
        int posHijoDer = pos * 2 + 1;

        if (posHijoIzq < posTope && posHijoDer < posTope)
        {
            int posHijoMenor = posHijoIzq;
            if (this->arr[posHijoIzq] > this->arr[posHijoDer])
            {
                posHijoMenor = posHijoDer;
            }
            
            if (this->arr[pos] > this->arr[posHijoMenor])
            {
                this->swap(pos, posHijoMenor);
                this->hundir(posHijoMenor);
            }
        }

        else if (posHijoIzq < posTope)
        {
            if (this->arr[pos] > this->arr[posHijoIzq])
            {
                this->swap(pos, posHijoIzq);
                this->hundir(posHijoIzq);
            }
        }
    }

public:
    MinHeap(int unaCapacidad)
    {

        this->arr = new int[unaCapacidad + 1]();
        this->posTope = 1;
        this->capacidad = unaCapacidad;
    }

    int tope()
    {
        assert(!this->estaVacio());
        return this->arr[1];
    }

    void eliminarTope()
    {
        assert(!this->estaVacio());
        this->arr[1] = this->arr[posTope - 1];
        this->posTope--;
        this->hundir(1);
    }

    void insertar(int el)
    {
        assert(!this->estaLleno());
        this->arr[posTope++] = el;
        this->flotar(posTope - 1);
    }

    bool estaLleno()
    {
        return this->posTope > this->capacidad;
    }

    bool estaVacio()
    {
        return this->posTope == 1;
    }
};

#endif
