//
// Created by Angel Miranda on 19/06/24.
//

#include "SolutionCell.h"

SolutionCell::SolutionCell(int i, int j, int value, bool isPath) {
    this->i = i;
    this->j = j;
    this->value = value;
    this->isPath = isPath;
}

int SolutionCell::getI() const {
    return i;
}

int SolutionCell::getJ() const {
    return j;
}

int SolutionCell::getValue() const {
    return value;
}

bool SolutionCell::getIsPath() const {
    return isPath;
}

void SolutionCell::setIsPath(bool isPath) {
    this->isPath = isPath;
}

SolutionCell::~SolutionCell() = default;