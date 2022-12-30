cmake_minimum_required(VERSION 3.23)
project(KMP C)

set(CMAKE_C_STANDARD 99)

add_executable(KMP main.c substring.c substring.h substringTest.c substringTest.h)
