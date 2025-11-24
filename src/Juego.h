#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include "Jugador.h"
#include "Puntaje.h"

// Declaraciones mínimas para evitar dependencias circulares
class Tablero;
class PilaTesoros;
class Tesoro;

class Juego {
private:
    Jugador jugador;
    Tablero *tablero;
    PilaTesoros *pila;
    Puntaje puntajes;

    int tesorosRecolectados;

    void loopPartida();
    void procesarMovimiento(char tecla);
    void usarTesoro();

public:
    // El constructor SOLO recibe punteros de afuera.
    Juego(Tablero *t, PilaTesoros *p);

    // inicia todo el juego
    void iniciar();
};

#endif

