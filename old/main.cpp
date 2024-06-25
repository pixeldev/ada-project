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

using namespace std;

const int MAXN = 1000;
const char *RESET_COLOR = "\033[0m";
const char *GREEN_BACKGROUND = "\033[42m";

int dp[MAXN][MAXN];
pair<int, int> path[MAXN][MAXN];
int board[MAXN][MAXN];
int n;

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
    cout << "Ingrea el tamaño del tablero: \n>> ";
    cin >> n;

    int min, max;
    cout << "Ingresa el rango de valores aleatorios: \n>> ";
    cin >> min >> max;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = rand() % (max - min + 1) + min;
        }
    }

    cout << "Tablero:\n";
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

    memset(dp, -1, sizeof(dp));
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
    cout << "Máximo puntaje posible: " << max_score << "\nCamino: ";

    vector<vector<bool>> isPath(n, vector<bool>(n, false));
    int x = max_i, y = max_j;
    while (x != -1 && y != -1) {
        isPath[x][y] = true;
        tie(x, y) = path[x][y];
    }

    cout << "Tablero:\n";
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
    return 0;
}