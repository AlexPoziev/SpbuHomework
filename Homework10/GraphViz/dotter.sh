#!/bin/zsh

mkdir build
cd build
cmake ..
make

./GraphViz ../matrix.txt
cd ..

if [[ $? -ne 0 ]]
then
    rm graph.dot
    rm -r build
    exit 1
fi

dot -Tpng graph.dot -o image.png
open image.png
rm graph.dot
rm -r build
