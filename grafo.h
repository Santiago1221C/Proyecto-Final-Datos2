#ifndef GRAFO_H
#define GRAFO_H
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Grafo {
    private:
    // Estructura para almacenar la distancia y dificultad de una conexión
    struct Arista {
        int distancia;
        };
    // Estructura para almacenar la posición de un vértice (puede ser en un plano 2D, por ejemplo)
    struct Vertice {
        string nombre;
        int x, y; // Coordenadas (pueden ser diferentes según la representación)
    };

    // Mapa de adyacencia: cada nodo tiene un mapa de vecinos con sus respectivas aristas (distancia y dificultad)
    unordered_map<string, unordered_map<string, Arista>> grafo;
    string primerNodo;

    // Mapas para almacenar el estado en el algoritmo de Dijkstra
    unordered_map<string, int> costos;
    unordered_map<string, string> padres;
    // Función para calcular la distancia entre dos vértices con Manhatan
    int calcularDistancia(const Vertice& v1, const Vertice& v2) const;
    // Función para calcular el costo real considerando la distancia y dificultad
    void conectarTresVerticesCercanos(const Vertice& vertice);

    public:
    Grafo(); // Constructor
    ~Grafo(); // Destructor

    // Métodos principales
    void insertarArista(const string& nodo, const string& vecino, int distancia);
    void setNodoInicial(const string& nodoInicial);
    void insertarVertice(const string& nombre, int x, int y);
    void generarAristasDirigidas();
    void dijkstra(const string& nodoInicio);
    void mostrarCamino(const string& nodoDestino) const;
};


#endif // GRAFO_H