#!/bin/bash

# My compiler flags
CXX=g++
CXXFLAGS="-std=c++17 -Wall -Iinclude"

# My directories for said source, object and bin files
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

# Find all .cpp source files in the source directory
SOURCES=$(find $SRC_DIR -name '*.cpp')
# Convert list of source files to their respective object file paths
OBJECTS=$(echo $SOURCES | sed "s|$SRC_DIR/|$OBJ_DIR/|g" | sed "s|.cpp|.o|g")

# Path for final executable
EXECUTABLE=$BIN_DIR/line_counter.exe

# Function to build line_counter project
build() {
    echo "Building project..."

    # Create directories for object files and binary if they don't exist
    mkdir -p $OBJ_DIR
    mkdir -p $BIN_DIR

    # Compile source files into an object files
    for src in $SOURCES; do
        obj=$(echo $src | sed "s|$SRC_DIR/|$OBJ_DIR/|g" | sed "s|.cpp|.o|g")
        echo "Compiling $src..."
        $CXX $CXXFLAGS -c -o $obj $src
    done

    # Link all object files into final executable
    echo "Linking executable..."
    $CXX $CXXFLAGS -o $EXECUTABLE $OBJECTS

    # I like putting this to make sure my terminal is not hanged
    echo "Build completed."
}

# Function to run executable with a provided path argument
run() {
    # Check if argument is provided; if not, display an error message
    if [ -z "$1" ]; then
        echo "Error: No argument provided for running the program."
        echo "Usage: $0 <path_to_argument>"
        exit 1
    fi

    # Run the executable with the provided path argument
    echo "Running $EXECUTABLE with argument: $1"
    $EXECUTABLE "$1"
}

# Function to clean up built artifacts (object files and binary)
clean() {
    echo "Cleaning up build artifacts..."
    rm -rf $OBJ_DIR
    rm -rf $BIN_DIR
    echo "Clean completed."
}

# Logic to handle different command-line arguments
case "$1" in
    # If "build" is passed as an argument, clean and then build the project
    build)
        clean
        build
        ;;
    # If "run" is passed as an argument, build the project and then run executable with the provided path argument
    run)
        build
        shift
        run "$@"
        ;;
    # If "clean" is passed as an argument, clean the build artifacts
    clean)
        clean
        ;;
    # If no valid argument is provided, display usage information
    *)
        echo "Usage: $0 {build|run <path_to_argument>|clean}"
        exit 1
        ;;
esac