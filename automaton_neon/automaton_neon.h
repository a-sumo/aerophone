#ifndef AUTOMATON_NEON_H
#define AUTOMATON_NEON_H

#include <stddef.h>
#include <stdint.h>

void compute_next_state(uint8_t* current_state, uint8_t* next_state, size_t n);

#endif
