#include "Tablero.h"
#include <cstdlib>
#include <ctime>
using namespace std;

Tablero::Tablero() {
    head = nullptr;
    playerNode = nullptr;
    tesorosRestantes = 10;
}

void Tablero::generarTablero() {
    // Construcción 9x9 enlazada
}

Nodo* Tablero::getNodo(int r, int c) {
    // Retorna el nodo correspondiente
    return nullptr;
}

void Tablero::lugarParedExterna() {
    // Marcar bordes como #
}

void Tablero::lugarMuroInterno() {
    // Ubicar 16 muros internos |
}

void Tablero::lugarTesoros() {
    // Ubicar 10 tesoros aleatorios
}

void Tablero::lugarJugador() {
    // Ubicar jugador aleatorio
}

void Tablero::imprimirTablero() {
    // Imprimir casillas: o, P, |, #, etc
}
