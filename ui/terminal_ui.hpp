#pragma once
#include "../lib/sudoku.hpp"
#include <ncurses.h>
#include <functional>

class TerminalUI {
    Sudoku& sudoku;
    void init_colors() const;
    void draw_board() const;
    void display(const Sudoku& sudoku, int current_row, int current_col) const;

public:
    TerminalUI(Sudoku& sudoku);
    ~TerminalUI();
    void display_message(const std::string& message) const;
    void handle_input(const std::function<void(int)>& on_key_press);
    void run();
    bool check_cell(int row, int col) const;
};

