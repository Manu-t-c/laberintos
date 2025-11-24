#include "Movimiento.h"

#include "Movimiento.h"
#include <iostream>

bool Movimiento::moverArriba(Tablero& tablero, Jugador& jugador, PilaTesoros& pila) {

    Nodo* actual = tablero.getJugadorPos();
    Nodo* destino = actual->arriba;

    // 1. Revisar si existe casilla arriba (por seguridad)
    if (destino == nullptr) {
        std::cout << "No puedes salir del tablero.\n";
        return false;
    }

    // 2. Revisar si es muro exterior
    if (destino->esParedExterior) {
        std::cout << "Hay una pared (#) arriba.\n";
        destino->visitado = true;
        return false;
    }

    // 3. Revisar si es muro interior
    if (destino->esMuroInterior) {
        std::cout << "Hay un muro (|) arriba.\n";
        destino->visitado = true;
        return false;
    }

    // 4. Movimiento válido — mover jugador
    actual->jugador = false;
    destino->jugador = true;
    tablero.setJugadorPos(destino);

    // 5. Sumar puntaje
    jugador.sumarPunto();   // este método debe existir en Jugador

    // 6. Si hay tesoro
    if (destino->tieneTesoro) {
        std::cout << "¡Encontraste un tesoro: "
                  << destino->tipoTesoro << "!\n";

        pila.push(Tesoro(destino->tipoTesoro));
        destino->tieneTesoro = false;
    }

    // 7. Destapar la casilla
    destino->visitado = true;

    return true;
}

bool Movimiento::moverAbajo(Tablero& tablero, Jugador& jugador, PilaTesoros& pila) {
    Nodo* actual = tablero.getJugadorPos();
    Nodo* destino = actual->abajo;

    if (destino == nullptr) return false;
    if (destino->esParedExterior) return false;
    if (destino->esMuroInterior) return false;

    actual->jugador = false;
    destino->jugador = true;
    tablero.setJugadorPos(destino);

    jugador.sumarPunto();

    if (destino->tieneTesoro) {
        pila.push(Tesoro(destino->tipoTesoro));
        destino->tieneTesoro = false;
    }

    destino->visitado = true;
    return true;
}


bool Movimiento::moverIzquierda(Tablero& tablero, Jugador& jugador, PilaTesoros& pila) {
    Nodo* actual = tablero.getJugadorPos();
    Nodo* destino = actual->izquierda;

    if (destino == nullptr) return false;
    if (destino->esParedExterior) return false;
    if (destino->esMuroInterior) return false;

    actual->jugador = false;
    destino->jugador = true;
    tablero.setJugadorPos(destino);

    jugador.sumarPunto();

    if (destino->tieneTesoro) {
        pila.push(Tesoro(destino->tipoTesoro));
        destino->tieneTesoro = false;
    }

    destino->visitado = true;
    return true;
}

bool Movimiento::moverDerecha(Tablero& tablero, Jugador& jugador, PilaTesoros& pila) {
    Nodo* actual = tablero.getJugadorPos();
    Nodo* destino = actual->derecha;

    if (destino == nullptr) return false;
    if (destino->esParedExterior) return false;
    if (destino->esMuroInterior) return false;

    actual->jugador = false;
    destino->jugador = true;
    tablero.setJugadorPos(destino);

    jugador.sumarPunto();

    if (destino->tieneTesoro) {
        pila.push(Tesoro(destino->tipoTesoro));
        destino->tieneTesoro = false;
    }

    destino->visitado = true;
    return true;
}
