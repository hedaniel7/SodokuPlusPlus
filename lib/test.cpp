#include "cell.hpp"
#include <cassert>

void test_cell(){
    Cell cell('0');
    assert(cell.is_empty());
    Cell cell1('1');
    assert(!cell1.is_empty());
    assert(cell1.value()==1);
}



int main(){
    test_cell();
}