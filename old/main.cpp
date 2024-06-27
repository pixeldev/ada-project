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

/**
 * @brief Constantes para los códigos de color de la consola.
 *
 * RESET_COLOR es un código de escape ANSI que restablece el color de la consola al predeterminado.
 * GREEN_BACKGROUND es un código de escape ANSI que establece el color de fondo de la consola en verde.
 */
const char *RESET_COLOR = "\033[0m";
const char *GREEN_BACKGROUND = "\033[42m";

/**
 * @brief Matriz de tabulación para la programación dinámica.
 *
 * 'dp' es una matriz 2D de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero del juego.
 * Cada celda en 'dp' representa el resultado de un subproblema, que es la mayor suma de puntos que se puede obtener comenzando en la celda correspondiente en el tablero del juego.
 */
int **dp;

/**
 * @brief Matriz de camino para el algoritmo.
 *
 * 'path' es una matriz 2D de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero del juego.
 * Cada celda en 'path' contiene un par de enteros que representan las coordenadas (i, j) del siguiente paso en el camino óptimo.
 */
pair<int, int> **path;

/**
 * @brief Matriz del tablero del juego.
 *
 * 'board' es una matriz 2D de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero del juego.
 * Cada celda en 'board' contiene un número entero que representa el valor de la celda en el juego.
 */
int **board;

/**
 * @brief Tamaño del tablero del juego.
 *
 * 'n' es un entero que representa el tamaño del tablero del juego. El tablero es una matriz cuadrada de tamaño 'n' x 'n'.
 */
int n;

/**
 * @brief Coordenadas de la celda con el puntaje máximo.
 *
 * 'max_i' y 'max_j' son enteros que representan las coordenadas de la fila y la columna, respectivamente, de la celda con el puntaje máximo en el tablero del juego.
 */
int max_i, max_j;

/**
 * @brief Matriz de indicadores de camino óptimo.
 *
 * 'isPath' es una matriz 2D de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero del juego.
 * Cada celda en 'isPath' es un valor booleano que indica si la celda correspondiente en el tablero del juego es parte del camino óptimo.
 */
vector<vector<bool>> isPath;

/**
 * @brief Inicializa el tablero del juego a partir de un archivo.
 *
 * Esta función abre un archivo de texto que contiene la configuración del tablero del juego.
 * El archivo debe tener el siguiente formato:
 * - La primera línea debe contener un solo número entero 'n' que representa el tamaño del tablero (n x n).
 * - Las siguientes 'n' líneas deben contener 'n' números enteros cada una, representando los valores de las celdas del tablero.
 *
 * Ejemplo de archivo:
 * 3
 * 1 2 3
 * 4 5 6
 * 7 8 9
 *
 * En este ejemplo, se crea un tablero de 3x3 con los valores del 1 al 9.
 *
 * @param filename Una cadena que representa la ruta al archivo que contiene la configuración del tablero.
 */
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

/**
 * @brief Imprime la matriz de tabulación (dp).
 *
 * Esta función imprime la matriz de tabulación (dp) en la consola. La matriz de tabulación se utiliza en la programación dinámica
 * para almacenar los resultados de subproblemas, de modo que no necesitamos resolver el mismo subproblema varias veces.
 *
 * La matriz se imprime en un formato de cuadrícula para facilitar la visualización. Cada celda de la cuadrícula contiene el valor
 * de dp[i][j], que es el resultado del subproblema para la celda (i, j) en el tablero del juego.
 *
 * Esta función es útil para depurar y entender cómo se están resolviendo los subproblemas en la programación dinámica.
 */
void printDp() {
    cout << "DP:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "| " << setw(3) << dp[i][j] << " ";
        }
        cout << "|\n";
        for (int j = 0; j < n; ++j) {
            cout << "+-----";
        }
        cout << "+\n";
    }
}

/**
 * @brief Imprime el camino óptimo en la consola.
 *
 * Esta función imprime el camino óptimo que se ha calculado en la matriz 'path'.
 * La matriz 'path' almacena el siguiente paso óptimo para cada celda en el tablero del juego.
 * Cada celda en 'path' contiene un par de enteros que representan las coordenadas (i, j) del siguiente paso.
 *
 * El camino se imprime en un formato de cuadrícula para facilitar la visualización. Cada celda de la cuadrícula contiene el par de coordenadas del siguiente paso.
 *
 * Esta función es útil para depurar y entender cómo se está calculando el camino óptimo en el algoritmo.
 */
