#include "audio_handler.h"
#include "automaton_2d.h"

#define WIDTH 512
#define HEIGHT 512

int audio_callback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                   double streamTime, RtAudioStreamStatus status, void *userData)
{
    uint8_t **current_state = (uint8_t **)userData;

    // Get the average audio data from a small domain.
    float *buffer = (float *)outputBuffer;
    unsigned int domainSize = 10; // Example domain size
    float sum = 0.0f;
    for (unsigned int i = HEIGHT / 2 - domainSize / 2; i < HEIGHT / 2 + domainSize / 2; ++i)
    {
        for (unsigned int j = WIDTH / 2 - domainSize / 2; j < WIDTH / 2 + domainSize / 2; ++j)
        {
            sum += current_state[i][j];
        }
    }
    float avg = sum / (domainSize * domainSize);

    for (unsigned int i = 0; i < nBufferFrames; ++i)
    {
        buffer[i] = avg / 255.0f - 0.5f; // Normalize to [-0.5, 0.5]
    }
    return 0;
}
