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

void RenderingWidget::paintEvent(QPaintEvent* event)
{
 QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::black); // Fill the background with black


    const int tubeWidth = 20;
    const double amplitudeScaling = 1000.0;

    if (simulation)
    {
        const auto& radii = simulation->getRadii();
        const auto& values = simulation->getPreviousValues();
        // log values
        for (size_t i = 0; i < radii.size(); ++i)
        {
            std::cout << "radii[" << i << "] = " << radii[i] << std::endl;
            std::cout << "values[" << i << "] = " << values[i] << std::endl;
        }
        int x = 10;

        for (size_t i = 0; i < radii.size(); ++i)
        {
            int height = static_cast<int>(radii[i] * amplitudeScaling);
            QColor color(0, 0, 255, static_cast<int>(values[i] * 255));  // Blue with intensity based on wave value

            QRect rect(x, (this->height() - height) / 2, tubeWidth, height);
            painter.fillRect(rect, color);

            x += tubeWidth + 5;
        }
    }
}


void RenderingWidget::updateVisualization()
{
    // Fetch data from the simulation and update the visualization
    // Then trigger a repaint
    this->update();
}
