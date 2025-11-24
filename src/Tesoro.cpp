#include "Tesoro.h"

Tesoro::Tesoro() : tipo("") {}

Tesoro::Tesoro(const std::string& tipo) : tipo(tipo) {}

std::string Tesoro::getTipo() const {
    return tipo;
}
