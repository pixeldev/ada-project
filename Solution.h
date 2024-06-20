//
// Created by Angel Miranda on 19/06/24.
//

#ifndef PROYECTO_SOLUTION_H
#define PROYECTO_SOLUTION_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "Board.h"
#include "SolutionCell.h"

inline const char *RESET_COLOR = "\033[0m";
inline const char *GREEN_BACKGROUND = "\033[42m";

using namespace std;

class Solution {
private:
    SolutionCell **solutionMatrix;
    int maxScore;
    int n;

public:
    explicit Solution(Board *board, int maxScore);

    void setPath(int i, int j);

    bool isPathAt(int i, int j);

    int getMaxScore();

    int getN();

    void print();

    ~Solution();
};


#endif //PROYECTO_SOLUTION_H
