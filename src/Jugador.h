#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include "PilaTesoros.h"

using namespace std;



class Jugador {
    public:
        std::string nombre;
        int puntaje;
        PilaTesoros* pilaTesoros;


        Jugador(std::string n = "");

        void aumentarPuntaje();
        void agregarTesoro(string tipo);
        void mostrarTesoros();
    };




#endif //JUGADOR_H
