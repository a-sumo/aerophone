#include "MainWindow.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>

MainWindow::MainWindow(AudioEngine *engine, QWidget *parent)
    : QMainWindow(parent), audioEngine(engine)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    renderingWidget = new RenderingWidget(centralWidget);
    renderingWidget->setAudioEngine(audioEngine);
    
    layout->addWidget(renderingWidget);

    // Fluid length slider
    layout->addWidget(new QLabel("Pipe Length:", this));
    lengthSlider = new QSlider(Qt::Horizontal, this);
    layout->addWidget(lengthSlider);
    connect(lengthSlider, &QSlider::valueChanged, this, &MainWindow::setPipeLength);

    // Fluid amplitude slider
    layout->addWidget(new QLabel("Amplitude:", this));
    amplitudeSlider = new QSlider(Qt::Horizontal, this);
    layout->addWidget(amplitudeSlider);
    connect(amplitudeSlider, &QSlider::valueChanged, this, &MainWindow::setAmplitude);

    lengthSlider->setRange(0, 100);    // e.g., 0 to 10 units
    amplitudeSlider->setRange(0, 100); // e.g., 0 to 10 units

    // Toggle audio button
    QPushButton *audioButton = new QPushButton("Toggle Audio", this);
    layout->addWidget(audioButton);
    // Toggle mode button
    QPushButton *modeButton = new QPushButton("Toggle Mode", this);
    layout->addWidget(modeButton);

    connect(audioButton, &QPushButton::clicked, [this]()
            {
        static bool isAudioRunning = true;
        if (isAudioRunning) {
            audioEngine->stopAudio();
        } else {
            audioEngine->startAudio();
        }
        isAudioRunning = !isAudioRunning; });

    connect(modeButton, &QPushButton::clicked, [this]()
            {
        static bool isWaveguide = true;
        if (isWaveguide) {
            audioEngine->switchMode(AudioEngine::AEOLIAN_TONE);
        } else {
            audioEngine->switchMode(AudioEngine::WAVEGUIDE);
        }
        isWaveguide = !isWaveguide; });

    // Aeolian diameter slider
    layout->addWidget(new QLabel("Aeolian Diameter:", this));
    aeolianDiameterSlider = new QSlider(Qt::Horizontal, this);
    layout->addWidget(aeolianDiameterSlider);
    connect(aeolianDiameterSlider, &QSlider::valueChanged, this, &MainWindow::setAeolianDiameter);
    // Aeolian flow velocity slider
    layout->addWidget(new QLabel("Aeolian Flow Velocity:", this));
    QSlider *aeolianFlowVelocitySlider = new QSlider(Qt::Horizontal, this);
    layout->addWidget(aeolianFlowVelocitySlider);
    connect(aeolianFlowVelocitySlider, &QSlider::valueChanged, [this](int value)
            {
        audioEngine->setAeolianFlowVelocity(value * 10.0);
    });
    aeolianFlowVelocitySlider->setRange(20, 200); // Representing 2.0 m/s to 20.0 m/s
    aeolianDiameterSlider->setRange(1, 100); // Representing a diameter from 0.01m to 1.0m
    this->getRenderingWidget()->setWaveguide(audioEngine->getWaveguide());

    this->setCentralWidget(centralWidget);
    this->setStyleSheet("background-color: black;");
}

void MainWindow::setPipeLength()
{
    double targetValue = lengthSlider->value() / 100.0;
    double currentValue = audioEngine->getPipeLength();
    audioEngine->setPipeLength(currentValue + 0.1 * (targetValue - currentValue));
}

void MainWindow::setAmplitude()
{
    double targetValue = amplitudeSlider->value() / 100.0;
    double currentValue = audioEngine->getAmplitude();
    audioEngine->setAmplitude(currentValue + 0.1 * (targetValue - currentValue));
}

void MainWindow::setAeolianDiameter()
{
    audioEngine->setAeolianDiameter(aeolianDiameterSlider->value());
}

RenderingWidget *MainWindow::getRenderingWidget() const
{
    return renderingWidget;
}

void MainWindow::updateSimulationSettings()
{
    // TODO: Update the renderingWidget with the new values
}
