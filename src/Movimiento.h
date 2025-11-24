#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H


#include "Tablero.h"
#include "Jugador.h"
#include "PilaTesoros.h"

class Movimiento {
public:
    Movimiento() = default;

    bool moverArriba(Tablero &tablero, Jugador &jugador);
    bool moverAbajo(Tablero &tablero, Jugador &jugador);
    bool moverIzquierda(Tablero &tablero, Jugador &jugador);
    bool moverDerecha(Tablero &tablero, Jugador &jugador);

private:
    bool mover(Tablero &tablero, Jugador &jugador, Nodo* destino);
};


#endif //MOVIMIENTO_H
