#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "automaton_neon.h"

#define N 1000
#define STEPS 44100  // Assuming 44.1kHz audio rate

int main() {
    uint8_t current_state[N] = {0};
    uint8_t next_state[N] = {0};

    current_state[N/2] = 1; // Single central cell alive as an initial state

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for(int step = 0; step < STEPS; step++) {
        for(size_t i = 0; i < N; i++) {
            printf("%c", current_state[i] ? '#' : ' ');  // Using '#' for 1 and ' ' for 0
        }
        printf("\n");
        compute_next_state(current_state, next_state, N);
        memcpy(current_state, next_state, N);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken for %d steps: %f seconds\n", STEPS, cpu_time_used);

    return 0;
}
