#include <iostream>
#include <string>
#include "grafo.h"
#include "cereza.h"
#include "tablero.h"
using namespace std;

// Variable para activar o desactivar mensajes de depuración
bool debugMode = false;

//Funcion para el menu principal
void mostrarMenu() {
    cout << "\n|||||||||| Menu Principal |||||||||||" << endl;
    cout << "1. Ingresar tamaño del tablero" << endl;
    cout << "2. Iniciar juego" << endl;
    cout << "3. Mostrar estado del tablero" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main() {
    int opcion;
    int filas = 0, columnas = 0;
    Tablero tablero;
    Grafo grafo;
    bool tableroIni = false;
    string pacmanNodo = "P";
    string fantasmaNodo = "F1";

    do {
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
            case 1: {
                cout << "Ingrese el número de filas del tablero: ";
                cin >> filas;
                cout << "Ingrese el número de columnas del tablero: ";
                cin >> columnas;
                tablero = Tablero(filas, columnas);  // Crear o cambiar dimensiones del tablero
                tableroIni = true;
                cout << "Tablero de " << filas << "x" << columnas << " creado." << endl;
                tablero.imprimirTablero();
                break;
            }
            
            case 2: {
                if (!tableroIni) {
                    cout << "Primero debes ingresar el tamaño del tablero." << endl;
                    break;
                }
                
                // Posicionar Pac-Man en el grafo y tablero
                grafo.insertarVertice(pacmanNodo, 0, 0);
                tablero.actualizarPosicion(0, 0, 'P');

                // Posicionar el fantasma en el grafo y tablero
                grafo.insertarVertice(fantasmaNodo, filas - 1, columnas - 1);
                tablero.actualizarPosicion(filas - 1, columnas - 1, 'F');

                // Crear y posicionar la cereza en el grafo y tablero
                Cereza cereza(rand() % filas, rand() % columnas);
                string nodoCereza = cereza.obtenerNodoCereza();
                grafo.insertarVertice(nodoCereza, cereza.getX(), cereza.getY());
                tablero.actualizarPosicion(cereza.getX(), cereza.getY(), 'C');

                int i = 1;
                cout << "\nTablero numero " << i++ << ":" << endl;    
                tablero.imprimirTablero();

                // Simulación del movimiento de Pac-Man en dos etapas
                string nodoActual = pacmanNodo;
                bool cerezaComida = false;

                while (nodoActual != fantasmaNodo) {
                    // Determinar el nodo destino según el estado
                    string nodoDestino;
                    if (cerezaComida) {
                        nodoDestino = fantasmaNodo;
                    } else {
                        nodoDestino = nodoCereza;
                    }

                    // Obtener siguiente movimiento de Pac-Man
                    string siguienteNodo = grafo.obtenerSiguienteNodo(nodoActual, nodoDestino);

                    // Convertir nombre de nodo a coordenadas
                    int xActual = grafo.obtenerDireccionX(nodoActual);  // Obtener coordenada X del nodo actual
                    int yActual = grafo.obtenerDireccionY(nodoActual);  // Obtener coordenada Y del nodo actual
                    int xSiguiente = grafo.obtenerDireccionX(siguienteNodo);  // Obtener coordenada X del siguiente nodo
                    int ySiguiente = grafo.obtenerDireccionY(siguienteNodo);  // Obtener coordenada Y del siguiente nodo

                    // Mover Pac-Man en el tablero
                    tablero.actualizarPosicion(xActual, yActual, '-');  // CAmbiar simbolo de p  por -
                    tablero.actualizarPosicion(xSiguiente, ySiguiente, 'P');  // Nueva posición de p
                    
                    // Imprimir el tablero después de cada movimiento
                    cout << "\nTablero numero " << i++ << ":" << endl;
                    tablero.imprimirTablero();
                    // Comprobar si Pac-Man encontró la cereza
                    if (!cerezaComida && xSiguiente == cereza.getX() && ySiguiente == cereza.getY()) {
                        cout << "Pac-Man comió la cereza! \nes momento de comerce al fantasma!\n" << endl;
                        cerezaComida = true;
                        // nuevo fantasma en el tablero después de comer la cereza
                        grafo.agregarFantasmaAleatorio(grafo, tablero, filas, columnas, pacmanNodo, cereza.getX(), cereza.getY());
                    }
                    nodoActual = siguienteNodo;
                }
                cout << "Pac-Man alcanzó el fantasma! \nFELICITACIONES!!!!! \n" << endl;
                break;
            }

            case 3: {
                if (!tableroIni) {
                    cout << "Primero debes ingresar el tamaño del tablero." << endl;
                } else {
                    tablero.imprimirTablero();
                }
                break;
            }

            case 4: {
                cout << "Saliendo del programa." << endl;
                break;
            }

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
