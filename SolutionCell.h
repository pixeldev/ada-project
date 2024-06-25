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
#ifndef PROYECTO_SOLUTIONCELL_H
#define PROYECTO_SOLUTIONCELL_H


class SolutionCell {
private:
    int i;
    int j;
    int value;
    bool isPath;

public:
    SolutionCell() : i(0), j(0), value(0), isPath(false) {}

    SolutionCell(int i, int j, int value, bool isPath);

    [[nodiscard]] int getI() const;

    [[nodiscard]] int getJ() const;

    [[nodiscard]] int getValue() const;

    [[nodiscard]] bool getIsPath() const;

    void setIsPath(bool isPath);

    ~SolutionCell();
};


#endif //PROYECTO_SOLUTIONCELL_H
