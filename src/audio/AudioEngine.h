#pragma once

#include <rtaudio/RtAudio.h>
#include "simulation/WaveSimulation.h"

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    void startAudio();
    void stopAudio();

private:
    WaveSimulation simulation;
    static int audioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
                             double streamTime, RtAudioStreamStatus status, void* data);
    RtAudio dac;
};
