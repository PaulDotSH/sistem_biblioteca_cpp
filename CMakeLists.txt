cmake_minimum_required(VERSION 3.21)
project(sistem_biblioteca_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(sistem_biblioteca_cpp main.cpp biblioteca/carte.cpp biblioteca/carte.h biblioteca/biblioteca.cpp biblioteca/biblioteca.h menu.cpp menu.h)
