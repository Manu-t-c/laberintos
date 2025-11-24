#include "src/Juego.h"
#include "src/Tablero.h"
#include "src/PilaTesoros.h"

int main() {

    Tablero tablero;
    PilaTesoros pila;

    Juego juego(&tablero, &pila);
    juego.iniciar();

    return 0;
}
