cmake_minimum_required(VERSION 3.23)
project(calculator C)

set(CMAKE_C_STANDARD 99)

add_executable(calculator main.c stack.c stack.h)
