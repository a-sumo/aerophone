#pragma once

#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include "RenderingWidget.h"
#include "audio/AudioEngine.h"
#include "simulation/DigitalWaveguide.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AudioEngine *audioEngine, QWidget *parent = nullptr);
    RenderingWidget *getRenderingWidget() const;

private slots:
    void updateSimulationSettings();
    void setPipeLength();
    void setAmplitude();

private:
    RenderingWidget *renderingWidget;
    AudioEngine *audioEngine;
    QSlider *lengthSlider;
    QSlider *amplitudeSlider;
    QSlider *aeolianDiameterSlider;
    

private slots:
    void setAeolianDiameter();
};