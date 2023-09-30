#include <QApplication>
#include "audio/AudioEngine.h"
#include "gui/MainWindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    
    AudioEngine audioEngine;
    audioEngine.startAudio();

    MainWindow window(&audioEngine);
    window.show();

    int ret = app.exec();

    audioEngine.stopAudio();
    return ret;
}
