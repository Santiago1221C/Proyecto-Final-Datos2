#include <iostream>
#include <fstream>
#include <string>
#include "grafo.h"
#include "cereza.h"
#include "tablero.h"
using namespace std;

// mensajes de depuración
bool debugMode = false;

// Función para el menú principal
void mostrarMenu() {
    cout << "\n|||||||||| Menu Principal |||||||||||" << endl;
    cout << "1. Ingresar tamaño del tablero" << endl;
    cout << "2. Iniciar juego" << endl;
    cout << "3. Salir" << endl;
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

    ofstream archivo("output.txt");  // Abrir archivo 
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Ingrese el número de filas del tablero: ";
                cin >> filas;
                cout << "Ingrese el número de columnas del tablero: ";
                cin >> columnas;
                tablero = Tablero(filas, columnas);  // Cambiar el tamaño del tablero
                tableroIni = true;
                cout << "Tablero de " << filas << "x" << columnas << " ha sido creado en el archivo output.txt." << endl;
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

                // Crear y posicionar la cereza en el grafo y por ende en el tablero
                Cereza cereza(rand() % filas, rand() % columnas);
                string nodoCereza = cereza.obtenerNodoCereza();
                grafo.insertarVertice(nodoCereza, cereza.getX(), cereza.getY());
                tablero.actualizarPosicion(cereza.getX(), cereza.getY(), 'C');

                int i = 1;
                archivo << "\nTablero numero " << i++ << ":" << endl;    
                tablero.imprimirTablero(archivo);  // Imprimir tablero en el archivo

                string nodoActual = pacmanNodo;
                bool cerezaComida = false;

                while (nodoActual != fantasmaNodo) {
                    // Determinar el nodo destino según el estado
                    string nodoDestino = cerezaComida ? fantasmaNodo : nodoCereza;

                    // Obtener siguiente movimiento de Pac-Man
                    string siguienteNodo = grafo.obtenerSiguienteNodo(nodoActual, nodoDestino);

                    // Convertir nombre de nodo a coordenadas
                    int xActual = grafo.obtenerDireccionX(nodoActual);
                    int yActual = grafo.obtenerDireccionY(nodoActual);
                    int xSiguiente = grafo.obtenerDireccionX(siguienteNodo);
                    int ySiguiente = grafo.obtenerDireccionY(siguienteNodo);

                    // Mover Pac-Man en el tablero
                    tablero.actualizarPosicion(xActual, yActual, '-');
                    tablero.actualizarPosicion(xSiguiente, ySiguiente, 'P');
                    
                    // Imprimir el tablero después de cada movimiento
                    archivo << "\nTablero numero " << i++ << ":" << endl;
                    tablero.imprimirTablero(archivo);

                    // Mirar el Pac-man si se comio la cereza 
                    if (!cerezaComida && xSiguiente == cereza.getX() && ySiguiente == cereza.getY()) {
                        archivo << "Pac-Man comió la cereza! \nes momento de comerce al fantasma!\n" << endl;
                        cerezaComida = true;
                        grafo.agregarFantasmaAleatorio(grafo, tablero, filas, columnas, pacmanNodo, cereza.getX(), cereza.getY()); // Agregar fantasma al grafo
                    }
                    nodoActual = siguienteNodo;
                }
                archivo << "Pac-Man alcanzó el fantasma! \nFELICITACIONES!!!!! \n" << endl;
                break;
            }

            case 3: {
                cout << "Saliendo del programa." << endl;
                break;
            }

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 3);

    archivo.close();  // Cerrar archivo al salir
    return 0;
}
