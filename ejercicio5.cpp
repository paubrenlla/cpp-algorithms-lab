#include <cassert>
#include <string>
#include <iostream>
#include <climits>
#include "tads/ListImp.cpp"
#include "tads/Iterator.cpp"
#include "tads/MinHeap.cpp"

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

        ListImp<int>* idPosteriores;

        Mision(int unId) : id(unId), previasPorCompletar(0), nombre(""), idCiudad(0), completada(false) 
        {
            idPosteriores = new ListImp<int>();
        }
        Mision(int unId, string unNombre, int unaCiudad): id(unId), previasPorCompletar(0), nombre(unNombre), idCiudad(unaCiudad), completada(false)
        {
            idPosteriores = new ListImp<int>();
        }

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

        Ciudad(int unId) : id(unId), nombre(NULL), cantConexiones(0) {};
        Ciudad(int unId, string unNombre) : id(unId), nombre(unNombre), cantConexiones(0), conexiones(NULL) {};
    };
    
    int ciudadActual;
    Ciudad** ciudades;
    Mision** misiones;
    int cantCiudades;
    int misionesTotales;
    int misionesRestantes;
    int tiempoViaje;

public:
    Misiones(int cantCiudades, int cantMisiones)
    {
        this->ciudadActual = 0;
        this->cantCiudades = 0;
        this->misionesTotales = 0;
        this->misionesRestantes = 0;
        this->tiempoViaje = 0;

        this->ciudades = new Ciudad*[cantCiudades + 1];
        this->misiones = new Mision*[cantMisiones + 1];
 
        for (int i = 0; i <= cantCiudades; i++)
        {
            this->ciudades[i] = NULL;
        }
        for (int i = 0; i <= cantMisiones; i++)
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
    
    int mejorMisionDeCiudad(int ciudad)
    {
        int nroMision = this->misionesTotales + 1;

        for (int i = 1; i <= this->misionesTotales; i++)
        {
            if (this->misiones[i] != NULL && this->misiones[i]->previasPorCompletar == 0 && this->misiones[i]->completada == false && this->misiones[i]->id < nroMision)
            {
                nroMision = i;
            }
        }

        if (nroMision == this->misionesTotales + 1)
        {
            return -1;
        }
        return nroMision;
    }

    string completarMision()
    {
        int** dijkstraResutls = this->dijkstra(ciudadActual);
        int menorCosto = INT_MAX;
        int mejorCiudad = 0;
        int hacerMision = this->misionesTotales + 1;
        for (int i = 1; i <= this->cantCiudades; i++)
        {
            if (this->ciudades[i] != NULL)
            {
                int mejorMision = this->mejorMisionDeCiudad(i);

                if (mejorMision != -1)
                {
                    if (dijkstraResutls[i][0] < menorCosto)
                    {   
                        mejorCiudad = i;
                        menorCosto = dijkstraResutls[i][0];
                        hacerMision = mejorMision;
                    }
                    else if (dijkstraResutls[i][0] == menorCosto && mejorMision < hacerMision)
                    {
                        mejorCiudad = i;
                        menorCosto = dijkstraResutls[i][0];
                        hacerMision = mejorMision;
                    }
                }
            }
        }

        for (int i = 1; i <= this->cantCiudades; i++)
        {
            cout << dijkstraResutls[i][1] << " - ";
        }
        cout << endl;
        

        cout << "procesamiento" << endl;
        string setCompleted = this->marcarCompletada(hacerMision);
        cout << "setCompleted " << setCompleted << endl;
        string caminoMasCorto = this->getCaminoMasCorto(dijkstraResutls, mejorCiudad);
        cout << "caminoMasCorto: " << caminoMasCorto << endl;
        string destinoMision = "- " + this->misiones[this->ciudadActual]->nombre;
        cout << "destinoMision " << destinoMision<< endl;
        string tiempo = " - Tiempo de viaje: " + std::to_string(dijkstraResutls[mejorCiudad][0]);
        cout << "tiempo " << tiempo << endl;

        return setCompleted + caminoMasCorto + destinoMision + tiempo;
    }

    string getCaminoMasCorto(int** dijkstraResults, int ciudad)
    {
        this->tiempoViaje += dijkstraResults[ciudad][0];
        string retorno;

        int aux = ciudad;
        while (aux != this->ciudadActual)
        {
            cout << this->misiones[aux]->nombre << endl;
            retorno = this->misiones[aux]->nombre + " -> " + retorno;
            aux = dijkstraResults[aux][1];
        }

        this->ciudadActual = ciudad;

        return retorno;
    }

    string marcarCompletada(int mision)
    {
        this->misiones[mision]->completada = true;
        
        ListImp<int>* aux = this->misiones[mision]->idPosteriores;
        for(int i = 0; i < aux->getSize(); i++)
        {
            this->misiones[aux->get(i)]->previasPorCompletar--; 
        }

        return "Mision: " + this->misiones[mision]->nombre + " ";
    }

    string getNombreCiudadActual()
    {   
        return this->ciudades[this->ciudadActual]->nombre;
    }

    int getTiempoViaje()
    {
        return this->tiempoViaje;
    }

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

        MinHeapImp* cola = new MinHeapImp(this->cantCiudades);
        cola->insertar(origen);

        while (cola->estaVacio() == false)
        {
            int top = cola->tope();
            cola->eliminarTope();

            if (!visitado[top])
            {
                visitado[top] = true;

                Iterator<Conexion>* it = new Iterator<Conexion>(this->ciudades[origen]->conexiones);
                while (it->hasNext())
                {
                    Conexion c = it->next();
                    int v = c.idDestino;
                    int peso = c.costo;
                    
                    if (!visitado[v] && costoVengo[v][0] > costoVengo[top][0] + peso)
                    {
                        costoVengo[v][0] = costoVengo[top][0] + peso;
                        costoVengo[v][1] = top;
                        cola->insertar(v);
                    }
                }
                delete it;
            }
        }

        delete[] visitado;
        return costoVengo;       
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
        cin >> posMision;
        while (posMision != 0)
        {
            misiones->addPosMision(idMision, posMision);
            cin >> posMision;
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

        cin >> idCiudad >> nombreCiudad;
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
    
    cout << "Ciudad inicial: " << misiones->getNombreCiudadActual() << endl;

    while (!misiones->esVacio())
    {
        cout << misiones->completarMision() << endl;
    }
    cout << "Misiones ejecutadas con exito." << endl;
    cout << "Tiempo total de viaje: " << misiones->getTiempoViaje() << endl;
    

    return 0;
}