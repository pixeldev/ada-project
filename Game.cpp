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
#include "Game.h"

int Game::solve(int i, int j) {
    int **gameBoard = this->board->getBoard();
    int n = this->board->getN();
    if (i >= n || j >= n) return 0;
    if (this->dp[i][j] != -1) return this->dp[i][j];
    int down = solve(i + 1, j);
    int right = solve(i, j + 1);
    if (down > right) {
        this->path[i][j] = (i + 1 < n) ? make_pair(i + 1, j) : make_pair(-1, -1);
        return this->dp[i][j] = down + gameBoard[i][j];
    } else {
        this->path[i][j] = (j + 1 < n) ? make_pair(i, j + 1) : make_pair(-1, -1);
        return this->dp[i][j] = right + gameBoard[i][j];
    }
}

Game::Game(int n) {
    this->board = new class Board(n);
    this->dp = new int*[n];
    this->path = new pair<int, int>*[n];
    for (int i = 0; i < n; i++) {
        this->dp[i] = new int[n];
        this->path[i] = new pair<int, int>[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            this->dp[i][j] = -1;
        }
    }
}

Board *Game::getBoard() const {
    return this->board;
}

Solution *Game::solve() {
    int n = this->board->getN();
    int maxScore = -1, maxI = -1, maxJ = -1, score = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            score = this->solve(i, j);
            if (score > maxScore) {
                maxScore = score;
                maxI = i;
                maxJ = j;
            }
        }
    }

    auto *solutionPath = new Solution(this->board, maxScore);
    int i = maxI, j = maxJ;
    while (i != -1 && j != -1) {
        solutionPath->setPath(i, j);
        tie(i, j) = this->path[i][j];
    }

    return solutionPath;
}

Game::~Game() {
    for (int i = 0; i < this->board->getN(); i++) {
        delete[] this->dp[i];
        delete[] this->path[i];
    }
    delete[] this->dp;
    delete[] this->path;
    delete this->board;
}
