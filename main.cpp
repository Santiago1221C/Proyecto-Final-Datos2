#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "grafo.h"
#include "cereza.h"
#include "tablero.h"
using namespace std;

bool debugMode = false;

// Función para generar posiciones aleatorias válidas
pair<int, int> generarPosicionAleatoria(int filas, int columnas, const vector<pair<int, int>>& posicionesOcupadas) {
    pair<int, int> nuevaPos;
    bool posicionValida;
    
    do {
        posicionValida = true;
        nuevaPos = {rand() % filas, rand() % columnas};
        
        // Verificar que la posición no esté ocupada
        for (const auto& pos : posicionesOcupadas) {
            if (nuevaPos == pos) {
                posicionValida = false;
                break;
            }
        }
    } while (!posicionValida);
    
    return nuevaPos;
}

void mostrarMenu() {
    cout << "\n|||||||||| Menu Principal |||||||||||" << endl;
    cout << "1. Configurar tamaño del tablero" << endl;
    cout << "2. Iniciar juego" << endl;
    cout << "3. Salir" << endl;
    cout << "Seleccione una opción: ";
}

void configurarTablero(Tablero& tablero, int& filas, int& columnas, bool& tableroIni, ofstream& archivo) {
    cout << "Ingrese el número de filas del tablero: ";
    cin >> filas;
    cout << "Ingrese el número de columnas del tablero: ";
    cin >> columnas;

    if (filas <= 0 || columnas <= 0) {
        cout << "Error: Las dimensiones del tablero deben ser mayores a 0." << endl;
        return;
    }

    tablero = Tablero(filas, columnas);
    tableroIni = true;

    archivo << "\nTablero inicial:\n";
    tablero.imprimirTablero(archivo);
    cout << "Tablero creado: " << endl;
    tablero.imprimirConsola(); // Nuevo método para imprimir en consola
}

