cmake_minimum_required(VERSION 3.10)
project(tetris C)

set(CMAKE_C_STANDARD 99)
set(GCC_CURSES_FLAG "-lncurses")
add_definitions("-lncurses")
add_executable(tetris main.c screen.c)
