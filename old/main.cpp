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
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

const char *RESET_COLOR = "\033[0m";
const char *GREEN_BACKGROUND = "\033[42m";

int **dp;
pair<int, int> **path;
int **board;
int n;

void initializeFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> n;
        board = new int *[n];
        for (int i = 0; i < n; i++) {
            board[i] = new int[n];
            for (int j = 0; j < n; j++) {
                file >> board[i][j];
            }
        }
    } else {
        cout << "No se pudo abrir el archivo.\n";
    }
}

int solve(int i, int j) {
    if (i >= n || j >= n) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int down = solve(i + 1, j);
    int right = solve(i, j + 1);
    if (down > right) {
        path[i][j] = (i + 1 < n) ? make_pair(i + 1, j) : make_pair(-1, -1);
        return dp[i][j] = down + board[i][j];
    } else {
        path[i][j] = (j + 1 < n) ? make_pair(i, j + 1) : make_pair(-1, -1);
        return dp[i][j] = right + board[i][j];
    }
}

int main() {
    srand(time(0));

    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
    cout << "Bienvenido al problema del juego con el mejor puntaje.\n";
    cout << "El objetivo de este juego es encontrar el camino con la mayor suma de puntos.\n";
    cout << "Cada celda del tablero tiene un valor aleatorio entre un rango dado.\n";
    cout << "Se puede mover hacia abajo o hacia la derecha.\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";


    cout << "¿Cómo quieres llenar el tablero?\n";
    cout << "1. Llenar con números aleatorios.\n";
    cout << "2. Llenar manualmente.\n";
    cout << "3. Usar valores de prueba.\n";
    cout << "4. Obtener datos desde un archivo.\n>> ";

    int option;
    cin >> option;

    switch (option) {
        case 1: {
            cout << "Ingrea el tamaño del tablero: \n>> ";
            cin >> n;

            int min, max;
            cout << "Ingresa el rango de valores aleatorios: \n>> ";
            cin >> min >> max;

            board = new int *[n];
            for (int i = 0; i < n; i++) {
                board[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    board[i][j] = rand() % (max - min + 1) + min;
                }
            }
            break;
        }
        case 2: {
            cout << "Ingrea el tamaño del tablero: \n>> ";
            cin >> n;

            board = new int *[n];
            for (int i = 0; i < n; i++) {
                board[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    cout << "Ingresa el valor de la celda [" << i << "][" << j << "]: \n>> ";
                    cin >> board[i][j];
                }
            }
            break;
        }
        case 3: {
            cout << "¿Qué caso de prueba quieres utilizar?.\n";
            cout << "1. Caso de prueba #1.\n";
            cout << "2. Caso de prueba #2.\n";
            cout << "3. Caso de prueba #3.\n>> ";
            int test;
            cin >> test;
            string filename;
            switch (test) {
                case 1:
                    filename = "cases/primer-caso.txt";
                    break;
                case 2:
                    filename = "cases/segundo-caso.txt";
                    break;
                case 3:
                    filename = "cases/tercer-caso.txt";
                    break;
                default:
                    cout << "Opción inválida.\n";
                    return 1;
            }
            initializeFromFile(filename);
            break;
        }
        case 4: {
            string filename;
            cout << "Ingresa el nombre del archivo: \n>> ";
            cin >> filename;
            initializeFromFile(filename);
            break;
        }
        default:
            cout << "Opción inválida.\n";
            return 1;
    }

    dp = new int *[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int[n];
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    path = new pair<int, int> *[n];
    for (int i = 0; i < n; i++) {
        path[i] = new pair<int, int>[n];
    }

    cout << "------------------------------------\n" << "Tablero:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "| " << setw(3) << board[i][j] << " ";
        }
        cout << "|\n";
        for (int j = 0; j < n; ++j) {
            cout << "+-----";
        }
        cout << "+\n";
    }

    int max_score = -1, max_i = -1, max_j = -1, score = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            score = solve(i, j);
            if (score > max_score) {
                max_score = score;
                max_i = i;
                max_j = j;
            }
        }
    }
    cout << "------------------------------------\n" << "Máximo puntaje posible: " << max_score << "\n\nCamino: \n";

    vector<vector<bool>> isPath(n, vector<bool>(n, false));
    int x = max_i, y = max_j;
    while (x != -1 && y != -1) {
        isPath[x][y] = true;
        tie(x, y) = path[x][y];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (isPath[i][j]) {
                cout << "| " << GREEN_BACKGROUND << setw(3) << board[i][j] << RESET_COLOR << " ";
            } else {
                cout << "| " << setw(3) << board[i][j] << " ";
            }
        }
        cout << "|\n";
        for (int j = 0; j < n; ++j) {
            cout << "+-----";
        }
        cout << "+\n";
    }

    cout << "------------------------------------\n";
    return 0;
}