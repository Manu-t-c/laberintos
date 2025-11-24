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
    Tablero *tablero;      // → Persona 1 lo crea y lo pasa a Juego
    PilaTesoros *pila;     // → Persona 2 lo crea y lo pasa a Juego
    Puntaje puntajes;      // → Tabla Hash que ya aprobamos

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

