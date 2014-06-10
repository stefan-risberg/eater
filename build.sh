#!/bin/zsh

BUILD_DIR=build
NUM_BUILD_THREADS=9

if [[ $# != 1 ]]; then
    echo "Wrong argument count."
    echo "Usage: TODO"
fi

if [[ ! (-a $BUILD_DIR) ]]; then
    echo $BUILD_DIR " does not exist, creating it."
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR
echo "Running cmake..."
cmake ..
echo "Running make..."
make -j $NUM_BUILD_THREADS
