//
// Created by Angel Miranda on 19/06/24.
//

#include "Solution.h"

Solution::Solution(Board *board, int maxScore) {
    this->n = board->getN();
    this->maxScore = maxScore;
    auto **boardMatrix = board->getBoard();
    this->solutionMatrix = new SolutionCell *[this->n];
    for (int i = 0; i < this->n; i++) {
        this->solutionMatrix[i] = new SolutionCell[this->n];
        for (int j = 0; j < this->n; j++) {
            this->solutionMatrix[i][j] = SolutionCell(i, j, boardMatrix[i][j], false);
        }
    }
}

void Solution::setPath(int i, int j) {
    this->solutionMatrix[i][j].setIsPath(true);
}

bool Solution::isPathAt(int i, int j) {
    return this->solutionMatrix[i][j].getIsPath();
}

void Solution::print() {
    cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    cout << "El puntaje máximo que se puede alcanzar es: " << this->maxScore << "\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    cout << "Tablero con la solución:\n";
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            auto cell = this->solutionMatrix[i][j];
            if (cell.getIsPath()) {
                cout << "| " << GREEN_BACKGROUND << setw(3) << cell.getValue() << RESET_COLOR << " ";
            } else {
                cout << "| " << setw(3) << cell.getValue() << " ";
            }
        }
        cout << "|\n";
        for (int j = 0; j < this->n; ++j) {
            cout << "+-----";
        }
        cout << "+\n";
    }
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
}

int Solution::getMaxScore() {
    return this->maxScore;
}

int Solution::getN() {
    return this->n;
}

Solution::~Solution() {
    for (int i = 0; i < this->n; i++) {
        delete[] this->solutionMatrix[i];
    }
    delete[] this->solutionMatrix;
}