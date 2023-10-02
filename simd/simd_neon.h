#ifndef SIMD_NEON_H
#define SIMD_NEON_H

#include <arm_neon.h>
#include <stddef.h> 

float dot_product(float* a, float* b, size_t n);

#endif
