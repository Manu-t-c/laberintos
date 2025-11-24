#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include "Tablero.h"
#include "Jugador.h"
#include "PilaTesoros.h"

class Movimiento {
public:
    bool moverArriba(Tablero& tablero, Jugador& jugador, PilaTesoros& pila);
    bool moverAbajo(Tablero& tablero, Jugador& jugador, PilaTesoros& pila);
    bool moverIzquierda(Tablero& tablero, Jugador& jugador, PilaTesoros& pila);
    bool moverDerecha(Tablero& tablero, Jugador& jugador, PilaTesoros& pila);
};

#endif //MOVIMIENTO_H
