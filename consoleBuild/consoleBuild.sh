declare -a array
declare -i i=0
while read currentFolder
 do
    cd $currentFolder
    currentFolder="$(basename $PWD)"
    
    mkdir build
    cd build
    cmake ..
    make
    
    ./$currentFolder --test
    if [[ $? -eq 0 ]]
    then
        array[i]=0
    else
        array[i]=1
    fi
    
    cd ..
    rm -r build
    cd ../
    
    let ++i
done <directions.txt

echo "\nTests Results: "

cd ../consoleBuild
let i=0

while read currentFolder
do
    currentFolder="$(basename $currentFolder)"
    
    if [[ array[i] -eq 0 ]]
    then
        echo $currentFolder "Tests: Passed"
    else
        echo $currentFolder "Tests: Failed"
    fi
    
    let ++i
done <directions.txt
