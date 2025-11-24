cmake_minimum_required(VERSION 3.3)
project(Laberintos)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(Laberintos
        main.cpp

        src/Juego.cpp
        src/Tablero.cpp
        src/Nodo.cpp
        src/Jugador.cpp
        src/Movimiento.cpp
        src/PilaTesoros.cpp
        src/Puntaje.cpp

)
