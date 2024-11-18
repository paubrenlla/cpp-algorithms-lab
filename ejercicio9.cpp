#include <cassert>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class Jugadores
{
private:
    int** jugadores;
    int cantJugadores;

    int promedio(int ritmo, int tiro, int pase, int regate, int defensa, int fisico)
    {
        return (ritmo + tiro + pase + regate + defensa + fisico) / 6;
    }

    int confianza(string c)
    {
        if (c == "Baja")
        {
            return -5;
        }
        if (c == "Regular")
        {
            return 0;
        }
        if (c == "Alta")
        {
            return 5;
        }
    }

    int formaFisica(string forma)
    {
        if (forma == "Lesionado")
        {
            return -1;    
        }
        if (forma == "Mala")
        {
            return -5;
        }
        if (forma == "Normal")
        {
            return 0;
        }
        if (forma == "Buena")
        {
            return 5;
        }
    }

public:
    Jugadores(int cant)
    {
        this->cantJugadores = cant;
        this->jugadores[3][cant];
        for (int i = 0; i < cant; i++)
        {
            this->jugadores[0][i] = 0;
            this->jugadores[1][i] = 0;
            this->jugadores[2][i] = 0;
        }
    }

    void add(int ritmo, int tiro, int pase, int regate, int defensa, int fisico, string formaFisica, string confianza, int salario, string extranjero, int index)
    {
        int promedio = this->promedio(ritmo, tiro, pase, regate, defensa, fisico);
        int forma = this->formaFisica(formaFisica);
        int conf = this->confianza(confianza);
        
        int valoracion = 0;

        if (forma != -1)
        {
            valoracion = promedio + forma + conf;
        }
        
        this->jugadores[0][index] = valoracion;
        this->jugadores[1][index] = salario;
        
        if (extranjero == "Si")
        {
            this->jugadores[2][index] = 1;
        }
        else
        {
            this->jugadores[2][index] = 0;
        }
    }

    void procesar(int presupuesto, int cantExtranjeros)
    {

    }
};

int main()
{
    int cantJugadores;
    cin >> cantJugadores;

    Jugadores* jugadores = new Jugadores(cantJugadores);

    for (int i = 0; i < cantJugadores; i++)
    {
        int ritmo, tiro, pase, regate, defensa, fisico;
        cin >> ritmo >> tiro >> pase >> regate >> defensa >> fisico;
        
        string formaFisica;
        cin >> formaFisica;

        int salario;
        cin >> salario;

        string extranjero, confianza;
        cin >> extranjero, confianza;
        
        jugadores->add(ritmo, tiro, pase, regate, defensa, fisico, formaFisica, confianza, salario, extranjero, i);
    }
    
    int presupuesto, cantExtranjeros;

    cin >> presupuesto >> cantExtranjeros;

    jugadores->procesar(presupuesto, cantExtranjeros);

    return 0;
}