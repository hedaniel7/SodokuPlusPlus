cmake_minimum_required(VERSION 3.10)

project(
    SudokuPlusPlus
    VERSION 1.0.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(sudoku SHARED lib/sudoku.cpp lib/cell.cpp)

add_executable(tests lib/test.cpp)
target_link_libraries(tests PRIVATE sudoku)


#add_executable(sudoku_ui ui/main.cpp ui/terminal_ui.cpp)
#target_link_libraries(sudoku_ui PRIVATE sudoku)
#find_package(Curses REQUIRED)
#target_link_libraries(sudoku_ui PRIVATE ${CURSES_LIBRARIES})
#target_include_directories(sudoku_ui PRIVATE ${CURSES_INCLUDE_DIR})
