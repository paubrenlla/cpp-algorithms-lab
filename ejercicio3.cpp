#include <cassert>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class ObjetosEstanteriaBH
{
private:
    struct ObjetoEstanteria
    {
        int id;
        int precio;
        int celda;

        ObjetoEstanteria(int unId, int unPrecio, int unaCelda) : id(unId), precio(unPrecio), celda(unaCelda) {};
    };

    ObjetoEstanteria **objetos;

    ObjetoEstanteria **existencia;

    int ultimo;

    void actualizar(int unId, int unPrecio)
    {
        if (this->existencia[unId]->precio > unPrecio)
        {
            this->existencia[unId]->precio = unPrecio;
            this->flotar(this->existencia[unId]->celda);
        }
    }

    void flotar(int pos)
    {
        while (pos > 1)
        {
            int precioPadre = this->objetos[pos / 2]->precio;
            int precioPos = this->objetos[pos]->precio;

            if (precioPos < precioPadre)
            {
                this->swap(pos, pos / 2);
                pos = pos / 2;
            }
            else if (precioPos == precioPadre && this->objetos[pos]->id > this->objetos[pos / 2]->id)
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

    void agregar(int id, int precio)
    {
        this->ultimo = this->ultimo + 1;

        this->objetos[this->ultimo] = new ObjetoEstanteria(id, precio, this->ultimo);
        this->existencia[id] = this->objetos[this->ultimo];

        this->flotar(this->ultimo);
    }

    void pop()
    {
        this->swap(this->ultimo, 1);

        int id = this->objetos[this->ultimo]->id;
        delete this->objetos[this->ultimo];
        this->objetos[this->ultimo] = NULL;
        this->existencia[id] = NULL;

        this->ultimo--;
        this->hundir(1);
    }
    
    int mejorObjeto(int nodo1, int nodo2)
    {
        if (this->objetos[nodo1]->precio < this->objetos[nodo2]->precio)
        {
            return nodo1;
        } 
        else if (this->objetos[nodo1]->precio > this->objetos[nodo2]->precio)
        {
            return nodo2;
        }
        else 
        {
            if (this->objetos[nodo1]->id > this->objetos[nodo2]->id)
            {
                return nodo1;
            }
            else if (this->objetos[nodo1]->id < this->objetos[nodo2]->id)
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
        ObjetoEstanteria *temp = this->objetos[i];

        this->objetos[i]->celda = j;
        this->objetos[i] = this->objetos[j];

        this->objetos[j]->celda = i;
        this->objetos[j] = temp;
    }

public:
    ObjetosEstanteriaBH(int esperados)
    {
        this->existencia = new ObjetoEstanteria *[esperados + 1];

        this->objetos = new ObjetoEstanteria *[esperados + 1];

        for (int i = 0; i < esperados + 1; i++)
        {
            this->existencia[i] = NULL;
            this->objetos[i] = NULL;
        }

        this->ultimo = 0;
    }

    void add(int id, int precio)
    {
        if (this->existencia[id] != NULL)
        {
            this->actualizar(id, precio);
        }
        else
        {
            this->agregar(id, precio);
        }
    }

    int masBarato()
    {
        int id = this->objetos[1]->id;
        this->pop();
        return id;
    }
};

int main()
{
    int n = 0;
    cin >> n;

    ObjetosEstanteriaBH *objetos = new ObjetosEstanteriaBH(n);

    int id = -1;
    int precio = -1;

    for (int i = 0; i < n; i++)
    {
        cin >> id;
        cin >> precio;
        objetos->add(id, precio);
    }

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << objetos->masBarato() << endl;
    }

    return 0;
}

/*
Vamos a ordenar no por ID, sino por precio, ya que nos pide en O(N*logN) la funcion masBaratos.
El array existencia nos permite saber si hay que insetrtar por precio y flotar, o si hay que buscar el objeto.
*/