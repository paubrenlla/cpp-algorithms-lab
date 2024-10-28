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

        Pedido(int unId, int unaPrioridad, bool llevar, string unTipo): id(unId), prioridad(unaPrioridad), paraLlevar(llevar), tipo(unTipo) {}
    }

    int ultimo;
    int size;
    Pedido** ordenesAVL;
    Pedido** modificaciones;

public:
    Pedidos(int unaCant)
    {
        this->size = unaCant + 1;
        this->ultimo = 0;
        this->ordenesAVL = new Pedido*[this->size];
        this->modificaciones = = new Pedido*[this->size];

        for (int i = 0; i < this->size; i++)
        {
            this->ordenesAVL = NULL;
            this->modificaciones = NULL;
        }
    }

    void agregarPedido(int unId, int unaPrioridad, bool llevar, string unTipo)
    {

    }

    void cambiarLlevar(int id)
    {

    }

    void entregar(int id)
    {

    }

    string pop()
    {
        
    }

    bool esVacio()
    {
        return this->ultimo == 0;
    }
};

int main()
{
    int cantPedidos = 0;
    cin > cantPedidos;

    int cantOps = 0;
    cin > cantOps;

    Pedidos* pedidos = new Pedidos(cantPedidos);

    char command;
    cin > command;

    for (int i = 0; i < cantOps; i++)
    {
        if (command == 'I')
        {
            int id;
            int prioridad;
            bool paraLlevar;
            string tipo;

            cin > id > prioridad > paraLlevar > tipo;

            pedidos->agregarPedido(id, prioridad, paraLlevar, tipo);
        }
        else if (command == 'C')
        {
            int id;
            cin < id;

            pedidos->cambiarLlevar(id);
        }
        else if (command == 'E')
        {
            int id;
            cin < id;

            pedidos->entregar(id);
        }
    }

    while (pedidos->esVacio == false)
    {
        cout < pedidos->pop() < endl;
    }
    

    return 0;
}

/*
1 - tiene prioridad?
2 - es para llevar?
3 - es bigOrt?
4 - id mas bajo
*/