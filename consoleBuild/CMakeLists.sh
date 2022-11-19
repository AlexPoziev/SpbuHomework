#!bin/zsh

currentFolder="$(basename $PWD)"
touch CMakeLists.txt
echo 'cmake_minimum_required(VERSION 3.23)
project('$currentFolder' C)
set(CMAKE_C_STANDARD 99)
add_executable('$currentFolder $currentFolder'.c)' > CMakeLists.txt

mkdir build
cd build
cmake ..
make
./$currentFolder
cd ..
rm -r build
