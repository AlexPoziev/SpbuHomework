cmake_minimum_required(VERSION 3.23)
project(sortedList C)

set(CMAKE_C_STANDARD 99)

add_executable(sortedList main.c sortedList.c sortedList.h SortedListTest.c SortedListTest.h)
