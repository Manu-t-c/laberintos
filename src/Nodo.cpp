#include "Nodo.h"


Nodo::Nodo(int r, int c) {
    row = r;
    col = c;

    esParedExterior = false;
    esMuroInterior = false;
    estaJugador = false;
    estaTesoro = false;
    estaDescubierto = false;
    tipoTesoro = "";

    arriba = abajo = izquierda = derecha = nullptr;
}
