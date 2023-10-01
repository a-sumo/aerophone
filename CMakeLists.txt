cmake_minimum_required(VERSION 3.16)

project(helloworld VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the RtAudio header and library
set(RTAUDIO_INCLUDE_DIR "/opt/homebrew/opt/rtaudio/include")
set(RTAUDIO_LIBRARY "/opt/homebrew/opt/rtaudio/lib/librtaudio.dylib")

if(NOT RTAUDIO_INCLUDE_DIR OR NOT RTAUDIO_LIBRARY)
    message(FATAL_ERROR "RtAudio not found!")
endif()

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

# Create the executable
qt_add_executable(helloworld
    src/main.cpp
    src/audio/AudioEngine.cpp
    src/audio/AudioEngine.h
    src/simulation/WaveSimulation.cpp
    src/simulation/WaveSimulation.h
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/RenderingWidget.cpp
    src/gui/RenderingWidget.h
    src/simulation/AeolianToneGenerator.cpp
    src/simulation/AeolianToneGenerator.h
    src//simulation/DigitalWaveguide.h
    src/simulation/DigitalWaveguide.cpp

)

# Link against Qt and RtAudio libraries
target_include_directories(helloworld PRIVATE 
    ${RTAUDIO_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(helloworld PRIVATE Qt6::Core Qt6::Widgets ${RTAUDIO_LIBRARY})

