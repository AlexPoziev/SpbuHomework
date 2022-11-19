
while read currentFolder
 do
    cd $currentFolder
    currentFolder="$(basename $PWD)"
    
    mkdir build
    cd build
    cmake ..
    make
    
    ./$currentFolder --test
    if [[ $? -eq 1 ]]
    then
        exit 1
    fi
    
    cd ..
    rm -r build
    cd ../
done <directions.txt
