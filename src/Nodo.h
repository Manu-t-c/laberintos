#ifndef NODO_H
#define NODO_H
#include <string>


class Nodo {
public:
    int row, col;
    bool esParedExterior;
    bool esMuroInterior;
    bool estaPlayer;
    bool estaTesoro;
    std::string tipoTesoro;

    Nodo* arriba;
    Nodo* abajo;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(int r = 0, int c = 0);
};



#endif //NODO_H
