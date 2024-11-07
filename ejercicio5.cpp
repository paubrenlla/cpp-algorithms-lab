#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "tads/List.h"

using namespace std;

class Misiones
{
private:
    struct Mision
    {
        int id;
        string nombre;
        int idCiudad;
        bool completada;

        int previasPorCompletar;

        List<int>* idPosteriores;

        Mision(int unId, string unNombre, int unaCiudad) : id(unId), previasPorCompletar(0), nombre(unNombre), idCiudad(unaCiudad), completada(false) {};
        Mision(int unId) : id(unId), previasPorCompletar(0), nombre(NULL), idCiudad(0), completada(false) {};
    };
    
    struct Conexion
    {
        int idDestino;
        int costo;
        Conexion* siguiente;

        Conexion(int idDest, int cost) : idDestino(idDest), costo(cost), siguiente(NULL) {};
        Conexion(int idDest, int cost, Conexion* sig) : idDestino(idDest), costo(cost), siguiente(sig) {};
    };

    struct Ciudad
    {
        int id;
        string nombre;

        int cantConexiones;
        Conexion* conexiones;

        Ciudad(int unId, string unNombre) : id(unId), nombre(unNombre), cantConexiones(0), conexiones(NULL) {};
        Ciudad(int unId) : id(unId), nombre(NULL), cantConexiones(0), conexiones(NULL) {};
    };
    
    int ciudadActual;
    Ciudad** ciudades;
    Mision** misiones;
    int cantCiudades;
    int misionesTotales;
    int misionesRestantes;

public:
    Misiones(int cantCiudades, int cantMisiones)
    {
        this->ciudadActual = 0;
        this->cantCiudades = 0;
        this->misionesTotales = 0;
        this->misionesRestantes = 0;

        this->ciudades = new Ciudad*[cantCiudades + 1];
        for (int i = 0; i != cantCiudades; i++)
        {
            this->ciudades[i] = NULL;
        }
        for (int i = 0; i != cantMisiones; i++)
        {
            this->misiones[i] = NULL;
        }
    }

    void addMision(int unId, string unNombre, int idCiudad)
    {
        if (this->misiones[unId] == NULL)
        {
            this->misiones[unId] = new Mision(unId, unNombre, idCiudad);
        }
        else
        {
            this->misiones[unId]->nombre = unNombre;
            this->misiones[unId]->idCiudad = idCiudad;
        }

        this->misionesTotales++;
        this->misionesRestantes++;
    }

    void addPosMision(int idMision, int idPosMision)
    {
        if (this->misiones[idPosMision] == NULL)
        {
            this->misiones[idPosMision] = new Mision(idPosMision);
        }

        this->misiones[idPosMision]->previasPorCompletar++;
        this->misiones[idMision]->idPosteriores->insert(idPosMision);
    }

    void addCiudad(int unId, string unNombre)
    {
        if (this->ciudades[unId] == NULL)
        {
            this->ciudades[unId] = new Ciudad(unId, unNombre);
        }
        else 
        {
            this->ciudades[unId]->nombre = unNombre;
        }

        this->cantCiudades++;
    }

    void setCiudadActual(int idCiudad)
    {
        this->ciudadActual = idCiudad;
    }

    void addConexion(int origen, int destino, int costo)
    {
        if (this->ciudades[origen] == NULL)
        {
            this->ciudades[origen] = new Ciudad(origen);
        }
        if (this->ciudades[destino] == NULL)
        {
            this->ciudades[destino] = new Ciudad(destino);
        }

        Conexion* aux = NULL;
        //Origen - Destino
        aux = this->ciudades[origen]->conexiones;
        this->ciudades[origen]->conexiones = new Conexion(destino, costo, aux);
        this->ciudades[origen]->cantConexiones++;

        //Destino - Origen
        aux = this->ciudades[destino]->conexiones;
        this->ciudades[destino]->conexiones = new Conexion(origen, costo, aux);
        this->ciudades[destino]->cantConexiones++;
    }

    void setOrigen(int idCiudad)
    {
        this->ciudadActual = idCiudad;
    }

    bool esVacio()
    {
        return this->misionesRestantes == 0;
    }
    
    string completarMision()
    {
        return "";
    }


};

int main()
{
    Misiones* misiones = new Misiones(50, 200);

    int cantMisiones;
    cin >> cantMisiones;

    for (int i = 0; i < cantMisiones; i++)
    {
        int idMision;
        string nombreMision;
        int idCiudad;

        cin >> idMision >> nombreMision >> idCiudad;
        misiones->addMision(idMision, nombreMision, idCiudad);

        int posMision;
        while (posMision != 0)
        {
            misiones->addPosMision(idMision, posMision);
        }
    }

    int cantCiudades;
    cin >> cantCiudades;
    
    int ciudadOrigen;
    cin >> ciudadOrigen;
    
    misiones->setOrigen(ciudadOrigen);

    for (int i = 0; i < cantCiudades; i++)
    {
        int idCiudad;
        string nombreCiudad;

        cin >> idCiudad >> ciudadOrigen;
        misiones->addCiudad(idCiudad, nombreCiudad);
    }

    int cantConexiones;
    cin >> cantConexiones;

    for (int i = 0; i < cantConexiones; i++)
    {
        int cOrigen;
        int cDestino;
        int costo;

        cin >> cOrigen >> cDestino >> costo;

        misiones->addConexion(cOrigen, cDestino, costo);

    }
    
    while (misiones->esVacio() == false)
    {
        cout << misiones->completarMision() << endl;
    }
    

    return 0;
}