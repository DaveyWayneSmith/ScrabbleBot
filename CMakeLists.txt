cmake_minimum_required(VERSION 3.5)
project(ScrabbleBot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp pile.cpp pile.h game.cpp game.h board.cpp board.h)
add_executable(ScrabbleBot ${SOURCE_FILES})