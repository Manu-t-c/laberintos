#include "PilaTesoros.h"

void PilaTesoros::push(const Tesoro& t) {
    pila.push(t);
}

Tesoro PilaTesoros::pop() {
    if (pila.empty()) {
        std::cout << "No hay tesoros para usar.\n";
        return Tesoro("");
    }

    Tesoro t = pila.top();
    pila.pop();
    return t;
}

bool PilaTesoros::estaVacia() const {
    return pila.empty();
}

void PilaTesoros::vaciar() {
    while (!pila.empty()) pila.pop();
}

void PilaTesoros::mostrar() const {
    if (pila.empty()) {
        std::cout << "No has recogido tesoros.\n";
        return;
    }

    std::stack<Tesoro> copia = pila;

    std::cout << "Tesoros recogidos (último primero):\n";
    while (!copia.empty()) {
        std::cout << " - " << copia.top().tipo << "\n";
        copia.pop();
    }
}


