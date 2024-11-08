#include <iostream>
#include <unordered_map>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits>
#include "grafo.h"
using namespace std;

class Grafo {
private:
    struct Arista {
        int distancia;
    };
    // Estructura para almacenar la posición de un vértice 
    struct Vertice {
        string nombre;
        int x, y; // Coordenadas (pueden ser diferentes según la representación)
    };
    unordered_map<string, unordered_map<string, Arista>> grafo;
    unordered_map<string, Vertice> vertices; // Información de cada vértice
    string primerNodo;
    // Función para calcular la distancia entre dos vértices con Manhatan
    int calcularDistancia(const Vertice& v1, const Vertice& v2) const {
    return abs(v1.x - v2.x) + abs(v1.y - v2.y); // Formula de distancia Manhatan |x2-x1| + |y2-y1| + | y2-y1|
    }
    // Función para encontrar los tres vértices más cercanos y crear aristas dirigidas
    void conectarTresVerticesCercanos(const Vertice& vertice) {
        vector<pair<int, string>> distancias; // Distancias a otros vértices
    // Calcula la distancia entre el vértice actual y todos los demás
    for (const auto& [nombre, v] : vertices) {
        if (nombre != vertice.nombre) { // No considerarse a sí mismo
            int distancia = calcularDistancia(vertice, v);
            distancias.push_back({distancia, nombre});
        }
    }
        // Ordenar por distancia
        sort(distancias.begin(), distancias.end());
        // Conectar con los tres vértices más cercanos
        for (int i = 0; i < 3 && i < distancias.size(); ++i) {
            const auto& [distancia, vecino] = distancias[i];
            insertarArista(vertice.nombre, vecino, distancia);
        }
    }

public:
    Grafo() {}
    ~Grafo() {}
    // Inserta un vértice con su posición en el plano
    void insertarVertice(const string& nombre, int x, int y) {
        vertices[nombre] = {nombre, x, y};
    }
    // Inserta una arista en el grafo
    void insertarArista(const string& nodo, const string& vecino, int distancia) {
        grafo[nodo][vecino] = {distancia};
    }
    // Genera las aristas dirigidas a los tres vértices más cercanos para cada vértice
    void generarAristasDirigidas() {
        for (const auto& [nombre, vertice] : vertices) {
            conectarTresVerticesCercanos(vertice);
        }
    }

    void setNodoInicial(const string& nodoInicial) {
        primerNodo = nodoInicial;
    }

    // Implementación del algoritmo de Dijkstra
    unordered_map<string, int> dijkstra(const string& nodoInicial) {
    unordered_map<string, int> distancias;
    for (const auto& [nombre, _] : vertices) {
        distancias[nombre] = numeric_limits<int>::max();
    }
    distancias[nodoInicial] = 0;

    // Cola de prioridad para procesar los vértices por distancia mínima
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> cola;
    cola.push({0, nodoInicial});

    while (!cola.empty()) {
        auto [distanciaActual, nodoActual] = cola.top();
        cola.pop();

        if (distanciaActual > distancias[nodoActual]) continue;

        for (const auto& [vecino, arista] : grafo[nodoActual]) {
            int nuevaDistancia = distanciaActual + arista.distancia;

        if (nuevaDistancia < distancias[vecino]) {
            distancias[vecino] = nuevaDistancia;
            cola.push({nuevaDistancia, vecino});
        }
    }
    }
    return distancias;
}
};
