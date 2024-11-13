#include <cassert>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class Ejercicio7
{
private:
    
    
public:
    Ejercicio7(int cantCanciones)
    {

    };

    void add(int duracion)
    {

    }

    void setAlumnos(int cantidad)
    {

    }

    void procesar()
    {

    }

};


int main()
{
    int cantCanciones = 0;
    cin >> cantCanciones;

    Ejercicio7* canciones = new Ejercicio7(cantCanciones);

    for (int i = 0; i < cantCanciones; i++)
    {
        int duracion;
        cin >> duracion;

        canciones->add(duracion);
    }

    int cantAlumnos;
    cin >> cantAlumnos;
    
    canciones->setAlumnos(cantAlumnos);

    canciones->procesar();

    return 0;
}