#!/bin/zsh

mkdir build
cd build
cmake ..
make

./GraphViz ../matrix.txt

if [[ $? -ne 0 ]]
then
    cd ..
    rm graph.dot
    rm -r build
else
    cd ..
    dot -Tpng graph.dot -o image.png
    open image.png
    rm graph.dot
    rm -r build
fi
