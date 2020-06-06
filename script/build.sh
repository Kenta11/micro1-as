#!/usr/bin/env bash

rm -rf build; mkdir build
cd build

cmake ..
make -j`grep processor /proc/cpuinfo | wc -l`
