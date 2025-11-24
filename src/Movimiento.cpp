#include "Movimiento.h"
#include <iostream>

bool Movimiento::mover(Tablero &tablero, Jugador &jugador, Nodo* destino) {
    if (destino == nullptr) return false;

    // Si hay pared exterior → no se mueve
    if (destino->esParedExterior) {
        std::cout << "No puedes pasar: hay una pared exterior.\n";
        return false;
    }

    // Si hay muro interior → tampoco se mueve
    if (destino->esMuroInterior) {
        std::cout << "No puedes pasar: hay un muro interior.\n";
        return false;
    }

    // Mover jugador
    tablero.nodoJugador->estaJugador = false;
    destino->estaJugador = true;
    tablero.nodoJugador = destino;

    // Destapar casilla
    destino->estaDescubierto = true;

    // Si hay tesoro
    if (destino->estaTesoro) {
        jugador.agregarTesoro(destino->tipoTesoro);
        destino->estaTesoro = false;
        destino->tipoTesoro = "";
    }

    jugador.aumentarPuntaje();

    return true;
}

bool Movimiento::moverArriba(Tablero &tablero, Jugador &jugador) {
    return mover(tablero, jugador, tablero.nodoJugador->arriba);
}

bool Movimiento::moverAbajo(Tablero &tablero, Jugador &jugador) {
    return mover(tablero, jugador, tablero.nodoJugador->abajo);
}

bool Movimiento::moverIzquierda(Tablero &tablero, Jugador &jugador) {
    return mover(tablero, jugador, tablero.nodoJugador->izquierda);
}

bool Movimiento::moverDerecha(Tablero &tablero, Jugador &jugador) {
    return mover(tablero, jugador, tablero.nodoJugador->derecha);
}
