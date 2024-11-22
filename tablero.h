#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <fstream>
using namespace std;

class Tablero {
private:
    vector<vector<char>>tablero; // vector que representa el tablero 
    int filas, columnas; // Dimensiones del tablero

public:
    
    Tablero(int filas, int columnas);// Constructor que recibe el tamaño del tablero
    Tablero();//constructor vacio

    // Métodos
    void imprimirTablero(ofstream&  archivo ) const;
    void imprimirConsola() const;
    void actualizarPosicion(int x, int y , char simbolo);
    char obtenerPosicion(int x , int y )const;
    void marcarVisitado(int x, int y);
    bool posicionValida(int x, int y) const;
    void limpiarVisitados();
};

#endif //TABLERO_H
