#include "Puntaje.h"
#include <iostream>
#include <algorithm>

Puntaje::Puntaje() {
    tabla.resize(TAMANO);
}

int Puntaje::funcionHash(const std::string &clave) const {
    int suma = 0;
    for (char c : clave) {
        suma += int(c);
    }
    return suma % TAMANO;
}

void Puntaje::registrarPuntaje(const std::string &nombre, int puntaje) {
    int pos = funcionHash(nombre);

    for (auto &par : tabla[pos]) {
        if (par.first == nombre) {
            if (puntaje < par.second) {
                par.second = puntaje;
            }
            return;
        }
    }

    tabla[pos].push_back(std::make_pair(nombre, puntaje));
}

bool Puntaje::obtenerPuntaje(const std::string &nombre, int &puntaje) const {
    int pos = funcionHash(nombre);

    for (const auto &par : tabla[pos]) {
        if (par.first == nombre) {
            puntaje = par.second;
            return true;
        }
    }
    return false;
}

bool Puntaje::existeJugador(const std::string &nombre) const {
    int dummy;
    return obtenerPuntaje(nombre, dummy);
}

void Puntaje::mostrarScoresOrdenados() const {
    std::vector<std::pair<std::string, int>> todos;

    for (int i = 0; i < TAMANO; i++) {
        for (const auto &par : tabla[i]) {
            todos.push_back(par);
        }
    }

    if (todos.empty()) {
        std::cout << "Aun no hay jugadores registrados.\n";
        return;
    }

    std::sort(todos.begin(), todos.end(),
              [](auto &a, auto &b){ return a.second < b.second; });

    std::cout << "======= RANKING (MENOR PUNTAJE = MEJOR) =======\n";
    for (auto &p : todos) {
        std::cout << p.first << " -> " << p.second << " puntos\n";
    }
}
