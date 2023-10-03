#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automaton_2d.h"
#include "audio_handler.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>

#define WIDTH 512
#define HEIGHT 512
#define STEPS 1000 // Assuming longer steps for visualization

int main()
{
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
    unsigned int bufferFrames = 256;

    try
    {
        dac.openStream(&parameters, NULL, RTAUDIO_FLOAT32, sampleRate, &bufferFrames, &audio_callback, (void *)current_state);
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
#pragma omp parallel sections
        {
#pragma omp section
            compute_next_state(current_state, next_state, WIDTH, HEIGHT);

#pragma omp section
            apply_boundary_conditions(current_state, WIDTH, HEIGHT);

#pragma omp section
            add_sustained_excitation(current_state, WIDTH, HEIGHT, step);
        }

        if (step % 1000 == 0)
        {
            // Visualize every 1000 steps
            uint8_t *flat_buffer = (uint8_t *)calloc(WIDTH * HEIGHT, sizeof(uint8_t));
            for (size_t y = 0; y < HEIGHT; y++)
            {
                for (size_t x = 0; x < WIDTH; x++)
                {
                    flat_buffer[y * WIDTH + x] = current_state[y][x];
                }
            }

            char filename[256];
            snprintf(filename, sizeof(filename), "output/output_%05d.png", step / 367);
            stbi_write_png(filename, WIDTH, HEIGHT, 1, flat_buffer, WIDTH);

            free(flat_buffer);
        }

        for (size_t i = 0; i < HEIGHT; i++)
        {
            memcpy(current_state[i], next_state[i], WIDTH * sizeof(uint8_t));
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
    return 0;
}
