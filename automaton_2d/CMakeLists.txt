cmake_minimum_required(VERSION 3.10)
project(Automaton2D LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0" CACHE STRING "Minimum OS X deployment version")

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find RtAudio header and library
find_path(RTAUDIO_INCLUDE_DIR NAMES "RtAudio.h")
find_library(RTAUDIO_LIBRARY NAMES rtaudio)

# Fallback to hardcoded paths if not found
if(NOT RTAUDIO_INCLUDE_DIR)
    set(RTAUDIO_INCLUDE_DIR "/opt/homebrew/opt/rtaudio/include")
endif()

if(NOT RTAUDIO_LIBRARY)
    set(RTAUDIO_LIBRARY "/opt/homebrew/opt/rtaudio/lib/librtaudio.dylib")
endif()

# Check if the paths are valid
if(NOT RTAUDIO_INCLUDE_DIR OR NOT RTAUDIO_LIBRARY)
    message(FATAL_ERROR "RtAudio not found!")
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Xclang -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Xclang -fopenmp")

# Source files
set(SOURCES
    src/main.cpp
    src/automaton_2d.cpp
    src/audio_handler.cpp
)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
qt_add_executable(automaton_example ${SOURCES})

set(OPENMP_LIB_PATH "/opt/homebrew/opt/libomp/lib/libomp.dylib")
set(OPENMP_INCLUDE_PATH "/opt/homebrew/opt/libomp/include")

target_include_directories(automaton_example PRIVATE 
    ${RTAUDIO_INCLUDE_DIR} 
    ${OPENMP_INCLUDE_PATH} 
    include
    external
)

target_link_libraries(automaton_example PRIVATE 
    Qt6::Core Qt6::Widgets
    ${RTAUDIO_LIBRARY} 
    ${OPENMP_LIB_PATH}
)

# Treat all warnings as errors
set_target_properties(automaton_example PROPERTIES
    COMPILE_WARNING_AS_ERROR ON
)

# Extra compiler warnings
if (MSVC)
    target_compile_options(automaton_example PRIVATE /W4)
else()
    target_compile_options(automaton_example PRIVATE -Wall -Wextra -pedantic)
endif()

# XCode specific settings for macOS
if(XCODE)
    set_target_properties(automaton_example PROPERTIES
        XCODE_GENERATE_SCHEME ON
        XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE "Metal")
endif()

# Integrate GLFW into the project
add_subdirectory(glfw)
target_link_libraries(automaton_example PRIVATE glfw)