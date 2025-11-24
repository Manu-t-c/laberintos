#include "Juego.h"
#include "Tablero.h"
#include "PilaTesoros.h"

int main() {

    Tablero tablero;         // Persona 1 lo construyó
    PilaTesoros pila;        // Persona 2 lo construyó

    Juego juego(&tablero, &pila);
    juego.iniciar();

    return 0;
}
