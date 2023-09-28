#pragma once

#include <QMainWindow>
#include "RenderingWidget.h"
#include "audio/AudioEngine.h"  // Include the header for AudioEngine

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AudioEngine* audioEngine, QWidget* parent = nullptr);  // Adjust the constructor to accept an AudioEngine pointer
    RenderingWidget* getRenderingWidget() const;

private slots:
    void updateSimulationSettings();  // To be connected with sliders or other controls

private:
    RenderingWidget* renderingWidget;
    AudioEngine* audioEngine;  // Member variable for AudioEngine
    // Add other UI elements like sliders, buttons, etc. here
};
