#include <cassert>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class Jugadores
{
private:
    struct Jugador
    {
        int valoracion;
        int salario;
        bool extranjero;

        Jugador(int v, int s, bool e) : valoracion(v), salario(s), extranjero(e) {};
    };

    Jugador **jugadores;
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

    void ordenar(int index)
    {
        if (index == 0)
        {
            return;
        }
        if (this->jugadores[index]->valoracion < this->jugadores[index - 1]->valoracion)
        {
            return;
        }
        if (this->jugadores[index]->valoracion > this->jugadores[index - 1]->valoracion || this->jugadores[index]->salario < this->jugadores[index - 1]->salario)
        {
            Jugador *aux = this->jugadores[index];
            this->jugadores[index] = this->jugadores[index - 1];
            this->jugadores[index - 1] = aux;
            this->ordenar(index - 1);
        }
    }

public:
    Jugadores(int cant)
    {
        this->cantJugadores = cant;
        this->jugadores = new Jugador *[cant];
        for (int i = 0; i < cant; i++)
        {
            this->jugadores[i] = NULL;
        }
    }

    void add(int ritmo, int tiro, int pase, int regate, int defensa, int fisico, string formaFisica, string confianza, int salario, string extranjero, int index)
    {
        int promedio = this->promedio(ritmo, tiro, pase, regate, defensa, fisico);
        int forma = this->formaFisica(formaFisica);
        int conf = this->confianza(confianza);

        int valoracion = 0;

        if (forma == -1)
        {
            valoracion = 0;
        }
        else
        {
            valoracion = promedio + forma + conf;
        }

        if (valoracion > 100)
        {
            valoracion = 100;
        }

        bool extr = extranjero == "Si";

        this->jugadores[index] = new Jugador(valoracion, salario, extr);
        this->ordenar(index);
    }

    void procesar(int presupuesto, int cantExtranjeros)
    {
        int jugadoresNecesarios = 11;

        int ****dp = new int ***[cantJugadores + 1];
        for (int i = 0; i <= cantJugadores; i++)
        {
            dp[i] = new int **[presupuesto + 1];
            for (int p = 0; p <= presupuesto; p++)
            {
                dp[i][p] = new int *[cantExtranjeros + 1];
                for (int e = 0; e <= cantExtranjeros; e++)
                {
                    dp[i][p][e] = new int[jugadoresNecesarios + 1];
                    for (int n = 0; n <= jugadoresNecesarios; n++){
                        if (n == 0) 
                        {
                            dp[i][p][e][n] = 0;
                        }
                        else
                        {
                            dp[i][p][e][n] = INT_MIN;
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= cantJugadores; i++)
        {
            for (int p = 0; p <= presupuesto; p++)
            {
                for (int e = 0; e <= cantExtranjeros; e++)
                {
                    for (int n = 0; n <= jugadoresNecesarios; n++)
                    {
                        dp[i][p][e][n] = dp[i - 1][p][e][n];

                        Jugador *jug = jugadores[i - 1];
                        if (jug->salario <= p && n > 0)
                        {
                            if (!jug->extranjero || (jug->extranjero && e > 0))
                            {
                                int nuevoPresupuesto = p - jug->salario;
                                int nuevoExtranjeros;
                                if (jug->extranjero)
                                {
                                    nuevoExtranjeros = e - 1;
                                }
                                else
                                {
                                    nuevoExtranjeros = e;
                                }
                                dp[i][p][e][n] = max(dp[i][p][e][n],
                                                     dp[i - 1][nuevoPresupuesto][nuevoExtranjeros][n - 1] + jug->valoracion);
                            }
                        }
                    }
                }
            }
        }

        int mejorValoracion = dp[cantJugadores][presupuesto][cantExtranjeros][jugadoresNecesarios];
        cout << mejorValoracion / jugadoresNecesarios << endl;

    }
        
};

int main()
{
    int cantJugadores;
    cin >> cantJugadores;

    Jugadores *equipo = new Jugadores(cantJugadores);

    for (int i = 0; i < cantJugadores; i++)
    {
        int ritmo, tiro, pase, regate, defensa, fisico;
        cin >> ritmo >> tiro >> pase >> regate >> defensa >> fisico;

        string formaFisica;
        cin >> formaFisica;

        int salario;
        cin >> salario;

        string extranjero, confianza;
        cin >> extranjero >> confianza;

        equipo->add(ritmo, tiro, pase, regate, defensa, fisico, formaFisica, confianza, salario, extranjero, i);
    }

    int presupuesto, cantExtranjeros;

    cin >> presupuesto >> cantExtranjeros;

    equipo->procesar(presupuesto, cantExtranjeros);

    return 0;
}