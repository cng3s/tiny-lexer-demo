cmake_minimum_required(VERSION 3.13)
project(hzcc)

set(CMAKE_CXX_STANDARD 14)

add_executable(hzcc main.cpp scanner.cpp scanner.hpp type.cpp type.hpp tok.cpp tok.hpp)