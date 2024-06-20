#include <iostream>

#include "Game.h"

using namespace std;

int main()  {
    int n;

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
            cout << "Introduce el tamaño del tablero.\n>> ";
            cin >> n;

            Game game(n);

            int min, max;
            cout << "Introduce el rango de los números aleatorios: (min max)\n>> ";
            cin >> min >> max;
            game.getBoard()->fillRandom(min, max);
            game.getBoard()->print();
            game.solve()->print();
            break;
        }
        case 2: {
            cout << "Introduce el tamaño del tablero.\n>> ";
            cin >> n;

            Game game(n);
            game.getBoard()->fillManually();
            game.getBoard()->print();
            game.solve()->print();
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

            ifstream file(filename);
            if (file.is_open()) {
                file >> n;
                Game game(n);
                game.getBoard()->fillFromFile(filename);
                game.getBoard()->print();
                game.solve()->print();
            } else {
                cout << "Error al abrir el archivo.\n";
            }
            break;
        }
        case 4: {
            cout << "Introduce el nombre del archivo: ";
            string filename;
            cin >> filename;

            ifstream file(filename);
            if (file.is_open()) {
                file >> n;
                Game game(n);
                game.getBoard()->fillFromFile(filename);
                game.getBoard()->print();
                game.solve()->print();
            } else {
                cout << "Error al abrir el archivo.\n";
            }
            break;
        }
        default:
            cout << "Opción inválida.\n";
            return 1;
    }

    return 0;
}