void printPath(){
    cout << "Path:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "(" << path[i][j].first << ", " << path[i][j].second << ") ";
        }
        cout << "\n";
    }
}

/**
 * @brief Resuelve el subproblema para la celda (i, j) en el tablero del juego.
 *
 * Esta función utiliza la técnica de programación dinámica para resolver el subproblema para la celda (i, j) en el tablero del juego.
 * El subproblema consiste en encontrar el camino con la mayor suma de puntos que comienza en la celda (i, j) y termina en alguna celda en la última fila o columna.
 *
 * La función primero verifica si la celda (i, j) está fuera del tablero. Si es así, devuelve 0 porque no hay puntos que se puedan obtener fuera del tablero.
 *
 * Luego, verifica si el resultado del subproblema para la celda (i, j) ya ha sido calculado y almacenado en la matriz de tabulación 'dp'. Si es así, devuelve el resultado almacenado.
 *
 * Si el resultado del subproblema aún no se ha calculado, la función calcula el resultado de los subproblemas para las celdas (i + 1, j) y (i, j + 1), que representan los movimientos hacia abajo y hacia la derecha, respectivamente.
 *
 * Luego, compara los resultados de los dos subproblemas y elige el mayor. El camino correspondiente al mayor resultado se almacena en la matriz 'path'.
 *
 * Finalmente, la función suma el valor de la celda (i, j) al mayor resultado de los subproblemas y almacena el resultado en 'dp[i][j]'. Este resultado representa la mayor suma de puntos que se puede obtener comenzando en la celda (i, j).
 *
 * @param i La coordenada de la fila de la celda.
 * @param j La coordenada de la columna de la celda.
 * @return La mayor suma de puntos que se puede obtener comenzando en la celda (i, j).
 */
int solve(int i, int j) {
    if (i >= n || j >= n) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int down = solve(i + 1, j);
    int right = solve(i, j + 1);
    cout << "-------- Calculando dp[" << i << "][" << j << "] --------\n";
    if (down > right) {
        path[i][j] = (i + 1 < n) ? make_pair(i + 1, j) : make_pair(-1, -1);
        int result = dp[i][j] = down + board[i][j];
        printDp();
        printPath();
        cout << "-------------------------------------\n";
        return result;
    } else {
        path[i][j] = (j + 1 < n) ? make_pair(i, j + 1) : make_pair(-1, -1);
        int result = dp[i][j] = right + board[i][j];
        printDp();
        printPath();
        cout << "-------------------------------------\n";
        return result;
    }
}

/**
 * @brief Inicializa la matriz de tabulación (dp).
 *
 * Esta función inicializa la matriz de tabulación 'dp' que se utiliza en la programación dinámica.
 * La matriz 'dp' es una matriz 2D de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero del juego.
 * Cada celda en 'dp' representa el resultado de un subproblema, que es la mayor suma de puntos que se puede obtener comenzando en la celda correspondiente en el tablero del juego.
 *
 * La función inicializa todas las celdas en 'dp' a -1, lo que indica que el resultado del subproblema correspondiente aún no se ha calculado.
 * Esta inicialización es necesaria antes de comenzar a resolver los subproblemas en la programación dinámica.
 */
