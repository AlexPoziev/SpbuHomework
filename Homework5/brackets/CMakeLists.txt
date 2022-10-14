cmake_minimum_required(VERSION 3.23)
project(brackets C)

set(CMAKE_C_STANDARD 99)

add_executable(brackets main.c stack.c stack.h)
