#include "AeolianToneGenerator.h"
#include <cmath>

const double TAU = 6.283185307179586; // 2*Pi

AeolianToneGenerator::AeolianToneGenerator(double diameter) : diameter(diameter) {}

double AeolianToneGenerator::processSample(double flowVelocity)
{
    // Calculate the aeolian tone fundamental frequency
    double fundamentalFrequency = (diameter != 0) ? strouhalNumber * flowVelocity / (diameter * 0.1) : 0.0;
    // Generate a sinusoidal tone at this frequency with harmonics
    static double phase = 0;
    double sample = 0;
    const int maxHarmonics = 3; // Let's consider 3 harmonics for this example
    for (int n = 1; n <= maxHarmonics; n++)
    {
        sample += (1.0 / n) * std::sin(n * phase); // The 1/n term reduces the strength of higher harmonics
    }

    // Amplitude modulation based on flow velocity
    double amplitude = 0.1 * flowVelocity;
    sample *= amplitude;

    phase += TAU * fundamentalFrequency / 44100.0; // Assuming a sample rate of 44100 Hz
    if (phase > TAU)
    {
        phase -= TAU;
    }

    return sample;
}

void AeolianToneGenerator::setDiameter(double d)
{
    diameter = d;
}

double AeolianToneGenerator::getDiameter() const
{
    return diameter;
}

void AeolianToneGenerator::setFlowVelocity(double v)
{
    flowVelocity = v;
}

double AeolianToneGenerator::getFlowVelocity() const
{
    return flowVelocity;
}

 // implement reset method to clear any internal state
void AeolianToneGenerator::reset()
{
    // Reset the phase
    // 
}
