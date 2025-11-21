#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>



class Jugador {
    public:
        std::string nombre;
        int puntaje;

        Jugador(std::string n = "");
    };




#endif //JUGADOR_H
