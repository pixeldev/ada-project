/**
 * Proyecto: Juego con el mejor puntaje.
 * Materia: Análisis y Diseño de Algoritmos.
 * Semestre: 2024-2.
 * Integrantes:
 * - Luna González Gabriel Alexis
 * - Mazariegos Aguilar Julio Darikson
 * - Miranda San Martín Ángel
 * Equipo: C
 */
#ifndef PROYECTO_GAME_H
#define PROYECTO_GAME_H

#include "Board.h"
#include "Solution.h"

class Game {
private:
    int **dp;
    Board *board;
    pair<int, int> **path;

    int solve(int i, int j);

public:
    explicit Game(int n);

    [[nodiscard]] Board *getBoard() const;

    Solution *solve();

    ~Game();
};


#endif //PROYECTO_GAME_H
