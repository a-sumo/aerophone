#pragma once

#include <QWidget>
#include <QTimer>
#include "simulation/WaveSimulation.h"
#include "simulation/DigitalWaveguide.h"

class RenderingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderingWidget(QWidget* parent = nullptr);
    void setWaveSimulation(WaveSimulation* simulation);
    void setWaveguide(const DigitalWaveguide& waveguide);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void updateVisualization();

private:
    QTimer timer;
    WaveSimulation* simulation;
    const DigitalWaveguide* waveguide;

    // Add other attributes related to visualization here, e.g., current wave position
};