void iniciarJuego(Tablero& tablero, Grafo& grafo, int filas, int columnas, ofstream& archivo, bool tableroIni) {
    if (!tableroIni) {
        cout << "Primero debes configurar el tamaño del tablero." << endl;
        return;
    }

    // Vector para mantener registro de posiciones ocupadas
    vector<pair<int, int>> posicionesOcupadas;

    // Generar posición aleatoria para Pac-Man
    auto posPacman = generarPosicionAleatoria(filas, columnas, posicionesOcupadas);
    posicionesOcupadas.push_back(posPacman);

    // Generar posición aleatoria para la Cereza
    auto posCereza = generarPosicionAleatoria(filas, columnas, posicionesOcupadas);

    // Crear los nodos en el grafo
    string pacmanNodo = "P";
    string cerezaNodo = "C";

    // Insertar vértices en el grafo
    grafo.insertarVertice(pacmanNodo, posPacman.first, posPacman.second);
    grafo.insertarVertice(cerezaNodo, posCereza.first, posCereza.second);

    // Actualizar tablero
    tablero.actualizarPosicion(posPacman.first, posPacman.second, 'P');
    tablero.actualizarPosicion(posCereza.first, posCereza.second, 'C');

    // Generar cantidad de fantasmas según sqrt(filas x columnas)
    int cantidadFantasmas = static_cast<int>(sqrt(filas * columnas));

    // Generar posiciones aleatorias y añadir fantasmas al grafo y tablero
    for (int i = 1; i <= cantidadFantasmas; ++i) {
        auto posFantasma = generarPosicionAleatoria(filas, columnas, posicionesOcupadas);
        posicionesOcupadas.push_back(posFantasma);
        string fantasmaNodo = "F" + to_string(i);
        grafo.insertarVertice(fantasmaNodo, posFantasma.first, posFantasma.second);
        tablero.actualizarPosicion(posFantasma.first, posFantasma.second, 'F');
    }

    // Generar conexiones en el grafo
    grafo.generarAristasDirigidas();

    int turno = 1;
    string nodoActual = pacmanNodo;
    bool cerezaComida = false;
    vector<string> fantasmas;

    // Guardar los nombres de los fantasmas
    for (int i = 1; i <= cantidadFantasmas; ++i) {
        fantasmas.push_back("F" + to_string(i));
    }

    archivo << "\nEstado inicial del tablero:\n";
    tablero.imprimirTablero(archivo);
    cout << "\nEstado inicial del tablero:\n";
    tablero.imprimirConsola();

    // Bucle principal del juego
    while (!fantasmas.empty()) {
        // Si la cereza no ha sido comida, Pac-Man la busca primero
        string nodoDestino = cerezaComida ? fantasmas.back() : cerezaNodo;

        cout << "\nTurno " << turno++ << endl;
        cout << "Pac-Man está en (" << grafo.obtenerDireccionX(nodoActual)
            << "," << grafo.obtenerDireccionY(nodoActual) << ")" << endl;
        cout << "Objetivo: " << (cerezaComida ? nodoDestino : "Cereza") << endl;

        // Obtener el siguiente movimiento
        string siguienteNodo = grafo.obtenerSiguienteNodo(nodoActual, nodoDestino, tablero);

        if (siguienteNodo == nodoActual) {
            cout << "¡No hay camino posible! Fin del juego." << endl;
            break;
        }

        // Actualizar posiciones en el tablero
        int xActual = grafo.obtenerDireccionX(nodoActual);
        int yActual = grafo.obtenerDireccionY(nodoActual);
        int xSiguiente = grafo.obtenerDireccionX(siguienteNodo);
        int ySiguiente = grafo.obtenerDireccionY(siguienteNodo);

        tablero.actualizarPosicion(xActual, yActual, '-');
        tablero.actualizarPosicion(xSiguiente, ySiguiente, 'P');

        // Limpiar nodos visitados y mostrar tablero actualizado
        tablero.limpiarVisitados();
        archivo << "Estado del tablero después del turno " << turno - 1 << ":\n";
        tablero.imprimirTablero(archivo);
        cout << "\nTablero actual:\n";
        tablero.imprimirConsola();

        // Verificar si Pac-Man comió la cereza
        if (!cerezaComida && xSiguiente == posCereza.first && ySiguiente == posCereza.second) {
            cout << "¡Pac-Man comió la cereza! Ahora va por los fantasmas." << endl;
            archivo << "¡Pac-Man comió la cereza! Ahora va por los fantasmas.\n";
            cerezaComida = true;
        }

        // Verificar si Pac-Man comió un fantasma
        auto it = find(fantasmas.begin(), fantasmas.end(), siguienteNodo);
        if (it != fantasmas.end()) {
            cout << "¡Pac-Man comió un fantasma en (" << xSiguiente << ", " << ySiguiente << ")!" << endl;
            archivo << "¡Pac-Man comió un fantasma en (" << xSiguiente << ", " << ySiguiente << ")!\n";
            fantasmas.erase(it);
        }

        nodoActual = siguienteNodo;
    }

    if (fantasmas.empty()) {
        cout << "¡Juego terminado! Pac-Man se comió todos los fantasmas." << endl;
        archivo << "¡Juego terminado! Pac-Man se comió todos los fantasmas.\n";
    }
}
    
int main() {
    srand(time(0)); // Inicializar generador de números aleatorios
    
    int opcion;
    int filas = 0, columnas = 0;
    Tablero tablero;
    Grafo grafo;
    bool tableroIni = false;
    
    ofstream archivo("output.txt");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo output.txt para escritura." << endl;
        return 1;
    }

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                configurarTablero(tablero, filas, columnas, tableroIni, archivo);
                break;

            case 2:
                iniciarJuego(tablero, grafo, filas, columnas, archivo, tableroIni);
                break;

            case 3:
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción no válida. Por favor, intenta de nuevo." << endl;
                break;
        }
    } while (opcion != 3);

    archivo.close();
    return 0;
}