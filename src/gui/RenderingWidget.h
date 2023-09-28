#pragma once

#include <QWidget>
#include <QTimer>
#include "simulation/WaveSimulation.h"

class RenderingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderingWidget(QWidget* parent = nullptr);
    void setWaveSimulation(WaveSimulation* simulation);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void updateVisualization();

private:
    QTimer timer;
    WaveSimulation* simulation;

    // Add other attributes related to visualization here, e.g., current wave position
};
