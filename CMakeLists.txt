cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(tetris)

add_executable(main 
    src/main.cpp
    src/tetromino.cpp
    src/tetris.cpp
)