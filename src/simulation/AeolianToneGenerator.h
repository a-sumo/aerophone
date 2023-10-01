#pragma once

class AeolianToneGenerator {
public:
    AeolianToneGenerator(double diameter);
    // reset
    void reset();
    // Process a sample through the tone generator
    double processSample(double flowVelocity);

    // Set and get the diameter of the object
    void setDiameter(double diameter);
    double getDiameter() const;
    // Set and get the flow velocity of the fluid
    void setFlowVelocity(double flowVelocity);
    double getFlowVelocity() const;

private:
    double diameter;
    double flowVelocity;
    const double strouhalNumber = 0.2;  // Typical value for cylinders
};
