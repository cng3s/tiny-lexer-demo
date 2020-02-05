cmake_minimum_required(VERSION 3.13)
project(tiny-lexer-demo)

set(CMAKE_CXX_STANDARD 14)

add_executable(lexer main.cpp scanner.cpp scanner.hpp tok.cpp tok.hpp)
