#pragma once
#include "../lib/sudoku.hpp"
#include <ncurses.h>

class TerminalUI {
    Sudoku& sudoku;
    void init_colors() const;
    void draw_board() const;

public:
    TerminalUI(Sudoku& sudoku);
    ~TerminalUI();
    void display(const Sudoku& sudoku) const;
    void run();
};