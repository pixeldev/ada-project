//
// Created by Angel Miranda on 19/06/24.
//

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
