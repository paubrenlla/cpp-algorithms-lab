#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "tads/MinHeap.cpp"

using namespace std;

class Morfeo
{
private:

    struct Ciudad
    {
        int idCiudad;
        string nombreCiudad;
        
        Ciudad(int id, string nombre) : idCiudad(id), nombreCiudad(nombre) {};
    };
    
    int cantCiudades;
    Ciudad** ciudades;
    int ** conexiones;

    int start;
    int entity;
    int team;
    int end;
    
    int** dijkstra(int origen)
    {
        bool *visitado = new bool[this->cantCiudades + 1]();
        int** costoVengo = new int*[this->cantCiudades + 1]();

        for (int v = 1; v <= this->cantCiudades; v++)
        {
            visitado[v] = false;

            costoVengo[v] = new int[2];
            costoVengo[v][0] = INT_MAX;
            costoVengo[v][1] = -1;
        }
        costoVengo[origen][0] = 0;

        MinHeap* cola = new MinHeap(this->cantCiudades);
        cola->add(origen, 0);

        while (!cola->isEmpty())
        {
            int top = cola->top();

            if (!visitado[top])
            {
                visitado[top] = true;

                for (int v = 1; v <= this->cantCiudades; v++)
                {
                    if (this->conexiones[top][v] != -1)
                    {
                        int peso = this->conexiones[top][v];
                        
                        if (!visitado[v] && costoVengo[v][0] > costoVengo[top][0] + peso)
                        {
                            costoVengo[v][0] = costoVengo[top][0] + peso;
                            costoVengo[v][1] = top;
                            cola->add(v, costoVengo[v][0]);
                        }
                    }
                }
            }
        }

        delete[] visitado;
        return costoVengo;       
    }
    
    string caminoRec(int** dijkstraResults, int v)
    {
        if (dijkstraResults[v][1] == -1)
        {
            return this->ciudades[v]->nombreCiudad + " -> ";
        }
        else
        {
            return caminoRec(dijkstraResults, dijkstraResults[v][1]) + this->ciudades[v]->nombreCiudad + " -> ";
        }
    }

public:
    Morfeo(int cantCiudades)
    {
        this->ciudades = new Ciudad*[cantCiudades + 1];
        this->conexiones = new int*[cantCiudades + 1];

        for (int i = 0; i <= cantCiudades; i++) 
        { 
            this->ciudades[i] = NULL;
            this->conexiones[i] = new int[cantCiudades + 1];

            for (int j = 0; j <= cantCiudades; j++) 
            { 
                this->conexiones[i][j] = -1;
            }
        }

        this->cantCiudades = cantCiudades;
        this->start = 0;
        this->entity = 0;
        this->team = 0;
        this->end = 0;
    }

    void addCiudad(int id, string nombre)
    {
        this->ciudades[id] = new Ciudad(id, nombre);
    }

    void addLocations(int s, int e, int t, int p)
    {
        this->start = s;
        this->entity = e;
        this->team = t;
        this->end = p;
    }

    void addConexion(int origen, int destino, int costo)
    {
        this->conexiones[origen][destino] = costo;
        this->conexiones[destino][origen] = costo;
    }

    string procesar()
    {
        int** dijkstraStart = this->dijkstra(this->start);
        int** dijkstraEntity = this->dijkstra(this->entity);
        int** dijkstraTeam = this->dijkstra(this->team);

        //Opcion inicio-team-entity-end
        int startTeam = dijkstraStart[this->team][0];
        int teamEntity = dijkstraTeam[this->entity][0];
        int entityEnd = 2 * dijkstraEntity[this->end][0];

        int suma1Team = startTeam + teamEntity + entityEnd;

        //Opcion inicio-entity-team-end
        int startEntity = dijkstraStart[this->entity][0];
        int entityTeam = 2 * dijkstraEntity[this->team][0];
        int teamEnd = 2 * dijkstraTeam[this->end][0];

        int suma1Entity = startEntity + entityTeam + teamEnd;

        //eleccion camino
        if (suma1Team < suma1Entity)
        {
            string descripcion = "BE11, la mejor ruta es buscar equipo, Desactivar la Entidad y punto de extraccion con un costo de " + std::to_string(suma1Team) + "\n";
            string alt = "La otra opcion tiene un costo de " + std::to_string(suma1Entity) + "\n";
            string start_team = "Paso 1: " + this->caminoRec(dijkstraStart, this->team) + "Buscar equipo \n";
            string team_entity = "Paso 2: " + this->caminoRec(dijkstraTeam, this->entity) + "Desactivar la Entidad \n";
            string entity_end = "Paso 3: " + this->caminoRec(dijkstraEntity, this->end) + "Ir a Punto de extraccion \n";
            return descripcion + alt + start_team + team_entity + entity_end;
        }
        if (suma1Entity < suma1Team)
        {
            string descripcion = "BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de " + std::to_string(suma1Entity) + "\n";
            string alt = "La otra opcion tiene un costo de " + std::to_string(suma1Team) + "\n";
            string start_entity = "Paso 1: " + this->caminoRec(dijkstraStart, this->entity) + "Desactivar la Entidad \n";
            string entity_team = "Paso 2: " + this->caminoRec(dijkstraEntity, this->team) + "Buscar equipo \n";
            string team_end = "Paso 3: " + this->caminoRec(dijkstraTeam, this->end) + "Ir a Punto de extraccion \n";
            return descripcion + alt + start_entity + entity_team + team_end;
        }

    }

    

};

int main()
{
    int cantCiudades;
    cin >> cantCiudades;

    Morfeo* morfeo = new Morfeo(cantCiudades);

    for (int i = 0; i < cantCiudades; i++)
    {
        int idCiudad;
        string nombreCiudad;

        cin >> idCiudad >> nombreCiudad;

        morfeo->addCiudad(idCiudad, nombreCiudad);
    }

    int comiento;
    cin >> comiento;

    int entidad;
    cin >> entidad;

    int restoEquipo;
    cin >> restoEquipo;

    int puntoExtraccion;
    cin >> puntoExtraccion;

    morfeo->addLocations(comiento, entidad, restoEquipo, puntoExtraccion);

    int conexiones;
    cin >> conexiones;

    for (int i = 0; i < conexiones; i++)
    {
        int idOrigen;
        int idDestino;
        int costo;

        cin >> idOrigen >> idDestino >> costo;

        morfeo->addConexion(idOrigen, idDestino, costo);
    }
    
    cout << morfeo->procesar() << endl;

    return 0;
}