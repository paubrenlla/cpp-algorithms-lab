#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include <cmath>
#include "tads/Tuple.cpp"
#include "funciones/enteros.cpp"

using namespace std;

class Ejercicio8
{
private:
    struct Ciudad
    {
        int x, y, poblacion;

        Ciudad() : x(0), y(0), poblacion(0) {};
        Ciudad(int cX, int cY, int p) : x(cX), y(cY), poblacion(p) {};
    };

    Ciudad *ciudades;
    int cantCiudades;

    double distanciaEfectiva(Ciudad *c1, Ciudad *c2)
    {
        double distEuclidiana = std::sqrt(std::pow(c2->x - c1->x, 2) + std::pow(c2->y - c1->y, 2));
        double difPoblacion = hacerPositivo(c2->poblacion - c1->poblacion) / double(std::max(c1->poblacion, c2->poblacion));
        return distEuclidiana + difPoblacion;
    }

    void ordenarPorX(Ciudad **arr, int n)
    {
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = 0; j < n - i - 1; ++j)
            {
                if (arr[j]->x > arr[j + 1]->x)
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    void ordenarPorY(Ciudad **arr, int n)
    {
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = 0; j < n - i - 1; ++j)
            {
                if (arr[j]->y > arr[j + 1]->y)
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    Tuple<int, int> encontrarParOptimo(int izquierda, int derecha, Ciudad **ciudadesOrdenadasY, int n)
    {
        if (derecha - izquierda <= 3)
        {
            double distanciaMinima = 1 << 24;
            int sumaPoblacionMaxima = 0;
            Tuple<int, int> mejorPar;

            for (int i = izquierda; i < derecha; ++i)
            {
                for (int j = i + 1; j < derecha; ++j)
                {
                    double distancia = distanciaEfectiva(&ciudades[i], &ciudades[j]);
                    int sumaPoblacion = ciudades[i].poblacion + ciudades[j].poblacion;

                    if (distancia < distanciaMinima ||
                        (distancia == distanciaMinima && sumaPoblacion > sumaPoblacionMaxima))
                    {
                        distanciaMinima = distancia;
                        sumaPoblacionMaxima = sumaPoblacion;
                        mejorPar = Tuple<int, int>(i, j);
                    }
                }
            }

            return mejorPar;
        }

        int mid = izquierda + (derecha - izquierda) / 2;
        int midX = ciudades[mid].x;

        Tuple<int, int> parIzquierdo = encontrarParOptimo(izquierda, mid, ciudadesOrdenadasY, n);
        Tuple<int, int> parDerecho = encontrarParOptimo(mid, derecha, ciudadesOrdenadasY, n);

        double distanciaIzquierda = distanciaEfectiva(&ciudades[parIzquierdo.getFirst()], &ciudades[parIzquierdo.getSecond()]);
        double distanciaDerecha = distanciaEfectiva(&ciudades[parDerecho.getFirst()], &ciudades[parDerecho.getSecond()]);

        double distanciaMinima = min(distanciaIzquierda, distanciaDerecha);
        Tuple<int, int> mejorPar;
        if (distanciaIzquierda < distanciaDerecha)
        {
            mejorPar = parIzquierdo;
        }
        else
        {
            mejorPar = parDerecho;
        }

        Ciudad **banda = new Ciudad *[n];
        int bandaSize = 0;
        for (int i = 0; i < n; ++i)
        {
            if (hacerPositivo(ciudadesOrdenadasY[i]->x - midX) < distanciaMinima)
            {
                banda[bandaSize++] = ciudadesOrdenadasY[i];
            }
        }

        int sumaPoblacionMaxima = ciudades[mejorPar.getFirst()].poblacion + ciudades[mejorPar.getSecond()].poblacion;
        for (int i = 0; i < bandaSize; ++i)
        {
            for (int j = i + 1; j < bandaSize && (banda[j]->y - banda[i]->y) < distanciaMinima; ++j)
            {
                double distancia = distanciaEfectiva(banda[i], banda[j]);
                int sumaPoblacion = banda[i]->poblacion + banda[j]->poblacion;

                if (distancia < distanciaMinima ||
                    (distancia == distanciaMinima && sumaPoblacion > sumaPoblacionMaxima))
                {
                    distanciaMinima = distancia;
                    sumaPoblacionMaxima = sumaPoblacion;
                    mejorPar = Tuple<int, int>(banda[i] - ciudades, banda[j] - ciudades);
                }
            }
        }

        delete[] banda;
        return mejorPar;
    }

public:
    Ejercicio8(int cantidad)
    {
        this->cantCiudades = cantidad;
        this->ciudades = new Ciudad[cantidad];
    }

    void add(int index, int x, int y, int p)
    {
        this->ciudades[index] = Ciudad(x, y, p);
    }

    void resolver()
    {
        Ciudad **ciudadesOrdenadasX = new Ciudad *[this->cantCiudades];
        Ciudad **ciudadesOrdenadasY = new Ciudad *[this->cantCiudades];

        for (int i = 0; i < this->cantCiudades; ++i)
        {
            ciudadesOrdenadasX[i] = &ciudades[i];
            ciudadesOrdenadasY[i] = &ciudades[i];
        }

        ordenarPorX(ciudadesOrdenadasX, this->cantCiudades);
        ordenarPorY(ciudadesOrdenadasY, this->cantCiudades);

        Tuple<int, int> resultado = encontrarParOptimo(0, this->cantCiudades, ciudadesOrdenadasY, this->cantCiudades);

        Ciudad *c1 = &ciudades[resultado.getFirst()];
        Ciudad *c2 = &ciudades[resultado.getSecond()];

        if (c1->x > c2->x || (c1->x == c2->x && c1->y > c2->y)) 
        {
            swap(c1, c2);
        }

        cout << c1->x << " " << c1->y << " " << c1->poblacion << endl;
        cout << c2->x << " " << c2->y << " " << c2->poblacion << endl;

        delete[] ciudadesOrdenadasX;
        delete[] ciudadesOrdenadasY;
    }
};

int main()
{
    int cantidad;
    cin >> cantidad;

    Ejercicio8 *ciudades = new Ejercicio8(cantidad);

    for (int i = 0; i < cantidad; i++)
    {
        int x, y, p;

        cin >> x >> y >> p;

        ciudades->add(i, x, y, p);
    }

    ciudades->resolver();

    return 0;
}