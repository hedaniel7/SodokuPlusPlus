cmake_minimum_required(VERSION 3.10)

project(
    SodokuPlusPlus
    VERSION 1.0.0
    LANGUAGES CXX)

#target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

add_library(sudoku SHARED lib/sudoku.cpp lib/cell.cpp)

add_executable(tests lib/test.cpp)

target_link_libraries(tests PRIVATE sudoku)