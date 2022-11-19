cmake_minimum_required(VERSION 3.23)
project(module C)

set(CMAKE_C_STANDARD 99)

add_executable(module modulesFiles.c sort.c sort.h)
