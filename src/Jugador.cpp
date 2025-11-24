#include "Jugador.h"
#include <iostream>

using namespace std;

Jugador::Jugador(string n) {
    nombre = n;
    puntaje = 0;
    pilaTesoros = new PilaTesoros();
}

void Jugador::aumentarPuntaje() {
    puntaje++;
}

void Jugador::agregarTesoro(string tipo) {
    pilaTesoros->push(tipo);

    cout << "\nHas recogido un tesoro! → " << tipo << endl;
}

void Jugador::mostrarTesoros() {
    if (pilaTesoros->estaVacia()) {
        cout << "Actualmente no tienes tesoros" << endl;
        return;
    }

    cout << "\nTesoros recogidos en total (del mas reciente al mas antiguo):\n";
    pilaTesoros->mostrar();
}