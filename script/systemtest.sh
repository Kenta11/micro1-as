#!/usr/bin/env bash

# run `source ./script/systemtest.sh` on root directory

function test_micro1_as () {
    echo "====================================================================="
    echo "input: $1"
    echo "expected: $(dirname $(dirname $1))/expect/${$(basename $1)%.asm}.b"
    echo "result: ${1%.asm}.b"

    ./bin/micro1-as $1
    if [ $? != 0 ]; then
        echo "Assembling failed"
        return 1
    fi

    diff $(dirname $(dirname $1))/expect/${$(basename $1)%.asm}.b ${1%.asm}.b --ignore-space-change
    if [ $? != 0 ]; then
        echo "Test failed"
        return 1
    fi
    
    echo "Ok"
    return 0
}

echo "Starting system tests..."
cd build/

if [ ! -f "./bin/micro1-as" ]; then
    echo "FATAL ERROR: micro1-as not found"
    return 1
fi

for f in $(ls test/systemtest/input/*.asm); do
    test_micro1_as\
        $f
done

cd ..
echo "Finished system tests"
