cmake_minimum_required(VERSION 3.23)
project(postfixConverter C)

set(CMAKE_C_STANDARD 99)

add_executable(postfixConverter main.c postfixConverter.c postfixConverter.h
        ../stack/stack.h ../stack/stack.c ../stack/stackTest.c ../stack/stackTest.h)
