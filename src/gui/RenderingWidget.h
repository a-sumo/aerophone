#pragma once

#include <QWidget>
#include <QTimer>
#include "audio/AudioEngine.h"
#include "simulation/WaveSimulation.h"
#include "simulation/DigitalWaveguide.h"

class RenderingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderingWidget(QWidget* parent = nullptr);
    void setWaveSimulation(WaveSimulation* simulation);
    void setWaveguide(const DigitalWaveguide& waveguide);
    void setAudioEngine(const AudioEngine* engine);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void updateVisualization();

private:
    QTimer timer;
    WaveSimulation* simulation;
    const DigitalWaveguide* waveguide;
    const AudioEngine* audioEngine;
    // Add other attributes related to visualization here, e.g., current wave position
};
