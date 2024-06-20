//
// Created by Angel Miranda on 19/06/24.
//

#ifndef PROYECTO_BOARD_H
#define PROYECTO_BOARD_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

class Board {
private:
    int n;
    int **boardArray;

    void initializeBoardArray();

public:
    explicit Board(int n);

    void fillRandom(int min, int max);

    void fillManually();

    void fillFromFile(const string& filename);

    void print();

    int get(int i, int j);

    void set(int i, int j, int value);

    [[nodiscard]] int getN() const;

    int **getBoard();

    ~Board();
};


#endif //PROYECTO_BOARD_H
