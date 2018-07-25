cmake_minimum_required(VERSION 3.10)
project(tetris)

set(CMAKE_C_STANDARD 99)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})
include_directories(${PTHREAD_INCLUDE_DIR})
add_executable(tetris main.c screen.c game.c)
target_link_libraries(tetris ${CURSES_LIBRARIES} pthread)