#include "AudioEngine.h"
#include "simulation/WaveSimulation.h"
#include <iostream>
#include <cmath>

constexpr double TAU = 6.283185307179586; // 2*Pi
constexpr double FREQUENCY = 440.0;       // A4 note frequency

AudioEngine::AudioEngine() : simulation({0.01, 0.012, 0.015, 0.018, 0.02})
{
    if (dac.getDeviceCount() < 1)
    {
        std::cerr << "No audio devices found!" << std::endl;
        exit(-1);
    }
}

AudioEngine::~AudioEngine()
{
    if (dac.isStreamOpen())
        dac.closeStream();
}

void AudioEngine::startAudio()
{
    if (dac.isStreamOpen())
    {
        dac.stopStream();
        dac.closeStream();
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1; // Mono output

    unsigned int sampleRate = 44100; // Standard audio sample rate
    unsigned int bufferFrames = 256; // Buffer size

    try
    {
        dac.openStream(&parameters, NULL, RTAUDIO_FLOAT64, sampleRate, &bufferFrames, &audioCallback, this);
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
        // ... handle other error types ...
        default:
            errorMessage = "Unhandled RtAudio error!";
        }
        std::cerr << "Failed to start audio stream: " << errorMessage << std::endl;
        exit(-1);
    }
}

void AudioEngine::stopAudio()
{
    dac.stopStream();
}

int AudioEngine::audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                               double streamTime, RtAudioStreamStatus status, void *data)
{
    AudioEngine *self = static_cast<AudioEngine *>(data);
    double *outBuffer = reinterpret_cast<double *>(outputBuffer);

    for (unsigned int i = 0; i < nBufferFrames; ++i)
    {
        double inputSample = std::sin(TAU * FREQUENCY * streamTime); // Sine wave for testing
        outBuffer[i] = self->simulation.updateAndGetSample(inputSample);
    }

    return 0;
}
