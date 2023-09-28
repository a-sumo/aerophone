#!/bin/bash

# Navigate to the project directory
cd /Users/armand/Documents/percept-tech

# Remove the build directory if it exists
if [ -d "build" ]; then
    rm -r build
fi

# Create a new build directory and navigate into it
mkdir build
cd build

# Run CMake
cmake ..

# If CMake completes without errors, run make
if [ $? -eq 0 ]; then
    make
else
    echo "CMake encountered errors!"
fi

# If make completes without errors, run the executable
if [ $? -eq 0 ]; then
    ./helloworld
else
    echo "Make encountered errors!"
fi
```