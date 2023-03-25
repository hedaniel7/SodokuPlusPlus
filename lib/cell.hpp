#pragma once
#include <cstdint>

class Cell{
    uint8_t cell;
    public:
    bool is_empty();
    Cell(char c);
    uint8_t value();
    void set(uint8_t n);
};

