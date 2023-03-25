#pragma once
#include <cstdint>

class Cell {
    uint8_t cell;
public:
    Cell() : cell(0) {}
    bool is_empty() const;
    Cell(char c);
    uint8_t value() const;
    void set(uint8_t n);
};

