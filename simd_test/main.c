#include <stdio.h>
#include "simd_neon.h"

int main() {
    float a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float b[] = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5};
    
    float result = dot_product(a, b, 8);
    
    printf("Dot product: %f\n", result);
    return 0;
}
