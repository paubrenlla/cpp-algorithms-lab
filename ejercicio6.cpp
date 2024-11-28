#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "tads/MinHeap.cpp"

using namespace std;

class Morfeo
{
private:

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
        
        Ciudad(int id, string nombre) : id(id), nombre(nombre), cantConexiones(0), conexiones(NULL) {};
    };
    
    int cantCiudades;
    Ciudad** ciudades;

    int start;
    int entity;
    int team;
    int end;
    
    int** dijkstra(int origen, Ciudad** grafo)
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

                Conexion* it = grafo[top]->conexiones;
                while (it != NULL)
                {
                    int v = it->idDestino;
                    int peso = it->costo;
                    
                    if (!visitado[v] && costoVengo[v][0] > costoVengo[top][0] + peso)
                    {
                        costoVengo[v][0] = costoVengo[top][0] + peso;
                        costoVengo[v][1] = top;
                        cola->add(v, costoVengo[v][0]);
                    }
                    it = it->siguiente;
                }
            }
        }

        delete[] visitado;
        return costoVengo;       
    }

    void actualizar(int origen, int destino, Ciudad**& grafo, int q)
    {
        if (q == 2)
        {
            return;
        }

        Conexion* aux = grafo[origen]->conexiones;
        while (aux->idDestino != destino)
        {
            aux = aux->siguiente;
        }
        aux->costo = aux->costo * 2;

        this->actualizar(destino, origen, grafo, q + 1);
    }
    
    string caminoRec(int** dijkstraResults, int v, Ciudad**& grafo)
    {
        if (dijkstraResults[v][1] == -1)
        {
            return this->ciudades[v]->nombre + " -> ";
        }
        else
        {
            this->actualizar(v, dijkstraResults[v][1], grafo, 0);
            return caminoRec(dijkstraResults, dijkstraResults[v][1], grafo) + this->ciudades[v]->nombre + " -> ";
        }
    }

    Ciudad** copiaCiudades()
    {
        Ciudad** copia = new Ciudad*[this->cantCiudades];
        
        for (int i = 1; i <= this->cantCiudades; i++)
        {
            copia[i] = new Ciudad(this->ciudades[i]->id, this->ciudades[i]->nombre);

            Conexion* aux = this->ciudades[i]->conexiones;
            Conexion* ultimo = NULL;
            
            while (aux != NULL)
            {
                Conexion* nuevaConexion = new Conexion(aux->idDestino, aux->costo);

                if (ultimo == NULL)
                {
                    copia[i]->conexiones = nuevaConexion;
                }
                else
                {
                    ultimo->siguiente = nuevaConexion;
                }
                ultimo = nuevaConexion;
                aux = aux->siguiente;
            }
            copia[i]->cantConexiones = this->ciudades[i]->cantConexiones;
        }
        return copia;
    }

public:
    Morfeo(int cantCiudades)
    {
        this->ciudades = new Ciudad*[cantCiudades + 1];

        for (int i = 0; i <= cantCiudades; i++) 
        { 
            this->ciudades[i] = NULL;
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
        Conexion* aux = this->ciudades[origen]->conexiones;
        this->ciudades[origen]->conexiones = new Conexion(destino, costo, aux);
        this->ciudades[origen]->cantConexiones++;
    }
    
    void procesar()
    {
        //start-team-entity-end
        Ciudad** step = copiaCiudades();
        int sumaStep = 0;

        int** dijkstraST = this->dijkstra(this->start, step);
        sumaStep += dijkstraST[this->team][0];
        string start_team = this->caminoRec(dijkstraST, this->team, step);
        delete dijkstraST;

        int** dijkstraTE = this->dijkstra(this->team, step);
        sumaStep += dijkstraTE[this->entity][0];
        string team_entity = this->caminoRec(dijkstraTE, this->entity, step);
        delete dijkstraTE;

        int** dijkstraEP = this->dijkstra(this->entity, step);
        sumaStep += dijkstraEP[this->end][0];
        string entity_end = this->caminoRec(dijkstraEP, this->end, step);
        delete dijkstraEP;

        //start-entity-team-end
        Ciudad** setp = copiaCiudades();
        int sumaSetp = 0;

        int** dijkstraSE = this->dijkstra(this->start, setp);
        sumaSetp += dijkstraSE[this->entity][0];
        string start_entity = this->caminoRec(dijkstraSE, this->entity, setp);
        delete dijkstraSE;

        int** dijkstraET = this->dijkstra(this->entity, setp);
        sumaSetp += dijkstraET[this->team][0];
        string entity_team = this->caminoRec(dijkstraET, this->team, setp);
        delete dijkstraET;

        int** dijkstraTP = this->dijkstra(this->team, setp);
        sumaSetp += dijkstraTP[this->end][0];
        string team_end = this->caminoRec(dijkstraTP, this->end, setp);
        delete dijkstraTP;

        if (sumaStep < sumaSetp)
        {
            string descripcion = "BE11, la mejor ruta es buscar equipo, Desactivar la Entidad y punto de extraccion con un costo de " + std::to_string(sumaStep);
            string alt = "La otra opcion tiene un costo de " + std::to_string(sumaSetp);
            cout << descripcion << endl;
            cout << alt << endl;
            cout << "Paso 1: " +start_team + "Buscar equipo" << endl;
            cout << "Paso 2: " + team_entity + "Desactivar la Entidad" << endl;
            cout << "Paso 3: " + entity_end + "Ir a Punto de extraccion" << endl;
        }
        else
        {
            string descripcion = "BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de " + std::to_string(sumaSetp);
            string alt = "La otra opcion tiene un costo de " + std::to_string(sumaStep);
            cout << descripcion << endl;
            cout << alt << endl;
            cout << "Paso 1: " + start_entity + "Desactivar la Entidad" << endl;
            cout << "Paso 2: " + entity_team + "Buscar equipo" << endl;
            cout << "Paso 3: " + team_end + "Ir a Punto de extraccion" << endl;
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
        int id;
        string nombre;

        cin >> id >> nombre;

        morfeo->addCiudad(id, nombre);
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
        morfeo->addConexion(idDestino, idOrigen, costo);
    }
    
    morfeo->procesar();

    return 0;
}