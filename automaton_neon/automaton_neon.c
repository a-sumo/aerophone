#include "automaton_neon.h"
#include <arm_neon.h>

void compute_next_state(uint8_t* current_state, uint8_t* next_state, size_t n) {
    for(size_t i = 1; i < n - 1; i += 16) {
        uint8x16_t left = vld1q_u8(&current_state[i-1]);
        uint8x16_t center = vld1q_u8(&current_state[i]);
        uint8x16_t right = vld1q_u8(&current_state[i+1]);

        // Rule 30: XOR between left, center and right
        uint8x16_t result = veorq_u8(left, veorq_u8(center, right));
        
        vst1q_u8(&next_state[i], result);
    }
}
