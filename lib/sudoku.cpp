#include "sudoku.hpp"
#include <iostream>

Sudoku::Sudoku(const std::vector<std::string>& input) {
    if (input.size() != 9) {
        throw std::runtime_error("Invalid input size");
    }

    for (size_t row = 0; row < 9; ++row) {
        if (input[row].size() != 9) {
            throw std::runtime_error("Invalid row size");
        }

        for (size_t col = 0; col < 9; ++col) {
            cells[row][col] = Cell(input[row][col]);
        }
    }
}

bool Sudoku::is_valid() const {
    // Check rows, columns, and 3x3 boxes for duplicates
    for (int i = 0; i < 9; ++i) {
        std::array<bool, 9> row_seen = {false};
        std::array<bool, 9> col_seen = {false};
        std::array<bool, 9> box_seen = {false};

        for (int j = 0; j < 9; ++j) {
            // Check row
            if (!cells[i][j].is_empty()) {
                int value = cells[i][j].value() - 1;
                if (row_seen[value]) return false;
                row_seen[value] = true;
            }

            // Check column
            if (!cells[j][i].is_empty()) {
                int value = cells[j][i].value() - 1;
                if (col_seen[value]) return false;
                col_seen[value] = true;
            }

            // Check 3x3 box
            int box_row = (i / 3) * 3 + j / 3;
            int box_col = (i % 3) * 3 + j % 3;
            if (!cells[box_row][box_col].is_empty()) {
                int value = cells[box_row][box_col].value() - 1;
                if (box_seen[value]) return false;
                box_seen[value] = true;
            }
        }
    }
    return true;
}

bool Sudoku::solve() {
    return solve(0, 0);
}

// Implement recursive backtracking algorithm
bool Sudoku::solve(int row, int col) {
    // if we reached the end of the column, wrap around to new row.
    int new_row = (col == 8) ? row + 1 : row;
    // cycle through columns
    int new_col = (col + 1) % 9;

    // If the current cell is not empty, it does not make sense to solve.
    // it. In that case, we pick another cell that we can solve. We do
    // this by adding to the row and column index.
    if (!cells[row][col].is_empty()) {
        return solve(new_row, new_col);
    }

    // Current cell is empty, iterate through candidates and check if we
    // can pick one.
    for (uint8_t candidate = 1; candidate <= 9; ++candidate) {
        if (is_safe(row, col, candidate)) {
            cells[row][col].set(candidate);

            // Try solving next cell
            if (solve(new_row, new_col)) {
                return true;
            }

            cells[row][col].set(0);
        }
    }

    return false;
}

bool Sudoku::is_safe(int row, int col, uint8_t num) const {
    // Check if the number can be placed in the given position
    // Check if the number is not in the same row or column
    for (int i = 0; i < 9; ++i) {
        if ((cells[row][i].value() == num && i != col) ||
            (cells[i][col].value() == num && i != row)) {
            return false;
        }
    }

    // Check if the number is not in the same 3x3 box
    int box_start_row = row - row % 3;
    int box_start_col = col - col % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (cells[box_start_row + i][box_start_col + j].value() == num &&
                (box_start_row + i != row || box_start_col + j != col)) {
                return false;
            }
        }
    }

    return true;
}

void Sudoku::print() const {
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            if (cell.is_empty()) {
                std::cout << '.';
            } else {
                std::cout << static_cast<int>(cell.value());
            }
        }
        std::cout << '\n';
    }
}

const Cell& Sudoku::get_cell(int row, int col) const {
    return cells[row][col];
}

Cell& Sudoku::get_cell(int row, int col) {
    return cells[row][col];
}
