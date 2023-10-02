#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automaton_2d.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 512
#define HEIGHT 512
#define STEPS 100

int main()
{
    uint8_t **current_state = malloc(HEIGHT * sizeof(uint8_t *));
    uint8_t **next_state = malloc(HEIGHT * sizeof(uint8_t *));
    for (int i = 0; i < HEIGHT; i++)
    {
        current_state[i] = calloc(WIDTH, sizeof(uint8_t));
        next_state[i] = calloc(WIDTH, sizeof(uint8_t));
    }

    // Seed the simulation with a more pronounced pulse
    for (int i = HEIGHT / 2 - 5; i < HEIGHT / 2 + 5; i++)
    {
        for (int j = WIDTH / 2 - 5; j < WIDTH / 2 + 5; j++)
        {
            current_state[i][j] = 255;
        }
    }

    for (int step = 0; step < STEPS; step++)
    {
        char filename[256];
        snprintf(filename, sizeof(filename), "output_%03d.png", step);
        stbi_write_png(filename, WIDTH, HEIGHT, 1, &current_state[0][0], WIDTH);

        compute_next_state(current_state, next_state, WIDTH, HEIGHT);
        uint8_t **temp = current_state;
        current_state = next_state;
        next_state = temp;
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        free(current_state[i]);
        free(next_state[i]);
    }
    free(current_state);
    free(next_state);

    return 0;
}
