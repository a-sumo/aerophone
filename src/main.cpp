#include <QApplication>
#include "audio/AudioEngine.h"
#include "simulation/WaveSimulation.h"
#include "gui/MainWindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    
    AudioEngine audioEngine;
    audioEngine.startAudio();

    WaveSimulation simulation({0.01, 0.012, 0.015, 0.018, 0.02});

    MainWindow window(&audioEngine);

    window.getRenderingWidget()->setWaveSimulation(&simulation);  // Set the simulation instance to the rendering widget
    window.show();

    int ret = app.exec();

    audioEngine.stopAudio();
    return ret;
}
