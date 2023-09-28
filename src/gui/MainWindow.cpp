#include "MainWindow.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>

MainWindow::MainWindow(AudioEngine* engine, QWidget* parent)
    : QMainWindow(parent), audioEngine(engine)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    renderingWidget = new RenderingWidget(centralWidget);
    layout->addWidget(renderingWidget);

    // Sample slider for demonstration
    QSlider* slider = new QSlider(Qt::Horizontal, this);
    layout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::updateSimulationSettings);

    // Sample button to stop/start audio for demonstration
    QPushButton* audioButton = new QPushButton("Toggle Audio", this);
    layout->addWidget(audioButton);
    connect(audioButton, &QPushButton::clicked, [this]() {
        static bool isAudioRunning = true;
        if (isAudioRunning) {
            audioEngine->stopAudio();
        } else {
            audioEngine->startAudio();
        }
        isAudioRunning = !isAudioRunning;
    });

    this->setCentralWidget(centralWidget);
    this->setStyleSheet("background-color: black;");
}

RenderingWidget* MainWindow::getRenderingWidget() const
{
    return renderingWidget;
}

void MainWindow::updateSimulationSettings()
{
    // Fetch values from sliders and other controls (for example, the sample slider above)
    // Update the renderingWidget with the new values

    // This line seems to be a comment or a mistake, I'll comment it out for now
    // renderingWidget->updateVisualization() or similar
}
