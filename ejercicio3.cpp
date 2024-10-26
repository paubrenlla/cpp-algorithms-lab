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

        ObjetoEstanteria(int unId, int unPrecio): id(unId), precio(unPrecio) {};
    };

    ObjetoEstanteria** objetos;
    int size;
    bool* existencia;

    int ultimo;

    void actualizar(int id, int precio)
    {
        for (int i = 1; i <= this->ultimo; i++)
        {
            if (this->objetos[i]->id == id)
            {
                if (this->objetos[i]->precio > precio)
                {
                    this->objetos[i]->precio = precio;
                    this->flotar(i);
                }
                return;
            }
        }
        
           
    }

    void flotar(int pos)
    {
        if ((pos > 1) && (this->objetos[pos/2]->precio < this->objetos[pos]->precio))
        {
            this->swap(pos, pos/2);
            this->hundir(pos/2);
        }
    }

    void agregar (int id, int precio)
    {
        this->ultimo = this->ultimo + 1;
        this->objetos[this->ultimo] = new ObjetoEstanteria(id, precio);
        this->flotar(this->ultimo);
    }

    void pop()
    {
        this->objetos[1] = this->objetos[this->ultimo];
        this->ultimo--;
        this->hundir(1);
    }

    void hundir(int pos)
    {
        while (pos*2 <= this->size)
        {
            int aux = 2*pos;
            if (this->objetos[aux]->precio < this->objetos[aux + 1]->precio)
            {
                aux++;
            }
            if (this->objetos[pos]->precio >= this->objetos[aux]->precio)
            {
                break;
            }
            this->swap(aux, pos);
            pos = aux;
        }
        
    }

    void swap(int i, int j) 
    {
        ObjetoEstanteria* temp = this->objetos[i];
        this->objetos[i] = this->objetos[j];
        this->objetos[j] = temp;
    }

public:

    ObjetosEstanteriaBH(int esperados)
    {
        this->size = esperados + 1;

        this->existencia = new bool[this->size];

        this->objetos = new ObjetoEstanteria*[this->size];

        for (int i = 0; i < this->size; i++)
        {
            this->existencia[i] = false;
            this->objetos[i] = NULL;
        }

        this->ultimo = 0;
    }

    void add(int id, int precio)
    {
        if (this->existencia[id] == true)
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

    ObjetosEstanteriaBH* objetos = new ObjetosEstanteriaBH(n);

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
        cout << objetos->masBarato();
    }
    

    return 0;
}

/*
Vamos a ordenar no por ID, sino por precio, ya que nos pide en O(N*logN) la funcion masBaratos.
El array existencia nos permite saber si hay que insetrtar por precio y flotar, o si hay que buscar el objeto.
*/