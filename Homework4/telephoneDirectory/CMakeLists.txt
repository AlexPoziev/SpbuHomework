cmake_minimum_required(VERSION 3.23)
project(telephoneDirectory C)

set(CMAKE_C_STANDARD 99)

add_executable(telephoneDirectory directory.c phone.c phone.h)
