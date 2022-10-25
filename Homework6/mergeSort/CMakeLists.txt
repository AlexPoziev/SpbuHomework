cmake_minimum_required(VERSION 3.23)
project(mergeSort C)

set(CMAKE_C_STANDARD 99)

add_executable(mergeSort main.c list.c list.h)
