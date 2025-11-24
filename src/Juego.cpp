#include "Juego.h"
#include "Tablero.h"
#include "PilaTesoros.h"
#include "Tesoro.h"

#include <iostream>
#include <cctype>
#include <conio.h>
#include <cstdlib>

Juego::Juego(Tablero *t, PilaTesoros *p) {
    tablero = t;
    pila = p;
    tesorosRecolectados = 0;
}

void Juego::iniciar() {

    std::cout << "Ingrese su nombre: ";
    std::string nombre;
    std::getline(std::cin, nombre);

    jugador = Jugador(nombre);
    jugador.puntaje = 0;
    tesorosRecolectados = 0;

    // generar tablero completo
    tablero->generarTablero();
    tablero->lugarParedExterna();
    tablero->lugarMuroInterno();
    tablero->lugarTesoros();
    tablero->lugarJugador();


    // limpiar pila
    pila->vaciar();

    loopPartida();

    // Guardar puntaje al final
    puntajes.registrarPuntaje(jugador.nombre, jugador.puntaje);

    std::cout << "\nPuntaje final: " << jugador.puntaje << "\n\n";

    std::cout << "=== RANKING ===\n";
    puntajes.mostrarScoresOrdenados();

    char opcion;
    std::cout << "¿Desea jugar otra partida? (S/N): ";
    std::cin >> opcion;

    // se estandariza la entrada para evitar errores
    opcion = toupper(opcion);
    std::cin.ignore();

    if (opcion == 'S') {
        iniciar(); // volver a comenzar
    }
}

void Juego::loopPartida() {

    while (tesorosRecolectados < 10) {

        tablero->imprimirTablero();

        std::cout << "\nPuntaje: " << jugador.puntaje
                  << "\nTesoros: " << tesorosRecolectados << "/10\n";
        std::cout << "Movimiento (WASD) | T=ver tesoros | X=usar tesoro: ";


        char op = _getch();
        op = toupper(op);


        if (op == 'T') {
            pila->mostrar();
        }
        else if (op == 'X') {
            usarTesoro();
        }
        else if (op=='W' || op=='A' || op=='S' || op=='D') {
            procesarMovimiento(op);
        }
        else {
            std::cout << "Comando invalido.\n";
        }
        std::cout << "\n";
    }

    std::cout << "\nPartida terminada!\n";

}

void Juego::procesarMovimiento(char tecla) {
    bool encontroTesoro = false;
    bool chocoMuro = false;

    int fila = tablero->nodoJugador->row;
    int col = tablero->nodoJugador->col;

    int nuevaFila = fila;
    int nuevaCol = col;

    switch (tecla) {
        case 'W': nuevaFila--; break;
        case 'S': nuevaFila++; break;
        case 'A': nuevaCol--; break;
        case 'D': nuevaCol++; break;
    }

    Nodo* nuevoNodo = tablero->obtenerNodo(nuevaFila, nuevaCol);

    // pared exterior
    if (!nuevoNodo || nuevoNodo->esParedExterior) {
        std::cout << "¡No puedes atravesar la pared exterior!\n";
        return;
    }

    if (nuevoNodo->esMuroInterior) {
        std::cout << "¡Te topaste con un muro!\n";
        nuevoNodo->estaDescubierto = true; // mostrar muro
        return;
    }

    // mover jugador
    tablero->nodoJugador->estaJugador = false;
    if (!nuevoNodo->estaTesoro) {
        nuevoNodo->estaDescubierto = true;
    }

    nuevoNodo->estaJugador = true;
    tablero->nodoJugador = nuevoNodo;

    jugador.puntaje++;

    // recoger tesoro si hay
    if (nuevoNodo->estaTesoro) {
        Tesoro t;
        t.tipo = nuevoNodo->tipoTesoro;
        pila->push(t);
        tesorosRecolectados++;
        nuevoNodo->estaTesoro = false;
        std::cout << "Encontraste un tesoro: " << t.tipo << "!\n";
    }
}

void Juego::usarTesoro() {
    if (pila->estaVacia()) {
        std::cout << "No tienes tesoros.\n";
        return;
    }

    Tesoro t = pila->pop(); // quita el tesoro de la pila
    // Disminuir el contador de tesoros recolectados
    tesorosRecolectados--;

    // resetear tablero: volver a tapar espacios internos
    tablero->resetearEspaciosInternos();

    // tesoros efectos
    if (t.tipo == "Rubi") {
        jugador.puntaje /= 2;
        std::cout << "Rubí: puntaje reducido.\n";
    }
    else if (t.tipo == "Diamante") {
        // eliminar 2 muros aleatorios
        int eliminados = 0;
        while (eliminados < 2) {
            int fila = rand() % 9; // ajustar al tamaño de tu tablero
            int col = rand() % 9;
            Nodo* n = tablero->obtenerNodo(fila, col);
            if (n && n->esMuroInterior) {
                n->esMuroInterior = false;
                n->estaDescubierto = true; // opcional para mostrar el camino
                eliminados++;
            }
        }
        std::cout << "Diamante: 2 muros eliminados.\n";
    }
    else if (t.tipo == "Perla") {
        if (rand() % 2 == 0) {
            jugador.puntaje = 0;
            std::cout << "Perla: puntaje a 0!\n";
        } else {
            jugador.puntaje *= 2;
            std::cout << "Perla: puntaje x2!\n";
        }
    }
    else if (t.tipo == "Ambar") {
        // teletransportar jugador a un nodo vacío aleatorio
        Nodo* nuevoNodo;
        do {
            int fila = rand() % 10; // ajustar según tamaño de tablero
            int col = rand() % 10;
            nuevoNodo = tablero->obtenerNodo(fila, col);
        } while (!nuevoNodo || nuevoNodo->estaJugador || nuevoNodo->esParedExterior || nuevoNodo->esMuroInterior);

        // mover jugador
        tablero->nodoJugador->estaJugador = false;
        nuevoNodo->estaJugador = true;
        tablero->nodoJugador = nuevoNodo;
        nuevoNodo->estaDescubierto = true;

        std::cout << "Ámbar: jugador teletransportado.\n";
    }

    // REUBICAR el tesoro usado en el tablero
    Nodo* nodoTesoro;
    do {
        int fila = rand() % 10; // ajustar según tu tamaño de tablero
        int col = rand() % 10;
        nodoTesoro = tablero->obtenerNodo(fila, col);
    } while (!nodoTesoro || nodoTesoro->estaJugador || nodoTesoro->esParedExterior || nodoTesoro->esMuroInterior);

    nodoTesoro->estaTesoro = true;
    nodoTesoro->tipoTesoro = t.tipo;
    nodoTesoro->estaDescubierto = false;
}

