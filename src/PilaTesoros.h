#ifndef PILATESOROS_H
#define PILATESOROS_H

#include <stack>
#include <iostream>
#include "Tesoro.h"

class PilaTesoros {
private:
    std::stack<Tesoro> pila;

public:
    void push(const Tesoro& t);
    Tesoro pop();

    bool estaVacia() const;
    void vaciar();

    void mostrar() const;
};

#endif

