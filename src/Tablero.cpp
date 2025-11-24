#include "Tablero.h"
#include <cstdlib>
#include <ctime>

Tablero::Tablero() {
    head = nullptr;
    nodoJugador = nullptr;
    tesorosRestantes = 10;
}

void Tablero::generarTablero() {
    /* se usa la hora actual como semilla para garantizar siempre aleatoriedad */
    srand(time(nullptr));

    Nodo* filaArriba = nullptr;
    Nodo* filaAbajo = nullptr;
    Nodo* nodoActual = nullptr;
    Nodo* nodoAnterior = nullptr;

   /* se construye el tablero mediante dos ciclos anidados*/

   /* se construye las filas*/
   for (int f = 0; f < 9; f++) {
        nodoAnterior = nullptr;

        /* se construye las columnas */
        for (int c = 0; c < 9; c++) {
            nodoActual = new Nodo(f, c);

            /* si estamos en la posicion (0,0) pues estamos en la cabeza*/
            if (f == 0 && c == 0) {
                head = nodoActual;
            }

            /* eje X */
            if (nodoAnterior != nullptr) {
                nodoAnterior->derecha = nodoActual;
                nodoActual->izquierda = nodoAnterior;
            }

            /* eje Y */
            if (filaArriba != nullptr) {
                filaArriba->abajo = nodoActual;
                nodoActual->arriba = filaArriba;
                filaArriba = filaArriba->derecha;
            }

            nodoAnterior = nodoActual;
        }

        /* si es la primera fila, filaAbajo comienza en head*/
        if (filaAbajo == nullptr) {
            filaAbajo = head;

        /*si no lo es, seguir bajando*/
        } else {
            filaAbajo = filaAbajo->abajo;
        }

        /* filaArriba tiene que comenzar desde el inicio de la nueva fila*/
        filaArriba = filaAbajo;
    }
}

Nodo* Tablero::obtenerNodo(int fila, int columna) {
    Nodo* actual = head;

    /* bajar hasta la fila necesaria*/
    while (actual != nullptr && actual->row != fila) {
        actual = actual->abajo;
    }

    /* moverse hasta la columna necesaria (de izq a der)*/
    while (actual != nullptr && actual->col != columna) {
        actual = actual->derecha;
    }

    return actual;
}

void Tablero::lugarParedExterna() {
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            Nodo* nodo = obtenerNodo(f, c);

            /* si todos estos OR's se cumplen, estamos en un borde, ahi va una pared */
            if (f == 0 || f == 8 || c == 0 || c == 8) {
                nodo->esParedExterior = true;
                nodo->estaDescubierto = true;
            }
        }
    }
}

bool Tablero::posicionValidaTesoro(Nodo* nodo) {

    /* retorna un booleano segun el cumplimiento de condiciones del nodo en el parametro */
    return !nodo->esParedExterior &&
           !nodo->esMuroInterior &&
           !nodo->estaJugador &&
           !nodo->estaTesoro;
}

bool Tablero::posicionValidaJugador(Nodo* nodo) {

    /* retorna un booleano segun el cumplimiento de condiciones del nodo en el parametro */
    return !nodo->esParedExterior &&
           !nodo->esMuroInterior &&
           !nodo->estaTesoro;
}

void Tablero::lugarMuroInterno() {
    int colocados = 0;

    /* solo se colocan 16 muros internos */
    while (colocados < 16) {
        /* generamos dos numero aleatorio entre 1 y 7 (espacio libre en el tablero) */
        /* fila */
        int f = rand() % 7 + 1;
        /* columna */
        int c = rand() % 7 + 1;

        /* se llama el nodo en esa posicion (x, y) aleatoria */
        Nodo* nodo = obtenerNodo(f, c);

        /* se verifica que el nodo no guarde otro muro interior o un tesoro */
        if (!nodo->esMuroInterior && !nodo->estaTesoro) {
            nodo->esMuroInterior = true;
            colocados++;
        }
    }
}

void Tablero::lugarTesoros() {
    int colocados = 0;

    /* se crea un arreglo con los tipos de tesoros (OJO es válido porque no tiene nada que ver con jugabilidad) */
    std::string tipos[4] = {"Rubi", "Diamante", "Perla", "Ambar"};

    /* solo se colocan 10 tesoros */
    while (colocados < 10) {

        /* generamos dos numero aleatorio entre 1 y 7 (espacio libre en el tablero) */
        /* fila */
        int f = rand() % 7 + 1;

        /* columna */
        int c = rand() % 7 + 1;

        /* se obtiene el nodo de esa posicion aleatoria */
        Nodo* nodo = obtenerNodo(f, c);

        /* posicionar tesoro si es es valido */
        if (posicionValidaTesoro(nodo)) {
            nodo->estaTesoro = true;

            /* se decide aleatoriamente el tipo del tesoro */
            nodo->tipoTesoro = tipos[rand() % 4];
            colocados++;
        }
    }
}

void Tablero::lugarJugador() {

    /* se crea una flag para evitar el uso del 'break' en el ciclo while */
    bool i = true;
    while (i == true) {

        /* nuevamente se generan 2 numeros (fila y columna) aleatorios */
        int f = rand() % 7 + 1;
        int c = rand() % 7 + 1;

        /* de igual forma, se usan para obtener un nodo en una posicion aleatoria */
        Nodo* nodo = obtenerNodo(f, c);

        /* posicionar jugador si la posicion es valida */
        if (posicionValidaJugador(nodo)) {
            nodo->estaJugador = true;
            nodoJugador = nodo;
            i = false;
        }
    }
}

void Tablero::destaparCasilla(Nodo* nodo) {
    /* se cambia el atributo al nodo */
    nodo->estaDescubierto = true;
}

void Tablero::imprimirTablero() {

    /* se crea puntero auxiliar del nodo cabeza */
    Nodo* fila = head;

    /* se recorre */
    while (fila != nullptr) {
        Nodo* actual = fila;

        while (actual != nullptr) {

            /* coloca el icono corrrespondiente al jugador */
            if (actual->estaJugador) {
                std::cout << "P";
            }

            /* coloca el icono correspondiente a las paredes exteriores */
            else if (actual->esParedExterior) {
                std::cout << "#";
            }

            /* se verifica que el nodo actual este descubierto */
            else if (actual->estaDescubierto) {

                /* si lo esta y es un muro interior, colocar icono correspondiente*/
                if (actual->esMuroInterior){
                    std::cout << "|";

                /* si esta descubierto y no es pared interior puede ser nada o tesoro (no se muestran) */
                }else{
                    std::cout << " ";
                 }
            }

            /* si no esta descubierto se coloca icono correspondiente */
            else {
                std::cout << "o";
            }

            actual = actual->derecha;
        }

        std::cout << std::endl;
        fila = fila->abajo;
    }
}

void Tablero::resetearEspaciosInternos() {
    Nodo* fila = head;
    while (fila) {
        Nodo* actual = fila;
        while (actual) {
            if (!actual->esMuroInterior && !actual->esParedExterior && !actual->estaJugador)
                actual->estaDescubierto = false;
            actual = actual->derecha;
        }
        fila = fila->abajo;
    }
}
