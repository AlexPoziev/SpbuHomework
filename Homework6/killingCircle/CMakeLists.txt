cmake_minimum_required(VERSION 3.23)
project(killingCircle C)

set(CMAKE_C_STANDARD 99)

add_executable(killingCircle main.c list.c list.h testList.c testList.h)
