cmake_minimum_required(VERSION 3.23)
project(Comments C)

set(CMAKE_C_STANDARD 99)

add_executable(Comments main.c comments.c comments.h commentsTest.c commentsTest.h)
