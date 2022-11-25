cmake_minimum_required(VERSION 3.23)
project(bracketsBalance C)

set(CMAKE_C_STANDARD 99)

add_executable(bracketsBalance main.c bracketsBalance.c bracketsBalance.h ../stack/stackTest.h ../stack/stackTest.c
        ../stack/stack.c ../stack/stack.h)
