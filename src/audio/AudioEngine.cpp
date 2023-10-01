#include "AudioEngine.h"
#include "simulation/WaveSimulation.h"
#include <iostream>
#include <cmath>

constexpr double TAU = 6.283185307179586; // 2*Pi
constexpr double BASE_FREQUENCY = 440.0;  // A4 note frequency

AudioEngine::AudioEngine()
    : waveguide(44100 / BASE_FREQUENCY),
      aeolianTone(1.0)
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

void AudioEngine::setPipeLength(double length)
{
    pipeLength = length;
    size_t newLength = static_cast<size_t>(100 + pipeLength * 1000); // Just an example mapping
    setWaveguideLength(newLength);
}

void AudioEngine::setAmplitude(double amplitude)
{
    Amplitude = amplitude;
}

void AudioEngine::setWaveguideLength(size_t length)
{
    waveguide.setLength(length);
}
void AudioEngine::setAeolianDiameter(double diameter)
{
    aeolianTone.setDiameter(diameter);
}

double AudioEngine::getAeolianDiameter() const
{
    return aeolianTone.getDiameter();
}

void AudioEngine::setAeolianFlowVelocity(double flowVelocity)
{
    fluidVelocity = flowVelocity;
}

double AudioEngine::getAeolianFlowVelocity() const
{
    return fluidVelocity;
}
double AudioEngine::getAmplitude() const
{
    return Amplitude;
}
double AudioEngine::getPipeLength() const
{
    return pipeLength;
}
AudioEngine::Mode AudioEngine::getCurrentMode() const
{
    return currentMode;
}
void AudioEngine::switchMode(Mode mode)
{
    // Stop the audio temporarily to avoid artifacts
    stopAudio();

    // Reset waveguide state if switching away from WAVEGUIDE
    if (currentMode == WAVEGUIDE && mode != WAVEGUIDE)
    {
        waveguide.reset(); // Assuming a reset method that clears waveguide state
    }

    // Reset aeolianTone state if switching away from AEOLIAN_TONE
    // (You may need to implement a reset method for AeolianToneGenerator)
    if (currentMode == AEOLIAN_TONE && mode != AEOLIAN_TONE)
    {
        aeolianTone.reset();
    }

    currentMode = mode;

    // Restart the audio
    startAudio();
}

int AudioEngine::audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                               double streamTime, RtAudioStreamStatus status, void *data)
{
    AudioEngine *self = static_cast<AudioEngine *>(data);
    double *outBuffer = reinterpret_cast<double *>(outputBuffer);

    switch (self->currentMode)
    {
    case WAVEGUIDE:
        for (unsigned int i = 0; i < nBufferFrames; ++i)
        {
            double modulatedFrequency = BASE_FREQUENCY + self->pipeLength * 10.0;
            double inputSample = self->Amplitude * std::sin(TAU * modulatedFrequency * streamTime);
            outBuffer[i] = self->waveguide.processSample(inputSample);
        }
        break;

    case AEOLIAN_TONE:
        for (unsigned int i = 0; i < nBufferFrames; ++i)
        {
            outBuffer[i] = self->aeolianTone.processSample(self->fluidVelocity);
        }
        break;
    }
    return 0;
}