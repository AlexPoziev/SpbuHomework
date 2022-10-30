cmake_minimum_required(VERSION 3.23)
project(parsingTree C)

set(CMAKE_C_STANDARD 99)

add_executable(parsingTree main.c binaryTree.c binaryTree.h testBinaryTree.c testBinaryTree.h)
