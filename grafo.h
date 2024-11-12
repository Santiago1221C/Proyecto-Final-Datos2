#ifndef GRAFO_H
#define GRAFO_H
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include "tablero.h"
using namespace std;

struct Vertice {
    std::string nombre;
    int x, y;
};

struct Arista {
    int distancia;
};

class Grafo {
    private:
    std::unordered_map<std::string, Vertice> vertices;  // Mapa de vértices
    std::unordered_map<std::string, std::unordered_map<std::string, Arista>> grafo;  // Mapa de adyacencia para aristas
    std::string primerNodo;  // Nodo inicial para el grafo
    public:
    Grafo(); // Constructor
    ~Grafo(); // Destructor

    // Métodos 
    void insertarVertice(const std::string& nombre, int x, int y); 
    void insertarArista(const std::string& nodo, const std::string& vecino, int distancia); 
    void generarAristasDirigidas(); 
    void setNodoInicial(const std::string& nodoInicial); 
    int calcularDistancia(const Vertice& v1, const Vertice& v2)  const; 
    void TresVerticesCercanos(const Vertice& vertice); 
    std::unordered_map<std::string, int> dijkstra(const std::string& nodoInicial) const; 
    std::string obtenerSiguienteNodo(const std::string& nodoActual, const std::string& nodoDestino); 
    int obtenerDireccionX(const std::string& nodo) const; 
    int obtenerDireccionY(const std::string& nodo) const;  
    void agregarFantasmaAleatorio(Grafo& grafo, Tablero& tablero, int maxFilas, int maxColumnas, const std::string& pacmanNodo, int cerezaX, int cerezaY); 
};
#endif // GRAFO_H