#include "cell.hpp"
#include "sudoku.hpp"
#include <cassert>

void test_cell(){
    Cell cell('0');
    assert(cell.is_empty());
    Cell cell1('1');
    assert(!cell1.is_empty());
    assert(cell1.value()==1);
}

void test_sudoku() {
    Sudoku sudoku({
        "123456789",
        "123456789",
        "123456789",
        "123456789",
        "123456789",
        "123456789",
        "123456789",
        "123456789",
        "123456789",
    });
    assert(!sudoku.is_valid());

    Sudoku grid1({
        "003020600",
        "900305001",
        "001806400",
        "008102900",
        "700000008",
        "006708200",
        "002609500",
        "800203009",
        "005010300",
    });
    assert(grid1.solve());
}

int main(){
    test_cell();
    test_sudoku();
}
