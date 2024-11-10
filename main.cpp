#include <iostream>
#include <vector>
#include <string>
#include "grafo.h"
#include "cereza.h"

using namespace std;

// Función para agregar un fantasma en una posición aleatoria
void agregarFantasmaAleatorio(Grafo& grafo, vector<vector<char>>& tablero, int maxFilas, int maxColumnas) {
    int x, y;
    string nombreFantasma = "F" + to_string(rand() % 100); // Crear un nombre único para el fantasma

    // Buscar una posición aleatoria que esté vacía
    do {
        x = rand() % maxFilas;
        y = rand() % maxColumnas;
    } while (tablero[x][y] != '-');

    // Insertar el nuevo fantasma en el grafo y el tablero
    grafo.insertarVertice(nombreFantasma, x, y);
    tablero[x][y] = 'F';
}

int main() {
    int filas = 5;
    int columnas = 5;

    Grafo grafo;
    vector<vector<char>> tablero(filas, vector<char>(columnas, '-'));

    // Inicializar Pac-Man y un fantasma inicial
    string pacmanNodo = "P";
    grafo.insertarVertice(pacmanNodo, 0, 0);
    tablero[0][0] = 'P';

    string fantasmaNodo = "F1";
    grafo.insertarVertice(fantasmaNodo, filas - 1, columnas - 1);
    tablero[filas - 1][columnas - 1] = 'F';

    // Crear la cereza en una posición aleatoria
    Cereza cereza(rand() % filas, rand() % columnas);
    tablero[cereza.getX()][cereza.getY()] = 'C';

    // Imprimir el tablero inicial
    cout << "Tablero inicial:" << endl;
    imprimirTablero(tablero);

    // Simulación del movimiento de Pac-Man
    string nodoActual = pacmanNodo;
    while (nodoActual != fantasmaNodo) {
        // Obtener siguiente movimiento de Pac-Man
        string siguienteNodo = grafo.obtenerSiguienteNodo(nodoActual, fantasmaNodo);

        // Convertir nombre de nodo a coordenadas
        int xActual = grafo.obtenerCoordenadaX(nodoActual);
        int yActual = grafo.obtenerCoordenadaY(nodoActual);
        int xSiguiente = grafo.obtenerCoordenadaX(siguienteNodo);
        int ySiguiente = grafo.obtenerCoordenadaY(siguienteNodo);

        // Mover Pac-Man en el tablero
        tablero[xActual][yActual] = '-';
        tablero[xSiguiente][ySiguiente] = 'P';

        // Comprobar si Pac-Man encontró la cereza
        if (xSiguiente == cereza.getX() && ySiguiente == cereza.getY()) {
            cout << "Pac-Man comió la cereza!" << endl;

            // Colocar una nueva cereza en otra posición aleatoria
            cereza.colocarEnNuevaPosicion(filas, columnas);
            tablero[cereza.getX()][cereza.getY()] = 'C';

            // Añadir un nuevo fantasma en el tablero
            agregarFantasmaAleatorio(grafo, tablero, filas, columnas);
        }

        // Imprimir el tablero después de cada movimiento
        imprimirTablero(tablero);
        nodoActual = siguienteNodo;
    }

    cout << "Pac-Man alcanzó al fantasma!" << endl;

    return 0;
}
