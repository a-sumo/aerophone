#pragma once
#include <vector>

class DigitalWaveguide {
public:
    DigitalWaveguide(size_t length);
    const std::vector<double>& getValues() const { return delayLine; }
    size_t getLength() const { return delayLine.size(); }
    // Adjust the length of the waveguide
    void setLength(size_t length);
    
    // Process a sample through the waveguide
    double processSample(double inputSample);
    
    // Set reflection and transmission coefficients
    void setReflectionCoefficient(double coefficient);
    void setTransmissionCoefficient(double coefficient);

private:
    std::vector<double> delayLine;
    size_t currentIdx;

    double reflectionCoefficient = 0.5;   // Default reflection
    double transmissionCoefficient = 0.5; // Default transmission
};

