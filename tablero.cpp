#include "tablero.h"
#include <iostream>
#include <vector>
extern bool debugMode;
using namespace std;
Tablero::Tablero() {} // Constructor vacío

Tablero::Tablero(int filas, int columnas) { // Constructor que recibe el tamaño del tablero
    this->filas = filas;
    this->columnas = columnas;
    tablero = vector<vector<char>>(filas, vector<char>(columnas,'-'));
}

// metodo para imprimir un tablero
void Tablero::imprimirTablero() const {
    for (const auto& fila : tablero) {
        for (char celda : fila) {
            cout << celda << ' ';
        }
        cout << endl;
    }
}

// Método para actualizar una posición en el tablero
void Tablero::actualizarPosicion(int x, int y, char simbolo) {
    if (x >= 0 && x < filas && y >= 0 && y < columnas) {
        tablero[x][y] = simbolo;
        if (debugMode) {
            cout << "Posición actualizada en (" << x << ", " << y << ") con símbolo '" << simbolo << "'" << endl;
        }
    } else if (debugMode) {
        cout << "Error: Intento de actualizar fuera de límites en (" << x << ", " << y << ")" << endl;
    }
}

//Método para obtener el símbolo de una posición en el tablero
char Tablero::obtenerPosicion(int x, int y) const { 
    if (x >= 0 && x < filas && y >= 0 && y < columnas) {
            return tablero[x][y];
        }
        return '\0'; // Devuelve un caracter nulo si la posición no está en el tablero
    }
