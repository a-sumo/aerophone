#include "RenderingWidget.h"
#include <QPainter>
#include <iostream>
RenderingWidget::RenderingWidget(QWidget* parent) : QWidget(parent), simulation(nullptr)
{
    // Set up the update timer
    connect(&timer, &QTimer::timeout, this, &RenderingWidget::updateVisualization);
    timer.start(16);  // About 60fps
    this->setStyleSheet("background-color: black;");
    this->setFixedSize(750, 500);  // Set a fixed size for the rendering widget for testing
}

void RenderingWidget::setWaveSimulation(WaveSimulation* sim)
{
    simulation = sim;
}

void RenderingWidget::setWaveguide(const DigitalWaveguide& wg) 
{
    waveguide = &wg;
}
void RenderingWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::black);  // Fill the background with black

    const double amplitudeScaling = 50.0;  // Adjust this value based on your needs

    // Draw the waveguide as a long rectangle
    int waveguideLength = waveguide ? waveguide->getLength() : 0;  // Get the length from the waveguide
    QRect waveguideRect(10, this->height() / 2 - 10, waveguideLength * 2.0, 20);  // Modify as necessary

    // Draw white lines 
    painter.setPen(Qt::white);

    // Draw the waveguide
    painter.drawRect(waveguideRect);  // White waveguide
    
    // Draw a baseline in the middle of the waveguide
    painter.drawLine(waveguideRect.left(), waveguideRect.center().y(), waveguideRect.right(), waveguideRect.center().y());

    // Draw the waveform inside the waveguide
    if (waveguide)
    {
        const auto& waveValues = waveguide->getValues();  // Assuming you have such a method
        int x = 10;
        int prevY = this->height() / 2;

        for (size_t i = 0; i < waveValues.size(); ++i)
        {
            int y = this->height() / 2 - static_cast<int>(waveValues[i] * amplitudeScaling);

            // Connect consecutive points
            painter.drawLine(x - 2, prevY, x, y);
            
            prevY = y;
            x += 2;  // Adjust as necessary
        }
    }
}



void RenderingWidget::updateVisualization()
{
    // Fetch data from the simulation and update the visualization
    // Then trigger a repaint
    this->update();
}
