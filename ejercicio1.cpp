#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "AVL.cpp"

using namespace std;

struct Libro
{
    int id;
    string titulo;
    bool habilitado;

    //Constructor
    Libro(int unId, string unTitulo): id(unId), titulo(unTitulo), habilitado(true) {}

    // Sobrecarga del operador ==
    bool operator==(const Libro& otro) const 
    {
        return id == otro.id;
    }

    // Sobrecarga del operador !=
    bool operator!=(const Libro& otro) const 
    {
        return !(*this == otro);
    }
};

class Biblioteca {
    public:
        Biblioteca() 
        {
            this->libros = new AVL<Libro>();
            this->cantLibros = 0;
            this->cantHabilitados = 0;
        }

        void agregar(int unId, int unTitulo){
            Libro* busqueda = this->libros->contains(unId);
            if (busqueda == NULL)
            {
                Libro nuevoLibro = new Libro(unId, unTitulo);
                this->libros->insert(nuevoLibro);
                this->cantHabilitados++;
                this->cantLibros++;
            } 
            else
            {
                busqueda->titulo = unTitulo;
                if (busqueda->habilitado == false)
                {
                    this->cantHabilitados++;
                    busqueda->habilitado = true;
                }
            }
        }

        string buscar(int unId)
        {
            Libro* busqueda = this->libros->contains(unId);
            
            if (busqueda == NULL)
            {
                return "libro no encontrado"
            }
            
            if (busqueda->habilitado == true)
            {
                return busqueda->titulo ++ " " ++ "H";
            }
            
            if (busqueda->habilitado == false)
            {
                return busqueda->titulo ++ " " ++ "D";
            }
            
        }

        string cambiarHab(int unId)
        {
            Libro* busqueda = this->libros->contains(unId);
            if (busqueda == NULL)
            {
                return "libro no encontrado"
            }
            
            busqueda->habilitado = !(busqueda->habilitado);
            
            if (busqueda->habilitado == true)
            {
                this->cantHabilitados++;
                return busqueda->titulo ++ " " ++ "H";
            }

            if (busqueda->habilitado == false)
            {
                this->cantHabilitados--;
                return busqueda->titulo ++ " " ++ "D";
            }
        }

        string totalLibros()
        {
            int cantDes = this->cantLibros - this->cantHabilitados;
            return this->cantLibros ++ " " ++ this->cantHabilitados ++ " " ++ cantDes;
        }


    private:
        int cantLibros;
        int cantHabilitados;
        AVL<Libro>* libros;
};


int main()
{
    return 0;
}