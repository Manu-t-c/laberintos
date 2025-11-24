#include "Juego.h"
#include "Tablero.h"
#include "PilaTesoros.h"
#include "Tesoro.h"

#include <iostream>
#include <cctype>

Juego::Juego(Tablero *t, PilaTesoros *p) {
    tablero = t;        // Los crea Persona 1 y 2 afuera
    pila = p;
    tesorosRecolectados = 0;
}

void Juego::iniciar() {

    std::cout << "Ingrese su nombre: ";
    std::string nombre;
    std::getline(std::cin, nombre);

    jugador = Jugador(nombre);
    jugador.puntaje = 0;
    tesorosRecolectados = 0;

    // --- Persona 1 ---
    // generar tablero completo
    tablero->generarTablero();
    tablero->lugarParedExterna();
    tablero->lugarMuroInterno();
    tablero->lugarTesoros();
    tablero->lugarJugador();

    // --- Persona 2 ---
    // limpiar pila
    pila->vaciar();

    loopPartida();

    // Guardar puntaje al final
    puntajes.registrarPuntaje(jugador.nombre, jugador.puntaje);

    std::cout << "\nPuntaje final: " << jugador.puntaje << "\n\n";

    std::cout << "=== RANKING ===\n";
    puntajes.mostrarScoresOrdenados();
}

void Juego::loopPartida() {

    while (tesorosRecolectados < 10) {

        tablero->imprimirTablero();   // Persona 1

        std::cout << "\nPuntaje: " << jugador.puntaje
                  << "\nTesoros: " << tesorosRecolectados << "/10\n";
        std::cout << "Movimiento (WASD) | T=ver tesoros | X=usar tesoro: ";

        char op;
        std::cin >> op;
        op = std::toupper(op);

        if (op == 'T') {
            pila->mostrar();       // Persona 2
        }
        else if (op == 'X') {
            usarTesoro();
        }
        else if (op=='W' || op=='A' || op=='S' || op=='D') {
            procesarMovimiento(op);
        }
        else {
            std::cout << "Comando invalido.\n";
        }
    }
}

void Juego::procesarMovimiento(char tecla) {
    bool encontroTesoro = false;
    Tesoro t;
    bool chocoMuro = false;

    // Persona 1 implementa moverJugador COMPLETO
    bool seMovio = tablero->moverJugador(tecla, encontroTesoro, t, chocoMuro);

    if (!seMovio) {
        if (chocoMuro)
            std::cout << "Hay un muro!\n";
        else
            std::cout << "Movimiento invalido.\n";
        return;
    }

    jugador.puntaje++;

    if (encontroTesoro) {
        pila->apilar(t);                   // Persona 2
        tesorosRecolectados++;
        std::cout << "Encontraste un tesoro!\n";
    }
}

void Juego::usarTesoro() {
    if (pila->estaVacia()) {
        std::cout << "No tienes tesoros.\n";
        return;
    }

    Tesoro t = pila->desapilar();   // Persona 2

    switch (t.getTipo()) {
        case Tesoro::RUBI:
            jugador.puntaje /= 2;
            std::cout << "Rubí: puntaje reducido.\n";
            break;

        case Tesoro::DIAMANTE:
            tablero->eliminarMurosAleatorios(2);   // Persona 1
            std::cout << "Diamante: se eliminaron 2 muros.\n";
            break;

        case Tesoro::PERLA:
            if (rand()%2 == 0) {
                jugador.puntaje = 0;
                std::cout << "Perla: puntaje a 0!\n";
            } else {
                jugador.puntaje *= 2;
                std::cout << "Perla: puntaje x2!\n";
            }
            break;

        case Tesoro::AMBAR:
            tablero->teletransportarJugador();     // Persona 1
            std::cout << "Ámbar: teletransportado.\n";
            break;
    }

    tablero->reubicarTesoro(t);   // Persona 1
    tablero->resetCasillas();     // Persona 1
}
