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

void TerminalUI::display(const Sudoku& sudoku, int current_row, int current_col) const {
    erase();
    draw_board();

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            const Cell& cell = sudoku.get_cell(row, col);
            if (!cell.is_empty()) {
                if (row == current_row && col == current_col) {
                    attron(COLOR_PAIR(2));
                }
                mvaddch(row * 2 + 1, col * 4 + 2, cell.value() + '0');
                if (row == current_row && col == current_col) {
                    attroff(COLOR_PAIR(2));
                }
            }
        }
    }

    refresh();
}

void TerminalUI::display_message(const std::string& message) const {
    mvprintw(0, 0, message.c_str());
    clrtoeol();
    refresh();
}

void TerminalUI::handle_input(const std::function<void(int)>& on_key_press) {
    int ch;
    while ((ch = getch()) != 'q' && ch != 'Q') {
        on_key_press(ch);
    }
}

void TerminalUI::run() {
    int current_row = 0, current_col = 0;
    display(sudoku, current_row, current_col);

    handle_input([&](int ch) {
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
            case 'c':
            case 'C':
                {
                    Cell& cell = sudoku.get_cell(current_row, current_col);
                    if (!cell.is_empty()) {
                        bool is_correct = check_cell(current_row, current_col);
                        display_message(is_correct ? "Correct!" : "Incorrect.");
                    }
                }
                break;
            default:
                if (ch >= '1' && ch <= '9') {
                    Cell& cell = sudoku.get_cell(current_row, current_col);
                    if (cell.is_empty()) {
                        cell.set(ch - '0');
                    }
                }
                break;
        }

        display(sudoku, current_row, current_col);
    });
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

bool TerminalUI::check_cell(int row, int col) const {
    int value = sudoku.get_cell(row, col).value();

    // Check row
    for (int c = 0; c < 9; ++c) {
        if (c != col && sudoku.get_cell(row, c).value() == value) {
            return false;
        }
    }

    // Check column
    for (int r = 0; r < 9; ++r) {
        if (r != row && sudoku.get_cell(r, col).value() == value) {
            return false;
        }
    }

    // Check box
    int box_start_row = row - (row % 3);
    int box_start_col = col - (col % 3);
    for (int r = box_start_row; r < box_start_row + 3; ++r) {
        for (int c = box_start_col; c < box_start_col + 3; ++c) {
            if ((r != row || c != col) && sudoku.get_cell(r, c).value() == value) {
                return false;
            }
        }
    }

    return true;
}