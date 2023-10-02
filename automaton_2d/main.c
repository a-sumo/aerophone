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
    for (size_t i = 0; i < HEIGHT; i++)
    { // Use size_t for the loop variable to fix the warning
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

    for (int step = 0; step < 10 * STEPS; step++)
    { // 10 times the STEPS for longer simulation
        compute_next_state(current_state, next_state, WIDTH, HEIGHT);
        apply_boundary_conditions(current_state, WIDTH, HEIGHT);
        add_sustained_excitation(current_state, WIDTH, HEIGHT, step);

        if (step % (367*10) == 0)
        {
            // Visualize every 367 steps
            uint8_t *flat_buffer = calloc(WIDTH * HEIGHT, sizeof(uint8_t));

            for (size_t y = 0; y < HEIGHT; y++)
            {
                for (size_t x = 0; x < WIDTH; x++)
                {
                    flat_buffer[y * WIDTH + x] = current_state[y][x];
                }
            }

            char filename[256];
            snprintf(filename, sizeof(filename), "output/output_%05d.png", step / 367);
            stbi_write_png(filename, WIDTH, HEIGHT, 1, flat_buffer, WIDTH);

            free(flat_buffer);
        }

        for (size_t i = 0; i < HEIGHT; i++)
        {
            memcpy(current_state[i], next_state[i], WIDTH * sizeof(uint8_t));
        }
    }

    for (size_t i = 0; i < HEIGHT; i++)
    { // Use size_t for the loop variable to fix the warning
        free(current_state[i]);
        free(next_state[i]);
    }
    free(current_state);
    free(next_state);
    return 0;
}
