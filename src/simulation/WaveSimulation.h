#pragma once
#include <vector>

class WaveSimulation {
public:
    explicit WaveSimulation(const std::vector<double>& initialRadii);
    const std::vector<double>& getRadii() const { return radii; }
    const std::vector<double>& getPreviousValues() const { return previousValues; }
    
    void setRadii(const std::vector<double>& radii);
    double updateAndGetSample(double inputSample);  // processes the input sample and returns the output sample

private:
    std::vector<double> radii;
    std::vector<double> previousValues;  // delay line for each segment
};
