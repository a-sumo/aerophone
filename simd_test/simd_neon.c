#include "simd_neon.h"

float dot_product(float* a, float* b, size_t n) {
    float32x4_t sum_vec = vdupq_n_f32(0);
    
    for(size_t i = 0; i < n; i += 4) {
        float32x4_t a_vec = vld1q_f32(&a[i]);
        float32x4_t b_vec = vld1q_f32(&b[i]);
        
        sum_vec = vmlaq_f32(sum_vec, a_vec, b_vec);
    }
    
    float sum_array[4];
    vst1q_f32(sum_array, sum_vec);
    
    return sum_array[0] + sum_array[1] + sum_array[2] + sum_array[3];
}
