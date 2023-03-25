#pragma once
#include "cell.hpp"
#include <array>
#include <string>
#include <vector>

class Sudoku {
public:
    Sudoku(const std::vector<std::string>& input);
    bool is_valid() const;
    bool solve();
    void print() const;
    const Cell& get_cell(int row, int col) const;
    Cell& get_cell(int row, int col);

private:
    std::array<std::array<Cell, 9>, 9> cells;
    bool solve(int row, int col);
    bool is_safe(int row, int col, uint8_t num) const;
};