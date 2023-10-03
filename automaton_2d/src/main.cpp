#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automaton_2d.h"
#include "audio_handler.h"
#include "stb_image_write.h"
#include <iostream>
#include <QApplication>
#include <mutex>

#define WIDTH 256
#define HEIGHT 256
#define STEPS 44100

// Double buffering
uint8_t **currentStateBuffer1;
uint8_t **currentStateBuffer2;
uint8_t **readState = nullptr;  // Used by audio_callback
uint8_t **writeState = nullptr; // Updated by automaton

std::mutex bufferSwapMutex; // Used to protect buffer swap operations

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Visualizer visualizer;
    // visualizer.show();
    auto start_time = std::chrono::high_resolution_clock::now(); // Start timing

    uint8_t **current_state = (uint8_t **)malloc(HEIGHT * sizeof(uint8_t *));
    uint8_t **next_state = (uint8_t **)malloc(HEIGHT * sizeof(uint8_t *));
    for (size_t i = 0; i < HEIGHT; i++)
    {
        current_state[i] = (uint8_t *)calloc(WIDTH, sizeof(uint8_t));
        next_state[i] = (uint8_t *)calloc(WIDTH, sizeof(uint8_t));
    }

    // Seed the simulation with a more pronounced pulse
    for (int i = HEIGHT / 2 - 5; i < HEIGHT / 2 + 5; i++)
    {
        for (int j = WIDTH / 2 - 5; j < WIDTH / 2 + 5; j++)
        {
            current_state[i][j] = 255;
        }
    }
    currentStateBuffer1 = (uint8_t **)malloc(HEIGHT * sizeof(uint8_t *));
    currentStateBuffer2 = (uint8_t **)malloc(HEIGHT * sizeof(uint8_t *));
    for (size_t i = 0; i < HEIGHT; i++)
    {
        currentStateBuffer1[i] = (uint8_t *)calloc(WIDTH, sizeof(uint8_t));
        currentStateBuffer2[i] = (uint8_t *)calloc(WIDTH, sizeof(uint8_t));
    }

    readState = currentStateBuffer1;
    writeState = currentStateBuffer2;
    // Initialize RtAudio and stream audio
    RtAudio dac;
    if (dac.getDeviceCount() < 1)
    {
        std::cout << "\nNo audio devices found!\n";
        exit(0);
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256; // 256 sample frames

    try
    {
        dac.openStream(&parameters, NULL, RTAUDIO_FLOAT32, sampleRate, &bufferFrames, &audio_callback, (void *)readState); // Corrected argument
        dac.startStream();
    }
    catch (RtAudioErrorType &e)
    {
        std::string errorMessage;
        switch (e)
        {
        case RTAUDIO_WARNING:
            errorMessage = "Warning!";
            break;
        case RTAUDIO_UNKNOWN_ERROR:
            errorMessage = "Unknown Error!";
            break;
        case RTAUDIO_NO_DEVICES_FOUND:
            errorMessage = "No devices found!";
            break;
        case RTAUDIO_INVALID_DEVICE:
            errorMessage = "Invalid device!";
            break;
        default:
            errorMessage = "Unhandled RtAudio error!";
        }
        std::cerr << "Failed to start audio stream: " << errorMessage << std::endl;
        exit(-1);
    }

    for (int step = 0; step < STEPS; step++)
    {
        auto loop_start_time = std::chrono::high_resolution_clock::now(); // Start loop timing

#pragma omp parallel sections
        {

#pragma omp section
            compute_next_state(current_state, next_state, WIDTH, HEIGHT);

#pragma omp section
            apply_boundary_conditions(current_state, WIDTH, HEIGHT);

#pragma omp section
            add_sustained_excitation(current_state, WIDTH, HEIGHT, step);
        }

        auto loop_end_time = std::chrono::high_resolution_clock::now();
        auto loop_duration = std::chrono::duration_cast<std::chrono::microseconds>(loop_end_time - loop_start_time).count();
        std::cout << "Step " << step << " took " << loop_duration << " microseconds." << std::endl;
        // Copy the newly computed state to the writeState buffer
        for (size_t i = 0; i < HEIGHT; i++)
        {
            memcpy(writeState[i], next_state[i], WIDTH * sizeof(uint8_t));
        }

        // Swap buffers after computation
        {
            std::lock_guard<std::mutex> lock(bufferSwapMutex);
            std::swap(readState, writeState);
        }
    }

    // Stop and close the audio stream
    try
    {
        dac.stopStream();
        if (dac.isStreamOpen())
            dac.closeStream();
    }
    catch (RtAudioErrorType &e)
    {
        std::string errorMessage;
        switch (e)
        {
        case RTAUDIO_WARNING:
            errorMessage = "Warning!";
            break;
        case RTAUDIO_UNKNOWN_ERROR:
            errorMessage = "Unknown Error!";
            break;
        case RTAUDIO_NO_DEVICES_FOUND:
            errorMessage = "No devices found!";
            break;
        case RTAUDIO_INVALID_DEVICE:
            errorMessage = "Invalid device!";
            break;
        default:
            errorMessage = "Unhandled RtAudio error!";
        }
        std::cerr << "Failed to stop audio stream: " << errorMessage << std::endl;
        exit(-1);
    }

    for (size_t i = 0; i < HEIGHT; i++)
    { // Use size_t for the loop variable to fix the warning
        free(current_state[i]);
        free(next_state[i]);
    }
    free(current_state);
    free(next_state);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    std::cout << "Total execution time: " << total_duration << " seconds." << std::endl;

    // return app.exec();
}
