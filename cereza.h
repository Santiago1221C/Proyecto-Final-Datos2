#ifndef CEREZA_H
#define CEREZA_H
using namespace std;
#include <string>

class Cereza {
private:
    int x, y; // Coordenadas de la cereza

public:

    Cereza(int posX, int posY);// Constructor  con parametros
    Cereza(); // Constructor vacío

    // Getters 
    int getX() const;
    int getY() const;

    // Método para colocar la cereza en una nueva posición
    void colocarEnNuevaPosicion(int maxFilas, int maxColumnas);
    //Metodo para obtener el nodo de la cereza
    string obtenerNodoCereza() const;
};

#endif // CEREZA_H
