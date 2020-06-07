#!/usr/bin/env bash

rm -rf build; mkdir build
cd build

cmake -DBUILD_UNIT_TESTS=ON ..
make -j`nproc`
ctest
