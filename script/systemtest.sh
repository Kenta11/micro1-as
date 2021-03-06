#!/usr/bin/env bash

# Copyright (c) 2020 Kenta Arai
# 
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.

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

# Set input files
if [ ! -d "build/test/systemtest/input/" ]; then
    mkdir -p build/test/systemtest/input/
fi
cp test/systemtest/input/* build/test/systemtest/input/
# Set expect files
if [ ! -d "build/test/systemtest/expect/" ]; then
    mkdir -p build/test/systemtest/expect/
fi
cp test/systemtest/expect/* build/test/systemtest/expect/

if [ ! -f "build/bin/micro1-as" ]; then
    echo "FATAL ERROR: micro1-as not found"
    return 1
fi

cd build/

return_count=0
for f in $(ls test/systemtest/input/*.asm); do
    test_micro1_as $f
    return_count=$(($return_count + $?))
done

cd ..
echo "Finished system tests"
return $return_count
