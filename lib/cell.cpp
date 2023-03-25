#include "cell.hpp"

bool Cell::is_empty(){
    return this->cell == 0;
}

Cell::Cell(char c){
    switch (c){
        case '0': 
        case '1': 
        case '2': 
        case '3': 
        case '4': 
        case '5': 
        case '6': 
        case '7': 
        case '8': 
        case '9': 
        this->cell = c - '0';
        break;
        default:
        throw "Illegal value"; 
    }
}

uint8_t Cell::value(){
    if(this->cell == 0){
        throw "Oops";
    }
    return this->cell;
}

void Cell::set(uint8_t n){
    if(n <= 9){
        this->cell = n;
    } else {
        throw "Illegal value";
    }
}