#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "./funciones/enteros.cpp"

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

    int funcionHash1(int key)
    {
        return hacerPositivo(key * 31);
    }

    int funcionHash2(int key)
    {
        return hacerPositivo(potencia(key, 2));
    }

    int getIndex(int key, int intentos)
    {
        return (this->funcionHash1(key) + this->funcionHash2(key) * intentos) % this->buckets;
    }

    string libroHabilitado(bool hab)
    {
        if (hab)
        {
            return "H";
        }
        else
        {
            return "D";
        }
    }

public:
    BibliotecaHash(int espereados)
    {
        this->cantLibros = 0;
        this->cantHabilitados = 0;
        this->buckets = espereados * 2;
        this->libros = new Libro*[this->buckets];
        
        for (int i = 0; i < this->buckets; i++)
        {
            this->libros[i] = NULL;
        }
    }

    void add(int unId, string unNombre)
    {
        int indice = 0;
        
        int intentos = 0;
        while (intentos < this->buckets)
        {
            indice = this->getIndex(unId, intentos);

            if (this->libros[indice]->id == unId)
            {
                if (this->libros[indice]->habilitado != true)
                {
                    this->libros[indice]->habilitado = true;
                    this->cantHabilitados++;    
                }

                this->libros[indice]->titulo = unNombre;
                return;
            }
            if (this->libros[indice] == NULL)
            {
                Libro* nuevo = new Libro(unId, unNombre);
                this->cantLibros++;
                this->cantHabilitados++;
                return;
            }

            intentos++;
        }
    }

    string find(int unId)
    {
        int indice = 0;
        
        int intentos = 0;
        while (intentos < this->buckets)
        {
            indice = this->getIndex(unId, intentos);

            if (this->libros[indice]->id == unId)
            {
                return this->libros[indice]->titulo + " " + this->libroHabilitado(this->libros[indice]->habilitado);
            }
            if (this->libros[indice] == NULL)
            {
                return "libro_no_encontrado";
            }

            intentos++;
        }
    }

    string toggle(int unId)
    {
        int indice = 0;
        
        int intentos = 0;
        while (intentos < this->buckets)
        {
            indice = this->getIndex(unId, intentos);

            if (this->libros[indice]->id == unId)
            {
                if (this->libros[indice]->habilitado == false)
                {
                    this->libros[indice]->habilitado = true;
                    this->cantHabilitados++;
                }
                else
                {
                    this->libros[indice]->habilitado = false;
                    this->cantHabilitados--;
                }

                return "existe";

            }
            if (this->libros[indice] == NULL)
            {
                return "libro_no_encontrado";
            }

            intentos++;
        }
    }

    string count()
    {
        int totalDesHab = this->cantLibros - this->cantHabilitados;
        return to_string(this->cantLibros) + " " + to_string(this->cantHabilitados) + " " + to_string(totalDesHab);
    }


    

};

int main()
{
    int n;
    cin >> n;
    
    BibliotecaHash *biblioteca = new BibliotecaHash(n);
    
    string command;
    int id;
    string name;

    for (int i = 0; i < n; ++i)
    {
        cin >> command;
        if (command == "ADD")
        {
            cin >> id;
            cin >> name;
            biblioteca->add(id, name);
        }
        else if (command == "FIND")
        {
            cin >> id;
            cout << biblioteca->find(id) << endl;
        }
        else if (command == "TOGGLE")
        {
            cin >> id;
            string resultado = biblioteca->toggle(id);
            if (resultado != "existe")
            {
                cout << resultado << endl;
            }
        }
        else if (command == "COUNT")
        {
            cout << biblioteca->count() << endl;
        }
    }

    return 0;
}