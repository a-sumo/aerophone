#!/bin/bash

# Get the directory of the current script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Navigate to the project directory
cd $DIR

# If the argument is "clean", remove the entire build directory
if [ "$1" == "clean" ]; then
    if [ -d "build" ]; then
        rm -r build
    fi
    exit 0
fi

# If the build directory doesn't exist, create it
if [ ! -d "build" ]; then
    mkdir build
fi

# If CMakeCache.txt exists, empty it to force reconfiguration
if [ -f "build/CMakeCache.txt" ]; then
    > build/CMakeCache.txt
fi

cd build

# Check for RtAudio argument
if [ "$1" ]; then
    RTAUDIO_PATH=$1
    cmake .. -DRTAUDIO_INCLUDE_DIR=$RTAUDIO_PATH/include -DRTAUDIO_LIBRARY=$RTAUDIO_PATH/lib/librtaudio.dylib
else
    cmake ..
fi

# If CMake completes without errors, build the project
if [ $? -eq 0 ]; then
    cmake --build . --config Release
else
    echo "CMake encountered errors!"
fi

# If build completes without errors, run the executable
if [ $? -eq 0 ]; then
    ./automaton_example
else
    echo "Build process encountered errors!"
fi
