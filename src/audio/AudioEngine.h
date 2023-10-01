#pragma once

#include <rtaudio/RtAudio.h>
#include "simulation/WaveSimulation.h"
#include "simulation/DigitalWaveguide.h"
#include "simulation/AeolianToneGenerator.h"

class AudioEngine {
public:
    enum Mode { WAVEGUIDE, AEOLIAN_TONE };  // Added a mode enumeration

    AudioEngine();
    ~AudioEngine();

    void startAudio();
    void stopAudio();

    // Methods to set fluid parameters
    void setPipeLength(double length);
    void setAmplitude(double amplitude);
    // get pipe length
    double getPipeLength() const;
    double getAmplitude() const;
    void setWaveguideLength(size_t length);
    
    // Methods to control the aeolian tone
    void setAeolianDiameter(double diameter);
    double getAeolianDiameter() const;
    void setAeolianFlowVelocity(double flowVelocity);
    double getAeolianFlowVelocity() const;

    const DigitalWaveguide& getWaveguide() const { return waveguide; }

    void switchMode(Mode mode);  // Method to switch between modes
    // get mode
    Mode getCurrentMode() const;

private:
    DigitalWaveguide waveguide;
    AeolianToneGenerator aeolianTone;
    double pipeLength = 0.0;  // Default to zero
    double Amplitude = 0.0;  // Default to zero
    double fluidVelocity = 40.0;  // Default to zero

    Mode currentMode = WAVEGUIDE;  // Default mode

    static int audioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
                             double streamTime, RtAudioStreamStatus status, void* data);
    RtAudio dac;
};
