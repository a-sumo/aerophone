#!/bin/bash

# Get the directory of the current script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Navigate to the project directory
cd $DIR

# Remove the build directory if it exists
if [ -d "build" ]; then
    rm -r build
fi

# Create a new build directory and navigate into it
mkdir build
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
    ./aerophone
else
    echo "Build process encountered errors!"
fi