void initializeDp() {
    dp = new int *[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int[n];
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
}

/**
 * @brief Inicializa la matriz de camino (path).
 *
 * Esta función inicializa la matriz 'path' que se utiliza para almacenar el camino óptimo en el tablero del juego.
 * La matriz 'path' es una matriz 2D de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero del juego.
 * Cada celda en 'path' contiene un par de enteros que representan las coordenadas (i, j) del siguiente paso en el camino óptimo.
 *
 * La función inicializa todas las celdas en 'path' a un par de enteros vacío, lo que indica que el siguiente paso en el camino óptimo aún no se ha calculado.
 * Esta inicialización es necesaria antes de comenzar a calcular el camino óptimo en el algoritmo.
 */
void initializePath() {
    path = new pair<int, int> *[n];
    for (int i = 0; i < n; i++) {
        path[i] = new pair<int, int>[n];
    }
}

/**
 * @brief Imprime el tablero del juego en la consola.
 *
 * Esta función imprime el tablero del juego en la consola en un formato de cuadrícula para facilitar la visualización.
 * Cada celda de la cuadrícula contiene el valor de la celda correspondiente en el tablero del juego.
 *
 * El tablero del juego es una matriz 2D 'board' de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero.
 * Cada celda en 'board' contiene un número entero que representa el valor de la celda en el juego.
 *
 * Esta función es útil para visualizar el estado actual del tablero del juego durante la ejecución del programa.
 */
void printBoard() {
    cout << "-------------------------------------\n" << "Tablero:\n";
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
}

/**
 * @brief Calcula el máximo puntaje posible en el tablero del juego.
 *
 * Esta función recorre todas las celdas del tablero del juego y calcula el puntaje máximo que se puede obtener comenzando en cada celda.
 * Para cada celda, se llama a la función 'solve' que utiliza la técnica de programación dinámica para calcular el puntaje máximo.
 *
 * Si el puntaje calculado para una celda es mayor que el puntaje máximo actual, se actualiza el puntaje máximo y se almacenan las coordenadas de la celda.
 * Las coordenadas de la celda con el puntaje máximo se almacenan en las variables globales 'max_i' y 'max_j'.
 *
 * Al final de la función, se imprime el puntaje máximo en la consola.
 *
 * Esta función es útil para encontrar el camino con el puntaje máximo en el tablero del juego.
 */
void maxScore() {
    int max_score = -1, score = 0;
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
    cout << "-------------------------------------\n" << "Máximo puntaje posible: " << max_score << "\n\nCamino: \n";
}

/**
 * @brief Construye el camino óptimo en el tablero del juego.
 *
 * Esta función construye el camino óptimo en el tablero del juego utilizando la matriz 'path' y la matriz 'isPath'.
 * La matriz 'path' contiene el siguiente paso óptimo para cada celda en el tablero del juego.
 * La matriz 'isPath' es una matriz 2D de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero del juego. Cada celda en 'isPath' indica si la celda correspondiente en el tablero del juego es parte del camino óptimo.
 *
 * La función inicializa todas las celdas en 'isPath' a 'false', lo que indica que ninguna celda es parte del camino óptimo.
 *
 * Luego, la función comienza en la celda con el puntaje máximo (max_i, max_j) y sigue el camino óptimo almacenado en 'path', marcando cada celda en el camino como 'true' en 'isPath'.
 *
 * El camino óptimo se sigue hasta que se alcanza una celda con coordenadas (-1, -1), que indica el final del camino.
 *
 * Esta función es útil para marcar el camino óptimo en el tablero del juego, que luego se puede utilizar para visualizar el camino.
 */
void makePath() {
    isPath = vector<vector<bool>>(n, vector<bool>(n, false));
    int x = max_i, y = max_j;
    while (x != -1 && y != -1) {
        isPath[x][y] = true;
        tie(x, y) = path[x][y];
    }
}

/**
 * @brief Imprime el tablero del juego con el camino óptimo resaltado.
 *
 * Esta función imprime el tablero del juego en la consola en un formato de cuadrícula para facilitar la visualización.
 * Cada celda de la cuadrícula contiene el valor de la celda correspondiente en el tablero del juego.
 * Las celdas que forman parte del camino óptimo se resaltan con un color de fondo verde.
 *
 * El tablero del juego es una matriz 2D 'board' de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero.
 * Cada celda en 'board' contiene un número entero que representa el valor de la celda en el juego.
 *
 * La matriz 'isPath' es una matriz 2D de tamaño 'n' x 'n', donde 'n' es el tamaño del tablero del juego.
 * Cada celda en 'isPath' indica si la celda correspondiente en el tablero del juego es parte del camino óptimo.
 *
 * Esta función es útil para visualizar el camino óptimo en el tablero del juego después de que se ha calculado.
 */
void printBoardPath() {
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

    printBoard();
    initializeDp();
    initializePath();
    maxScore();
    makePath();
    printBoardPath();

    cout << "-------------------------------------\n";
    return 0;
}