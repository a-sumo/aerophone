#include "computationworker.h"
#include "automaton_2d.h"
#include "audio_handler.h"

// ... other necessary includes ...

#define WIDTH 512
#define HEIGHT 512
#define STEPS 44100

ComputationWorker::ComputationWorker(QObject *parent) : QObject(parent) {
    // Initialization code, if any
}

ComputationWorker::~ComputationWorker() {
    // Cleanup code, if any
}

void ComputationWorker::process() {
    // Move your computational code here
    // For example:

    uint8_t **current_state = /* ... */
    uint8_t **next_state = /* ... */

    for (int step = 0; step < STEPS; step++) {
        // ... your existing computation ...

        // Conditionally update the visualizer to achieve 60 FPS
        if (step % (STEPS / 60) == 0) {
            emit imageReady(current_state);
        }
    }

    // ... cleanup ...

    emit finished();  // Signal when the work is done
}
