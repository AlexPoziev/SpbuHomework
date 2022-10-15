cmake_minimum_required(VERSION 3.23)
project(postfixCalculate C)

set(CMAKE_C_STANDARD 99)

add_executable(postfixCalculate main.c postfixCalculator.c postfixCalculator.h
        ../stack/stack.h ../stack/stack.c ../stack/stackTest.c ../stack/stackTest.h)
