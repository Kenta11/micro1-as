#!/usr/bin/env bash

# run `source ./script/systemtest.sh` on root directory

function test_micro1_as () {
    doller1_dirname=$(dirname $1)
    expected_dirname=$(dirname ${doller1_dirname})
    input_filename=$(basename $1)

    echo "====================================================================="
    echo "input: $1"
    echo "expected: ${expected_dirname}/expect/${input_filename%.asm}.b"
    echo "result: ${1%.asm}.b"

    ./bin/micro1-as $1
    if [ $? != 0 ]; then
        echo "Assembling failed"
        return 1
    fi

    diff ${expected_dirname}/expect/${input_filename%.asm}.b ${1%.asm}.b --ignore-space-change
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
