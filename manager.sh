#!/bin/bash

CXX=g++
CXXFLAGS="-std=c++17 -Wall -Iinclude"

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
SOURCES=$(find $SRC_DIR -name '*.cpp')
OBJECTS=$(echo $SOURCES | sed "s|$SRC_DIR/|$OBJ_DIR/|g" | sed "s|.cpp|.o|g")

EXECUTABLE=$BIN_DIR/line_counter.exe

build() {
    echo "Building project..."

    mkdir -p $OBJ_DIR
    mkdir -p $BIN_DIR

    for src in $SOURCES; do
        obj=$(echo $src | sed "s|$SRC_DIR/|$OBJ_DIR/|g" | sed "s|.cpp|.o|g")
        echo "Compiling $src..."
        $CXX $CXXFLAGS -c -o $obj $src
    done

    echo "Linking executable..."
    $CXX $CXXFLAGS -o $EXECUTABLE $OBJECTS

    echo "Build completed."
}

run() {
    if [ -z "$1" ]; then
        echo "Error: No argument provided for running the program."
        echo "Usage: $0 <path_to_argument>"
        exit 1
    fi

    echo "Running $EXECUTABLE with argument: $1"
    $EXECUTABLE "$1"
}

clean() {
    echo "Cleaning up build artifacts..."
    rm -rf $OBJ_DIR
    rm -rf $BIN_DIR
    echo "Clean completed."
}

case "$1" in
    build)
        clean
        build
        ;;
    run)
        build
        shift
        run "$@"
        ;;
    clean)
        clean
        ;;
    *)
        echo "Usage: $0 {build|run <path_to_argument>|clean}"
        exit 1
        ;;
esac