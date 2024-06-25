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
#include "Board.h"

Board::Board(int n) {
    this->n = n;
    this->initializeBoardArray();
}

void Board::initializeBoardArray() {
    this->boardArray = new int *[this->n];
    for (int i = 0; i < this->n; i++) {
        this->boardArray[i] = new int[this->n];
    }
}

void Board::fillRandom(int min, int max) {
    srand(time(nullptr));
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            this->boardArray[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void Board::fillManually() {
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            cout << "Ingresa el valor para la posición [" << i << "][" << j << "]: ";
            cin >> this->boardArray[i][j];
        }
    }
}

void Board::fillFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        getline(file, line);

        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                if (!(file >> this->boardArray[i][j])) {
                    file.close();
                    return;
                }
            }
        }
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
    file.close();
}

void Board::print() {
    cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    cout << "Tablero:\n";
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            cout << "| " << setw(3) << this->boardArray[i][j] << " ";
        }
        cout << "|\n";
        for (int j = 0; j < this->n; ++j) {
            cout << "+-----";
        }
        cout << "+\n";
    }
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
}

int Board::get(int i, int j) {
    return this->boardArray[i][j];
}

void Board::set(int i, int j, int value) {
    this->boardArray[i][j] = value;
}

[[nodiscard]] int Board::getN() const {
    return this->n;
}

int **Board::getBoard() {
    return this->boardArray;
}

Board::~Board() {
    for (int i = 0; i < n; i++) {
        delete[] this->boardArray[i];
    }
    delete[] this->boardArray;
}
