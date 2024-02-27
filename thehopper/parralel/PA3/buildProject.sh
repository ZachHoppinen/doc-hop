#!/bin/bash
if [ $(hostname) == 'r2-login' ]; then
    echo "Loading modules."
    module load cmake
    module load gcc
    module load openmpi/gcc/64/1.10.7
    export CXX=/cm/local/apps/gcc/9.2.0/bin/g++
fi

if [ ! -e "./slurms/logs" ]; then
    mkdir slurms/logs
fi

if [ -e "./build" ]; then
    RM_CMD="rm -rf ./build"
    $RM_CMD
fi

mkdir build

cd build

cmake ..

make
