#include "tablero.h"
#include <iostream>
using namespace std;

Tablero::Tablero() {} // Constructor vacío

Tablero::Tablero(int filas, int columnas) { // Constructor que recibe el tamaño del tablero
    this->filas = filas;
    this->columnas = columnas;
    tablero = vector<vector<char>>(filas, vector<char>(columnas,'-'));
}

// metodo para imprimir un tablero
void Tablero::imprimirTablero(ofstream& archivo) const {

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }
    
     // Imprimir números de columna
    archivo << "  ";
    for (int j = 0; j < columnas; ++j) {
    }
    archivo << "\n";
    
    // Imprimir tablero con números de fila
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo << tablero[i][j] << " ";
        }
        archivo << "\n";
    }
    archivo << "\n";
}

//metodo para imprimir en consola 
void Tablero::imprimirConsola() const {
    // Imprimir números de columna
    cout << "  ";
    for (int j = 0; j < columnas; ++j) {
    }
    cout << "\n";
    
    // Imprimir tablero con números de fila
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << tablero[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


// Método para actualizar una posición en el tablero
void Tablero::actualizarPosicion(int x, int y, char simbolo) {
    if (posicionValida(x, y)) {
        tablero[x][y] = simbolo;
    }
}


//Método para obtener el símbolo de una posición en el tablero
char Tablero::obtenerPosicion(int x, int y) const { 
    if (posicionValida(x, y)) {
            return tablero[x][y];
        }
        return '\0'; // Devuelve un caracter nulo si la posición no está en el tablero
    }

//MEtodo para marcar temporalmente los nodos visitados 
void Tablero::marcarVisitado(int x, int y) {
    if (posicionValida(x, y) && tablero[x][y] == '-') {
        tablero[x][y] = '.';
    }
}

// Método para verificar si una posición es válida en el tablero
bool Tablero::posicionValida(int x, int y) const {
    return x >= 0 && x < filas && y >= 0 && y < columnas;
}

// Método para limpiar los '.' de los nodos visitados
void Tablero::limpiarVisitados() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (tablero[i][j] == '.') {
                tablero[i][j] = '-';
            }
        }
    }
}
