#include "terminal_ui.hpp"
#include "../lib/sudoku.hpp"
#include <vector>
#include <string>
#include <iostream>

int main() {
    std::vector<std::string> input = {
        "003020600",
        "900305001",
        "001806400",
        "008102900",
        "700000008",
        "006708200",
        "002609500",
        "800203009",
        "005010300",
    };

    try {
        Sudoku sudoku(input);
        TerminalUI ui(sudoku);
        ui.display(sudoku);
        ui.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}