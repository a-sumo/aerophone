#include "automaton_2d.h"
#include <arm_neon.h>

void compute_next_state(uint8_t** current_state, uint8_t** next_state, size_t width, size_t height) {
    for(size_t i = 1; i < height-1; i++) {
        for(size_t j = 1; j < width-1; j+=8) {  // Processing 8 cells at a time
            // Load 8 cells for each neighboring position
            uint8x8_t left = vld1_u8(&current_state[i][j-1]);
            uint8x8_t right = vld1_u8(&current_state[i][j+1]);
            uint8x8_t up = vld1_u8(&current_state[i-1][j]);
            uint8x8_t down = vld1_u8(&current_state[i+1][j]);
            uint8x8_t up_left = vld1_u8(&current_state[i-1][j-1]);
            uint8x8_t up_right = vld1_u8(&current_state[i-1][j+1]);
            uint8x8_t down_left = vld1_u8(&current_state[i+1][j-1]);
            uint8x8_t down_right = vld1_u8(&current_state[i+1][j+1]);
            uint8x8_t center = vld1_u8(&current_state[i][j]);

            // Convert uint8x8_t to uint16x8_t for sum accumulation
            uint16x8_t sum = vaddl_u8(center, left);
            sum = vaddw_u8(sum, right);
            sum = vaddw_u8(sum, up);
            sum = vaddw_u8(sum, down);
            sum = vaddw_u8(sum, up_left);
            sum = vaddw_u8(sum, up_right);
            sum = vaddw_u8(sum, down_left);
            sum = vaddw_u8(sum, down_right);

            // Divide the sum by 9 for averaging and store the result
            uint8x8_t avg = vshrn_n_u16(sum, 3);  // Approximate division by 9 using right shift by 3
            vst1_u8(&next_state[i][j], avg);
        }
    }
}

