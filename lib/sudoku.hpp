#pragma once
#include "cell.hpp"
#include <array>

class Sudoku{
    std::array<std::array<Cell, 9>, 9> cells;
};