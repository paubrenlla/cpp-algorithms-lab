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

    struct PedidoHash
    {
        Pedido* pedido;
        PedidoHash* sig;

        PedidoHash(Pedido* unPedido): pedido(unPedido), sig(NULL){}
        PedidoHash(Pedido* unPedido, PedidoHash* lista): pedido(unPedido), sig(lista){}
    };

    int ultimo;
    int size;
    Pedido** ordenesBH;

    PedidoHash** ordenesHash;
    int buckets;
    
    int hash(int i)
    {
        return (i * 31) % this->buckets;
    }

    Pedido* findHash(int id)
    {
        int pos = this->hash(id);
        PedidoHash* aux = this->ordenesHash[pos];
        while (aux != NULL && aux->pedido->id != id)
        {
            aux = aux->sig;
        }
        return aux->pedido;
    }

    void agregarHash(Pedido* p)
    {
        int pos = this->hash(p->id);
        
        PedidoHash* aux = this->ordenesHash[pos];
        this->ordenesHash[pos] = new PedidoHash(p, aux);
    }

    void borrarDeLista(int id, PedidoHash*& l) 
    {
        if (l != NULL) 
        {
            if (l->pedido->id == id) 
            {
                PedidoHash* aux = l;
                l = l->sig;
                delete aux;
                aux = NULL;
            }
            else borrarDeLista(id, l->sig);
        }
    }

    void eliminarHash(int id)
    {
        this->borrarDeLista(id, this->ordenesHash[this->hash(id)]);
    }

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
        if (this->ordenesBH[nodo1]->prioridad < this->ordenesBH[nodo2]->prioridad)
        {
            return nodo1;
        } 
        else if (this->ordenesBH[nodo1]->prioridad > this->ordenesBH[nodo2]->prioridad)
        {
            return nodo2;
        }
        else 
        {
            if (this->ordenesBH[nodo1]->paraLlevar && !this->ordenesBH[nodo2]->paraLlevar)
            {
                return nodo1;
            }
            else if (this->ordenesBH[nodo2]->paraLlevar && !this->ordenesBH[nodo1]->paraLlevar)
            {
                return nodo2;
            }
            else
            {
                if (this->ordenesBH[nodo1]->id > this->ordenesBH[nodo2]->id)
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
        Pedido* temp = this->ordenesBH[i];

        this->ordenesBH[i]->posicion = j;
        this->ordenesBH[i] = this->ordenesBH[j];

        this->ordenesBH[j]->posicion = i;
        this->ordenesBH[j] = temp;
    }

    int deleteUltimo()
    {
        int id = this->ordenesBH[this->ultimo]->id;
        this->eliminarHash(id);
        
        this->ordenesBH[this->ultimo] = NULL;
        this->ultimo--;
        
        return id;
    }

public:
    Pedidos(int unaCant)
    {
        this->size = unaCant + 1;
        this->ultimo = 0;
        this->ordenesBH = new Pedido*[this->size];

        this->buckets = (unaCant + 1) * 2; 
        this->ordenesHash = new PedidoHash*[this->buckets];

        for (int i = 0; i < this->size; i++)
        {
            this->ordenesBH[i] = NULL;
        }
        for (int i = 0; i < this->buckets; i++)
        {
            this->ordenesHash[i] = NULL;
        }
        
    }

    void agregarPedido(int unId, int unaPrioridad, bool llevar, string unTipo)
    {
        this->ultimo = this->ultimo + 1;

        this->ordenesBH[this->ultimo] = new Pedido(unId, unaPrioridad, llevar, unTipo, this->ultimo);
        this->agregarHash(this->ordenesBH[this->ultimo]);

        this->flotar(this->ultimo);        
    }

    void cambiarLlevar(int id)
    {
        Pedido* aux = this->findHash(id);
        aux->paraLlevar = true;

        this->flotar(aux->posicion);
    }

    void entregar(int id)
    {
        this->swap(this->ultimo, this->findHash(id)->posicion);
        int idElim = this->deleteUltimo();

        if (this->esVacio() == false && idElim != id && this->ultimo > 1)
        {
            this->flotar(this->findHash(id)->posicion);
            this->hundir(this->findHash(id)->posicion);
        }
    }

    string pop()
    {
        string llevar = "true";
        if (this->ordenesBH[1]->paraLlevar == false)
        {
            llevar = "false";
        }
        
        string retorno = std::to_string(this->ordenesBH[1]->id) + " " + std::to_string(this->ordenesBH[1]->prioridad) + " " + llevar + " " + this->ordenesBH[1]->tipo;
        
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

    string command;
    

    for (int i = 0; i < cantOps; i++)
    {
        cin >> command;
        if (command == "I")
        {
            int id;
            int prioridad;
            string llevar;
            bool paraLlevar = true;
            string tipo;

            cin >> id >> prioridad >> llevar >> tipo;

            if (llevar == "false")
            {
                paraLlevar = false;
            }

            pedidos->agregarPedido(id, prioridad, paraLlevar, tipo);
        }
        else if (command == "C")
        {
            int id;
            cin >> id;

            pedidos->cambiarLlevar(id);
        }
        else if (command == "E")
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