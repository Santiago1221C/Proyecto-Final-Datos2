#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <limits>
#include <queue>
#include "grafo.h"
#include "tablero.h"
#include "cereza.h"
using namespace std;
extern bool debugMode;

Grafo::Grafo() {} // Constructor
Grafo::~Grafo() {} // Destructor

// Calcular la distancia Manhattan entre dos vértices
int Grafo::calcularDistancia(const Vertice& v1, const Vertice& v2) const {
    return abs(v1.x - v2.x) + abs(v1.y - v2.y); // Formula de distancia Manhatan |x2-x1| + |y2-y1| + | y2-y1|
}

// Encontrar tres vértices más cercanos 
void Grafo::TresVerticesCercanos(const Vertice& vertice) {
    vector<pair<int, string>> distancias;
    for (const auto& [nombre, v] : vertices) {
        if (nombre != vertice.nombre) {
            distancias.push_back({calcularDistancia(vertice, v), nombre});  //calcular distancia entre el vertice actual y el siguiente
        }
    }
    sort(distancias.begin(), distancias.end());
    for (int i = 0; i < 3 && i < distancias.size(); ++i) {
        insertarArista(vertice.nombre, distancias[i].second, distancias[i].first);  //insertar arista entre el vertice actual y el siguiente
    }
}

// Insertar un vértice
void Grafo::insertarVertice(const string& nombre, int x, int y) {
    vertices[nombre] = {nombre, x, y};
    if (debugMode) {
        cout << "Vértice agregado: " << nombre << " en (" << x << ", " << y << ")" << endl; 
        // Imprime todos los nodos
        for (const auto& [key, vertice] : vertices) {
            cout << "Clave: " << key << " -> (" << vertice.x << ", " << vertice.y << ")" << endl;  //imprime la clave dle nodo y su poscion , para ver si se agrego el nodo correctamente
        }
    }
}

// Insertar una arista
void Grafo::insertarArista(const string& nodo, const string& vecino, int distancia) {
        grafo[nodo][vecino] = {distancia};
    if (debugMode) {
        cout << "Arista agregada entre " << nodo << " y " << vecino << " con distancia " << distancia << endl;
        // Imprime todas las aristas del nodo
        for (const auto& [key, vecinos] : grafo) { 
            cout << "Nodo: " << key << " -> ";
            for (const auto& [v, arista] : vecinos) {
                cout << v << " (Distancia: " << arista.distancia << "), ";
            }
            cout << endl;
        }
    }
}

// Generar aristas dirigidas a los tres vértices más cercanos para cada nodo
void Grafo::generarAristasDirigidas() {
    for (const auto& [nombre, vertice] : vertices) { // Generar aristas a los nodos adyacentes 
    for (const auto& [nombreVecino, verticeVecino] : vertices) { 
        if (nombre != nombreVecino) { int distancia = calcularDistancia(vertice, verticeVecino); 
        insertarArista(nombre, nombreVecino, distancia); 
        } 
    } 
}
}

// Establecer el nodo inicial
void Grafo::setNodoInicial(const string& nodoInicial) {
    primerNodo = nodoInicial;
}

// Algoritmo de Dijkstra para encontrar el camino más corto desde un nodo inicial
vector<string> Grafo::dijkstra(const string& nodoInicial, const string& nodoDestino, Tablero& tablero) const {
    // Validar existencia de los nodos
    if (vertices.find(nodoInicial) == vertices.end() || vertices.find(nodoDestino) == vertices.end()) {
        if (debugMode) {
            cout << "Error: Nodo inicial o destino no existen en el grafo." << endl;
        }
        return {};
    }

    // Inicialización
    unordered_map<string, int> distancias;
    unordered_map<string, string> previo;
    unordered_set<string> visitados; // Nodos ya procesados

    for (const auto& [nombre, _] : vertices) {
        distancias[nombre] = numeric_limits<int>::max();
    }
    distancias[nodoInicial] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> cola;
    cola.push({0, nodoInicial});

    while (!cola.empty()) {
        auto [distanciaActual, nodoActual] = cola.top();
        cola.pop();

        // Verificar si ya fue visitado
        if (visitados.find(nodoActual) != visitados.end()) continue;
        visitados.insert(nodoActual);

        // Marcar como visitado en el tablero
        int xActual = obtenerDireccionX(nodoActual);
        int yActual = obtenerDireccionY(nodoActual);
        tablero.marcarVisitado(xActual, yActual);

        // Si alcanzamos el destino, no necesitamos procesar más
        if (nodoActual == nodoDestino) break;

        // Procesar vecinos
        if (grafo.find(nodoActual) != grafo.end()) {
            for (const auto& [vecino, arista] : grafo.at(nodoActual)) {
                if (visitados.find(vecino) != visitados.end()) continue;

                int nuevaDistancia = distanciaActual + arista.distancia;
                if (nuevaDistancia < distancias[vecino]) {
                    distancias[vecino] = nuevaDistancia;
                    previo[vecino] = nodoActual;
                    cola.push({nuevaDistancia, vecino});
                }
            }
        }
    }

    // Reconstruir el camino
    vector<string> camino;
    if (previo.find(nodoDestino) == previo.end()) {
        if (debugMode) {
            cout << "No hay camino desde " << nodoInicial << " hasta " << nodoDestino << endl;
        }
        return {};
    }

    for (string at = nodoDestino; at != nodoInicial; at = previo[at]) {
        camino.push_back(at);
    }
    camino.push_back(nodoInicial);
    reverse(camino.begin(), camino.end());

    return camino;
}

// Obtener el siguiente nodo en el camino más corto
string Grafo::obtenerSiguienteNodo(const string& nodoActual, const string& nodoDestino, Tablero& tablero) {
    vector<string> camino = dijkstra(nodoActual,nodoDestino, tablero);
    if (camino.size() > 1) {
        return camino[1]; // El siguiente nodo en el camino
    }
    return nodoActual; // Si no hay camino, quedarse en el mismo lugar
}

// Obtener coordenada X de un nodo
int Grafo::obtenerDireccionX(const string& nodo) const { 
    if (vertices.find(nodo) != vertices.end()) {
        return vertices.at(nodo).x;
    } else {
        if (debugMode==false) {
            cout << "Error: El nodo " << nodo << " no existe en vertices." << endl;
        }
        return -1; // devuelve -1 si el nodo no existe
    }
}

// Obtener coordenada Y de un nodo
int Grafo::obtenerDireccionY(const string& nodo) const {
    if (vertices.find(nodo) != vertices.end()) {
        return vertices.at(nodo).y;
    } else {
        if (debugMode==false) {
            cout << "Error: El nodo " << nodo << " no existe en vertices." << endl;
        }
        return -1; // devuelve -1 si el nodo no existe
    }
}

// Agregar un fantasma en una posición aleatoria
void Grafo::agregarFantasmaAleatorio(Grafo& grafo, Tablero& tablero, int maxFilas, int maxColumnas, const string& pacmanNodo, int cerezaX , int cerezaY) {
    int x, y;
    string nombreFantasma = "F" + to_string(rand() % 100); //nombre aletorio a los fantasmas 
    do {
        x = rand() % maxFilas;
        y = rand() % maxColumnas;
    } while (tablero.obtenerPosicion(x, y) != '-' || 
            (x == grafo.obtenerDireccionX(pacmanNodo) && y == grafo.obtenerDireccionY(pacmanNodo)) ||  
            (x == cerezaX && y == cerezaY));
    grafo.insertarVertice(nombreFantasma, x, y);
    tablero.actualizarPosicion(x, y, 'F');
}
