cmake_minimum_required(VERSION 3.23)
project(mergeSort C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_compile_options(-fsanitize=address -g)
add_link_options(-fsanitize=address -g)
add_executable(mergeSort main.c list.c list.h mergeSort.c mergeSort.h listTest.c listTest.h)

