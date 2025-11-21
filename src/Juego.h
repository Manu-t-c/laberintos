#ifndef JUEGO_H
#define JUEGO_H
#include "Tablero.h"
#include "Jugador.h"
#include "Movimiento.h"
#include "Puntaje.h"
#include "PilaTesoros.h"

class Juego {
private:
    Tablero tablero;
    Jugador jugador;
    PilaTesoros tesoros;
    Movimiento movimiento;
    Puntaje puntaje;

public:
    Juego();
    void iniciar();
    void jugar();
    void usarTesoro();
    void finalizar();

};



#endif //JUEGO_H
