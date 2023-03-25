#include "terminal_ui.hpp"
#include <string>
#include <vector>

TerminalUI::TerminalUI(Sudoku& sudoku) : sudoku(sudoku) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_colors();
}

TerminalUI::~TerminalUI() {
    endwin();
}

void TerminalUI::display(const Sudoku& sudoku) const {
    // Display the Sudoku puzzle using the curses library
    erase();
    draw_board();

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            const Cell& cell = sudoku.get_cell(row, col);
            if (!cell.is_empty()) {
                mvaddch(row * 2 + 1, col * 4 + 2, cell.value() + '0');
            }
        }
    }

    refresh();
}

void TerminalUI::run() {
    // Implement the main loop for the terminal UI
    int ch;
    int current_row = 0, current_col = 0;

    while ((ch = getch()) != 'q' && ch != 'Q') {
        switch (ch) {
            case KEY_UP:
                if (current_row > 0) current_row--;
                break;
            case KEY_DOWN:
                if (current_row < 8) current_row++;
                break;
            case KEY_LEFT:
                if (current_col > 0) current_col--;
                break;
            case KEY_RIGHT:
                if (current_col < 8) current_col++;
                break;
            default:
                if (ch >= '1' && ch <= '9') {
                    Cell& cell = sudoku.get_cell(current_row, current_col);
                    if (cell.is_empty()) {
                        cell.set(ch - '0');
                        display(sudoku);
                    }
                }
                break;
        }

        move(current_row * 2 + 1, current_col * 4 + 2);
    }
}

void TerminalUI::init_colors() const {
    // Initialize color pairs
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
}

void TerminalUI::draw_board() const {
    // Draw the Sudoku board
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            attron(COLOR_PAIR(1));

            // Draw vertical lines
            if (col % 3 == 0) {
                mvaddch(row * 2 + 1, col * 4, ACS_VLINE);
            }

            // Draw horizontal lines
            if (row % 3 == 0) {
                mvaddch(row * 2, col * 4 + 2, ACS_HLINE);
            }

            // Draw the plus sign at the intersection
            if (row % 3 == 0 && col % 3 == 0) {
                mvaddch(row * 2, col * 4, ACS_PLUS);
            }

            // Draw the normal vertical and horizontal lines
            mvaddch(row * 2 + 1, col * 4 + 1, ACS_VLINE);
            mvaddch(row * 2, col * 4 + 2, ACS_HLINE);
            attroff(COLOR_PAIR(1));
        }
    }
}