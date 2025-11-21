#include "Nodo.h"

Nodo::Nodo(int r, int c) {
    row = r;
    col = c;

    esParedExterior = false;
    esMuroInterior = false;
    estaPlayer = false;
    estaTesoro = false;
    tipoTesoro = "";

    arriba = abajo = izquierda = derecha = nullptr;
}
