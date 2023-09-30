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

    // Fluid velocity slider
    layout->addWidget(new QLabel("Pipe Length:", this));
    velocitySlider = new QSlider(Qt::Horizontal, this);
    layout->addWidget(velocitySlider);
    connect(velocitySlider, &QSlider::valueChanged, this, &MainWindow::setPipeLength);

    // Fluid pressure slider
    layout->addWidget(new QLabel("Amplitude:", this));
    pressureSlider = new QSlider(Qt::Horizontal, this);
    layout->addWidget(pressureSlider);
    connect(pressureSlider, &QSlider::valueChanged, this, &MainWindow::setAmplitude);

    velocitySlider->setRange(0, 10);  // e.g., 0 to 10 units
    pressureSlider->setRange(0, 10);  // e.g., 0 to 10 units

    // Toggle audio button
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

    // This is the corrected line
    this->getRenderingWidget()->setWaveguide(audioEngine->getWaveguide());

    this->setCentralWidget(centralWidget);
    this->setStyleSheet("background-color: black;");
}

void MainWindow::setPipeLength()
{
    audioEngine->setPipeLength(velocitySlider->value() / 100.0);
}

void MainWindow::setAmplitude()
{
    audioEngine->setAmplitude(pressureSlider->value() / 100.0);
}

RenderingWidget* MainWindow::getRenderingWidget() const
{
    return renderingWidget;
}

void MainWindow::updateSimulationSettings()
{
    // TODO: Update the renderingWidget with the new values
}
