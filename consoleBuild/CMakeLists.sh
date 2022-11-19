#!bin/zsh

current_folder="$(basename $PWD)"
touch CMakeLists.txt
echo 'cmake_minimum_required(VERSION 3.23)
project('$current_folder' C)
set(CMAKE_C_STANDARD 99)
add_executable('$current_folder $current_folder'.c)' > CMakeLists.txt

mkdir build
cd build
cmake ..
make
./$current_folder
cd ..
rm -r build
