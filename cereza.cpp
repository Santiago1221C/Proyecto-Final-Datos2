#include "cereza.h"
#include <random>


Cereza::Cereza(int posX, int posY) { //constructor con parametros 
    x = posX; 
    y = posY;
}

Cereza::Cereza(){} //constructor vacio

//getters
int Cereza::getX() const { 
    return x;
}

int Cereza::getY() const {
    return y;
}

//metodo para colocar la cereza en una nueva posicion aleatoria
void Cereza::colocarEnNuevaPosicion(int maxFilas, int maxColumnas){
    x = rand()%maxFilas;
    y = rand()%maxColumnas;
}

//metodo para obtener el nodo de la cereza
string Cereza::obtenerNodoCereza() const {
    return "C" + to_string(x) + "_" + to_string(y); 
}