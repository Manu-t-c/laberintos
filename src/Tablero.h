#ifndef TABLERO_H
#define TABLERO_H

#include "Nodo.h"
#include <iostream>

class Tablero {
private:
    Nodo* head;

public:
    Nodo* playerNode;
    int tesorosRestantes;

    Tablero();
    void generarTablero();
    Nodo* getNodo(int row, int col);
    void lugarParedExterna();
    void lugarMuroInterno();
    void lugarTesoros();
    void lugarJugador();

    void mostrar(Nodo* nodo);
    void imprimirTablero();
};



#endif //TABLERO_H
