#include "WaveSimulation.h"
#include <cmath>

// Coefficients for reflection based on change in area
// This is a simple model; in reality, the reflection and transmission would be more complex.
double reflectionCoefficient(double r1, double r2) {
    double A1 = M_PI * r1 * r1;
    double A2 = M_PI * r2 * r2;
    return (A2 - A1) / (A2 + A1);
}

WaveSimulation::WaveSimulation(const std::vector<double>& initialRadii) 
    : radii(initialRadii), previousValues(initialRadii.size(), 0.0) {}
    
void WaveSimulation::setRadii(const std::vector<double>& newRadii) {
    radii = newRadii;
}

double WaveSimulation::updateAndGetSample(double inputSample) {
    double signal = inputSample;
    for (size_t i = 0; i < radii.size(); ++i) {
        double reflection = (i == 0) ? 0.0 : reflectionCoefficient(radii[i-1], radii[i]);
        double transmission = signal * (1.0 - reflection);
        signal = transmission + previousValues[i];
        previousValues[i] = std::abs(signal * reflection);  // Take the absolute value for visualization
    }
    return signal;  // This is the signal at the end of the tube
}

