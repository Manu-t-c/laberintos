#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <string>
#include <vector>
#include <list>
#include <utility>

class Puntaje {
private:
    static const int TAMANO = 100;
    std::vector<std::list<std::pair<std::string,int>>> tabla;

    int funcionHash(const std::string &clave) const;

public:
    Puntaje();

    void registrarPuntaje(const std::string &nombre, int puntaje);

    bool obtenerPuntaje(const std::string &nombre, int &puntaje) const;

    bool existeJugador(const std::string &nombre) const;

    void mostrarScoresOrdenados() const;
};

#endif
