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
void RenderingWidget::setAudioEngine(const AudioEngine* engine)
{
    audioEngine = engine;
}
void RenderingWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    // get audio engine
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::black);  // Fill the background with black

    if (audioEngine->getCurrentMode() == AudioEngine::WAVEGUIDE) 
    {
        // Drawing the waveguide plot with labeled axes
        QRect plotRect(50, 50, this->width() - 100, this->height() - 100);
        painter.drawRect(plotRect);

        // Labeling axes
        painter.drawText(25, plotRect.center().y(), "0");
        painter.drawText(10, plotRect.top() - 5, "Max Amp");
        painter.drawText(10, plotRect.bottom() + 15, "-Max Amp");
        
        // Drawing the waveform inside the plot
        const auto& waveValues = waveguide->getValues();
        double scaleX = static_cast<double>(plotRect.width()) / waveValues.size();
        double scaleY = plotRect.height() / 2.0;
        int prevY = plotRect.center().y();

        for (size_t i = 0; i < waveValues.size(); ++i)
        {
            int x = plotRect.left() + i * scaleX;
            int y = plotRect.center().y() - static_cast<int>(waveValues[i] * scaleY);
            painter.drawLine(x - scaleX, prevY, x, y);
            prevY = y;
        }
    } 
    else if (audioEngine->getCurrentMode() == AudioEngine::AEOLIAN_TONE) 
    {
        // Drawing the cylinder (tube) as a rectangle
        double diameter = audioEngine->getAeolianDiameter() * 0.1;  // Adjust scaling as necessary
        QRect cylinderRect(this->width() / 4, this->height() / 2 - diameter / 2, this->width() / 2, diameter);
        painter.drawRect(cylinderRect);

        // Animated arrows to represent the air flow
        double flowVelocity = audioEngine->getAeolianFlowVelocity();
        int arrowLength = static_cast<int>(flowVelocity * 0.1);  // Adjust scaling as necessary
        painter.drawLine(cylinderRect.left() - 20, cylinderRect.center().y(), cylinderRect.left() - 20 - arrowLength, cylinderRect.center().y());
        painter.drawLine(cylinderRect.right() + 20, cylinderRect.center().y(), cylinderRect.right() + 20 + arrowLength, cylinderRect.center().y());

        // TODO: Add more visual elements to represent reflection, propagation, or any other dynamics inside the cylinder.
    }
}




void RenderingWidget::updateVisualization()
{
    // Fetch data from the simulation and update the visualization
    // Then trigger a repaint
    this->update();
}
