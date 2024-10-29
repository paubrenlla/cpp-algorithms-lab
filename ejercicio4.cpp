#include <cassert>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class Pedidos
{
private:
    struct Pedido
    {
        int id;
        int prioridad;
        bool paraLlevar;
        string tipo;
        int posicion;

        Pedido(int unId, int unaPrioridad, bool llevar, string unTipo, int unaPos): id(unId), prioridad(unaPrioridad), paraLlevar(llevar), tipo(unTipo), posicion(unaPos) {}
    };

    int ultimo;
    int size;
    Pedido** ordenesAVL;
    Pedido** modificaciones;

    void flotar(int pos)
    {
        while (pos > 1)
        {
            int padre = pos / 2;
            
            if (this->mejorPedido(pos, padre) == pos)
            {
                this->swap(padre, pos);
            }
            else
            {
                return;
            }

            pos = pos / 2;
        }
        
    }

    int mejorPedido(int nodo1, int nodo2)
    {
        if (this->ordenesAVL[nodo1]->prioridad > this->ordenesAVL[nodo2]->prioridad)
        {
            return nodo1;
        } 
        else if (this->ordenesAVL[nodo1]->prioridad < this->ordenesAVL[nodo2]->prioridad)
        {
            return nodo2;
        }
        else 
        {
            if (this->ordenesAVL[nodo1]->paraLlevar && !this->ordenesAVL[nodo2]->paraLlevar)
            {
                return nodo1;
            }
            else if (this->ordenesAVL[nodo2]->paraLlevar && !this->ordenesAVL[nodo1]->paraLlevar)
            {
                return nodo2;
            }
            else
            {
                if (this->ordenesAVL[nodo1]->id > this->ordenesAVL[nodo2]->id)
                {
                    return nodo2;
                }
                else
                {
                    return nodo1;
                }
                
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
                mejor = this->mejorPedido(hijoIzq, hijoDer);
            }
            if (mejor != -1 && this->mejorPedido(pos, mejor) == mejor) {
                this->swap(pos, mejor);
                this->hundir(mejor);
            }
        }
    }

    void swap(int i, int j)
    {
        Pedido* temp = this->ordenesAVL[i];

        this->ordenesAVL[i]->posicion = j;
        this->ordenesAVL[i] = this->ordenesAVL[j];

        this->ordenesAVL[j]->posicion = i;
        this->ordenesAVL[j] = temp;
    }

    void deleteUltimo()
    {
        int id = this->ordenesAVL[this->ultimo]->id;
        delete this->modificaciones[id];
        this->modificaciones[id] = NULL;
        this->ordenesAVL[this->ultimo] = NULL;
        this->ultimo--;
    }

public:
    Pedidos(int unaCant)
    {
        this->size = unaCant + 1;
        this->ultimo = 0;
        this->ordenesAVL = new Pedido*[this->size];
        this->modificaciones = new Pedido*[this->size];

        for (int i = 0; i < this->size; i++)
        {
            this->ordenesAVL = NULL;
            this->modificaciones = NULL;
        }
    }

    void agregarPedido(int unId, int unaPrioridad, bool llevar, string unTipo)
    {
        this->ultimo = this->ultimo + 1;

        this->ordenesAVL[this->ultimo] = new Pedido(unId, unaPrioridad, llevar, unTipo, this->ultimo);
        this->modificaciones[unId] = this->ordenesAVL[this->ultimo];

        this->flotar(this->ultimo);        
    }

    void cambiarLlevar(int id)
    {
        this->modificaciones[id]->paraLlevar = true;

        this->flotar(this->modificaciones[id]->posicion);
    }

    void entregar(int id)
    {
        this->swap(this->ultimo, this->modificaciones[id]->posicion);
        this->deleteUltimo();

        this->hundir(this->modificaciones[id]->posicion);
    }

    string pop()
    {
        string retorno = std::to_string(this->ordenesAVL[1]->id) + " " + std::to_string(this->ordenesAVL[1]->prioridad) + " " + std::to_string(this->ordenesAVL[1]->paraLlevar) + " " + this->ordenesAVL[1]->tipo;
        
        this->swap(this->ultimo, 1);
        this->deleteUltimo();
        this->hundir(1);

        return retorno;
    }

    bool esVacio()
    {
        return this->ultimo == 0;
    }
};

int main()
{
    int cantPedidos;
    cin >> cantPedidos;

    int cantOps;
    cin >> cantOps;

    Pedidos* pedidos = new Pedidos(cantPedidos);

    char command;
    cin >> command;

    for (int i = 0; i < cantOps; i++)
    {
        if (command == 'I')
        {
            int id;
            int prioridad;
            bool paraLlevar;
            string tipo;

            cin >> id >> prioridad >> paraLlevar >> tipo;

            pedidos->agregarPedido(id, prioridad, paraLlevar, tipo);
        }
        else if (command == 'C')
        {
            int id;
            cin >> id;

            pedidos->cambiarLlevar(id);
        }
        else if (command == 'E')
        {
            int id;
            cin >> id;

            pedidos->entregar(id);
        }
    }

    while (pedidos->esVacio() == false)
    {
        cout << pedidos->pop() << endl;
    }
    

    return 0;
}