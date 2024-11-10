#ifndef CEREZA_H
#define CEREZA_H

#include <string>

class Cereza {
private:
    int x, y; // Coordenadas de la cereza

public:
    // Constructor que recibe la posición inicial de la cereza
    Cereza(int posX, int posY);

    // Getters para la posición de la cereza
    int getX() const;
    int getY() const;

    // Método para colocar la cereza en una nueva posición
    void colocarEnNuevaPosicion(int maxFilas, int maxColumnas);
};

#endif // CEREZA_H
