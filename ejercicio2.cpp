#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

class BibliotecaHash
{
private:
    struct Libro
    {
        int id;
        string titulo;
        bool habilitado;

        // Constructor
        Libro(int unId, string unTitulo) : id(unId), titulo(unTitulo), habilitado(true) {}
    };
    int cantLibros;
    int cantHabilitados;
    int buckets;
    Libro** libros;
    //usaremoms V para vacio, E para eliminado y L para lleno
    char* vacioElimLleno;

public:
    BibliotecaHash(int espereados)
    {
        this->cantLibros = 0;
        this->cantHabilitados = 0;
        this->buckets = espereados/0.7;
        this->vacioElimLleno = new char[this->buckets];
        this->libros* = new Libro[this->buckets];
        
        for (int i = 0; i < this->buckets; i++)
        {
            char[i] = 'V';
            this->libros[i] = NULL;
        }
    }
}

int main()
{
    
    return 0;
}