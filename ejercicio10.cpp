#include <cassert>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class Jardin
{
private:
    struct Flor
    {
        string nombre;
        int restriccion;

        Flor(string n, int r) : nombre(n), restriccion(r) {};
        Flor() : nombre(""), restriccion(-1) {};
    };
    Flor *flores;
    int cuadriculaSize;
    int floresDiferentes;
    Flor **cuadricula;
    int maxFlores;
    bool *floresPlantadas;

    bool esValido(int fila, int columna, Flor flor)
    {
        for (int i = max(0, fila - 1); i <= min(this->cuadriculaSize - 1, fila + 1); ++i)
        {
            for (int j = max(0, columna - 1); j <= min(this->cuadriculaSize - 1, columna + 1); ++j)
            {
                if (cuadricula[i][j].nombre == flor.nombre)
                {
                    return false;
                }
            }
        }

        if (flor.restriccion != -1 && flor.restriccion != fila)
        {
            return false;
        }

        return true;
    }

    void plantarFlores(int fila, int columna, int count)
    {
        if (fila == this->cuadriculaSize)
        {
            maxFlores = max(maxFlores, count);
            return;
        }

        if (count + (this->cuadriculaSize - fila) * this->cuadriculaSize <= maxFlores)
        {
            return;
        }

        int sigFila = fila + (columna + 1) / this->cuadriculaSize;
        int sigCol = (columna + 1) % this->cuadriculaSize;

        for (int i = 0; i < this->floresDiferentes; ++i)
        {
            if (this->esValido(fila, columna, this->flores[i]))
            {
                this->cuadricula[fila][columna] = this->flores[i];
                this->floresPlantadas[i] = true; 
                this->plantarFlores(sigFila, sigCol, count + 1);
                this->floresPlantadas[i] = false; 
                this->cuadricula[fila][columna] = Flor();
            }
        }

        this->plantarFlores(sigFila, sigCol, count);
    }

public:
    Jardin(int n, int f)
    {
        this->cuadricula = new Flor *[n];
        for (int i = 0; i < n; ++i)
        {
            this->cuadricula[i] = new Flor[n];
            for (int j = 0; j < n; ++j)
            {
                cuadricula[i][j] = Flor();
            }
        }
        this->flores = new Flor[f];
        this->floresPlantadas = new bool[f];

        for (int i = 0; i < f; ++i)
        {
            floresPlantadas[i] = false;
        }

        this->maxFlores = 0;
        this->cuadriculaSize = n;
        this->floresDiferentes = f;
    }

    void add(string nombre, int restriccion, int index)
    {
        this->flores[index] = Flor(nombre, restriccion);
    }

    void procesar()
    {
        this->plantarFlores(0, 0, 0);
        cout << maxFlores << endl;
    }
};

int main()
{
    int cuadricula;
    cin >> cuadricula;

    int flores;
    cin >> flores;

    Jardin *j = new Jardin(cuadricula, flores);
    for (int i = 0; i < flores; i++)
    {
        string color;
        int fila;

        cin >> color >> fila;
        j->add(color, fila, i);
    }

    j->procesar();

    return 0;
}
