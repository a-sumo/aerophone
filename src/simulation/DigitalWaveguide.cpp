#include "DigitalWaveguide.h"

DigitalWaveguide::DigitalWaveguide(size_t length)
    : delayLine(length, 0.0), currentIdx(0) {}

void DigitalWaveguide::setLength(size_t length) {
    delayLine.resize(length, 0.0);
}

double DigitalWaveguide::processSample(double inputSample) {
    // Get the sample from the delay line
    double delayedSample = delayLine[currentIdx];

    // Update delay line with the new sample
    delayLine[currentIdx] = inputSample;

    // Update the index for the next round
    currentIdx = (currentIdx + 1) % delayLine.size();

    // Return a mix of the delayed sample and the input (basic reflection and transmission)
    return reflectionCoefficient * delayedSample + transmissionCoefficient * inputSample;
}

void DigitalWaveguide::setReflectionCoefficient(double coefficient) {
    reflectionCoefficient = coefficient;
}

void DigitalWaveguide::setTransmissionCoefficient(double coefficient) {
    transmissionCoefficient = coefficient;
}
