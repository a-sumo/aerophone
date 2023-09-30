#pragma once

#include <rtaudio/RtAudio.h>
#include "simulation/WaveSimulation.h"
#include "simulation/DigitalWaveguide.h"

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    void startAudio();
    void stopAudio();

    // Methods to set fluid parameters
    void setPipeLength(double velocity);
    void setAmplitude(double pressure);
    void setWaveguideLength(size_t length);

    const DigitalWaveguide& getWaveguide() const { return waveguide; }

private:
    DigitalWaveguide waveguide;  // Replace WaveSimulation with this
    double pipeLength = 0.0;  // Default to zero
    double Amplitude = 0.0;  // Default to zero

    static int audioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
                             double streamTime, RtAudioStreamStatus status, void* data);
    RtAudio dac;
};
