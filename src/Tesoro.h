#ifndef TESORO_H
#define TESORO_H

#include <string>

struct Tesoro {
    std::string tipo;

    Tesoro(std::string t = "") : tipo(t) {}
};

#endif

