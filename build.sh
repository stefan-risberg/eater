#!/bin/zsh

BUILD_DIR=build
NUM_BUILD_THREADS=9


function build_cppformat {
    echo "Building cppformat"
    cd lib

    if [[ ! (-a cppformat) ]]; then
        git submodule update --init
    fi

    cd cppformat

    if [[ ! (-a libformat.a) ]]; then
        echo "libformat.a does not exist."
        if [[ ! (-a CMakeLists.txt) ]]; then
            echo "need to fetch cppformat repo"
            cd ..
            git submodule update --init
            cd cppformat
        fi

        cmake .
        make -j $NUM_BUILD_THREADS
    fi

    cd ..
    cd ..
}

function build_lib {
    echo "Build libs"
    build_cppformat
}

function build_eater {
    if [[ ! (-a $BUILD_DIR) ]]; then
        echo $BUILD_DIR " does not exist, creating it."
        mkdir $BUILD_DIR
    fi

    cd $BUILD_DIR
    echo "Running cmake..."
    cmake ..
    echo "Running make..."
    make -j $NUM_BUILD_THREADS
}

function build {
    echo "Start build all"
    build_lib
    build_eater
}

function clean {
    echo "Cleaning all"
    if [[ -a bin ]]; then
        rm -r bin
    fi

    if [[ -a build ]]; then
        rm -r build
    fi
}

function run {
    cd bin
    ./eater
    cd ..
}

function usage {
    echo "Usage: ./build.sh <commands>"
    echo ""
    echo "Commands are stacked meaning that \"cbr\" will"
    echo "clean, build and run and \"rcb\" will run, clean and build"
    echo "b - build"
    echo "c - clean"
    echo "r - run"
}

if [[ $# != 1 ]]; then
    echo "Wrong argument count."
    usage
    exit 1
fi

first_arg=$1
for (( i = 1; i < $#first_arg+1; i++ )); do
    case $first_arg[$i] in
        (b) build
            ;;
        (c) clean
            ;;
        (r) run
            ;;
        (*) usage
            ;;
    esac
done
