class MinHeap
{
private:
    struct Nodo
    {
        int id;
        int costo;
        int celda;

        Nodo(int unId, int uncosto, int unaCelda) : id(unId), costo(uncosto), celda(unaCelda) {};
    };

    Nodo **nodoBH;

    Nodo **existencia;

    int ultimo;

    void actualizar(int unId, int uncosto)
    {
        if (this->existencia[unId]->costo > uncosto)
        {
            this->existencia[unId]->costo = uncosto;
            this->flotar(this->existencia[unId]->celda);
        }
    }

    void flotar(int pos)
    {
        while (pos > 1)
        {
            int costoPadre = this->nodoBH[pos / 2]->costo;
            int costoPos = this->nodoBH[pos]->costo;

            if (costoPos < costoPadre)
            {
                this->swap(pos, pos / 2);
                pos = pos / 2;
            }
            else if (costoPos == costoPadre && this->nodoBH[pos]->id > this->nodoBH[pos / 2]->id)
            {
                this->swap(pos, pos / 2);
                pos = pos / 2;
            }
            else 
            {
                return;
            }
        }
    }

    void agregar(int id, int costo)
    {
        this->ultimo = this->ultimo + 1;

        this->nodoBH[this->ultimo] = new Nodo(id, costo, this->ultimo);
        this->existencia[id] = this->nodoBH[this->ultimo];

        this->flotar(this->ultimo);
    }

    void pop()
    {
        this->swap(this->ultimo, 1);

        int id = this->nodoBH[this->ultimo]->id;
        delete this->nodoBH[this->ultimo];
        this->nodoBH[this->ultimo] = NULL;
        this->existencia[id] = NULL;

        this->ultimo--;
        this->hundir(1);
    }
    
    int mejorObjeto(int nodo1, int nodo2)
    {
        if (this->nodoBH[nodo1]->costo < this->nodoBH[nodo2]->costo)
        {
            return nodo1;
        } 
        else if (this->nodoBH[nodo1]->costo > this->nodoBH[nodo2]->costo)
        {
            return nodo2;
        }
        else 
        {
            if (this->nodoBH[nodo1]->id > this->nodoBH[nodo2]->id)
            {
                return nodo1;
            }
            else if (this->nodoBH[nodo1]->id < this->nodoBH[nodo2]->id)
            {
                return nodo2;
            }
            else
            {
                return -1;
            }
        }
    }

    void hundir(int pos)
    {
        int hijoIzq = 2 * pos;
        int hijoDer = hijoIzq + 1;
        if (hijoIzq <= this->ultimo) {
            int mejor = hijoIzq;
            if (hijoDer <= this->ultimo) {
                mejor = this->mejorObjeto(hijoIzq, hijoDer);
            }
            if (mejor != -1 && this->mejorObjeto(pos, mejor) == mejor) {
                this->swap(pos, mejor);
                this->hundir(mejor);
            }
        }
    }

    void swap(int i, int j)
    {
        Nodo *temp = this->nodoBH[i];

        this->nodoBH[i]->celda = j;
        this->nodoBH[i] = this->nodoBH[j];

        this->nodoBH[j]->celda = i;
        this->nodoBH[j] = temp;
    }

public:
    MinHeap(int esperados)
    {
        this->existencia = new Nodo *[esperados + 1];

        this->nodoBH = new Nodo *[esperados + 1];

        for (int i = 0; i < esperados + 1; i++)
        {
            this->existencia[i] = NULL;
            this->nodoBH[i] = NULL;
        }

        this->ultimo = 0;
    }

    void add(int id, int costo)
    {
        if (this->existencia[id] != NULL)
        {
            this->actualizar(id, costo);
        }
        else
        {
            this->agregar(id, costo);
        }
    }

    int top()
    {
        int id = this->nodoBH[1]->id;
        this->pop();
        return id;
    }
};