#!/bin/bash

if [ $(hostname) == 'r2-login' ]; then
    echo "Loading modules."
    module load cmake
    module load gcc
    export CXX=/cm/local/apps/gcc/9.2.0/bin/g++
fi

if [ -e "./build" ]; then
    RM_CMD="rm -rf ./build"
    $RM_CMD
fi

mkdir build

cd build

cmake ..

make
