#include <cassert>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class Ejercicio7
{
private:
    int* duraciones;
    int cantCanciones;
    int sumaDuraciones;
    int cantAlumnos;
    int maxIndex;
    
    bool esFactible(int tiempoMax) {
        int alumnosUsados = 1;
        int tiempoActual = 0;

        for (int i = 0; i < this->cantCanciones; ++i) {
            if (tiempoActual + this->duraciones[i] <= tiempoMax) {
                tiempoActual += this->duraciones[i];
            } else {
                alumnosUsados++;
                if (alumnosUsados > this->cantAlumnos || this->duraciones[i] > tiempoMax) {
                    return false;
                }
                tiempoActual = this->duraciones[i];
            }
        }
        return true;
    }

    void dividirCanciones(int tiempoMax) {
        int asignaciones[cantAlumnos][2]; // Para almacenar las posiciones inicial y final de las canciones asignadas a cada estudiante
        int tiemposTotales[cantAlumnos] = {0}; // Para almacenar el tiempo total de cada estudiante

        int estudianteActual = 0;
        int tiempoActual = 0;
        int inicio = 1; // Posición inicial de la primera canción asignada (1-indexado)

        for (int i = 0; i < cantCanciones; ++i) {
            if (tiempoActual + duraciones[i] <= tiempoMax) {
                tiempoActual += duraciones[i];
            } else {
                // Guardar la asignación del estudiante actual
                asignaciones[estudianteActual][0] = inicio;
                asignaciones[estudianteActual][1] = i;
                tiemposTotales[estudianteActual] = tiempoActual;

                // Pasar al siguiente estudiante
                estudianteActual++;
                tiempoActual = duraciones[i];
                inicio = i + 1; // Nueva posición inicial
            }
        }

        // Guardar la última asignación
        asignaciones[estudianteActual][0] = inicio;
        asignaciones[estudianteActual][1] = cantCanciones;
        tiemposTotales[estudianteActual] = tiempoActual;

        // Imprimir los resultados
        for (int i = 0; i <= estudianteActual; ++i) {
            cout << tiemposTotales[i] << " " << asignaciones[i][0] << " " << asignaciones[i][1] << endl;
        }
        cout << tiempoMax << endl;
    }

public:
    Ejercicio7(int cantCanciones)
    {
        this->duraciones = new int[cantCanciones];
        for (int i = 0; i < cantCanciones; i++)
        {
            this->duraciones[i] = 0;
        }
        this->cantAlumnos = 0;
        this->sumaDuraciones = 0;
        this->maxIndex = 0;
        this->cantCanciones = cantCanciones;
    };

    void add(int duracion, int index)
    {
        this->duraciones[index] = duracion;
        this->sumaDuraciones += duracion;

        if (index = 0)
        {
            this->maxIndex = 0;
        } 
        else if (duracion > this->duraciones[maxIndex])
        {
            this->maxIndex = index;
        }
    }

    void setAlumnos(int cantidad)
    {
        this->cantAlumnos = cantidad;
    }

    void procesar()
    {
        int respuesta = this->sumaDuraciones;
        int inicio = this->duraciones[this->maxIndex];
        int fin = this->sumaDuraciones;

        while (inicio <= fin)
        {
            int medio = inicio + (fin - inicio) / 2;

            if (this->esFactible(medio)) {
                respuesta = medio;
                fin = medio - 1;
            } else {
                inicio = medio + 1;
            }
        }
        
        this->dividirCanciones(respuesta);
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

        canciones->add(duracion, i);
    }

    int cantAlumnos;
    cin >> cantAlumnos;
    
    canciones->setAlumnos(cantAlumnos);

    canciones->procesar();

    return 0;
}
