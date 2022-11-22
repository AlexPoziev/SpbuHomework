cmake_minimum_required(VERSION 3.23)
project(states C)

set(CMAKE_C_STANDARD 99)

add_executable(states main.c states.c states.h list.c list.h)
