#ifndef TABLERO_H
#define TABLERO_H

#include "Nodo.h"
#include <iostream>

class Tablero {
private:
    Nodo* head;

public:
    Nodo* nodoJugador;
    int tesorosRestantes;

    Tablero();

    void generarTablero();
    Nodo* obtenerNodo(int row, int col);

    void lugarParedExterna();
    void lugarMuroInterno();
    void lugarTesoros();
    void lugarJugador();

    void destaparCasilla(Nodo* nodo);
    void imprimirTablero();

    bool posicionValidaJugador(Nodo* nodo);
    bool posicionValidaTesoro(Nodo* nodo);
    void resetearEspaciosInternos();
};



#endif //TABLERO_H
