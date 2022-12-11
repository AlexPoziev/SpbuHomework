cmake_minimum_required(VERSION 3.23)
project(RealNumber C)

set(CMAKE_C_STANDARD 99)

add_executable(RealNumber main.c lexer.c lexer.h)
