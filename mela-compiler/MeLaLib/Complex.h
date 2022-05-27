#ifndef COMPLEX_TYPES_H_
#define COMPLEX_TYPES_H_

#include <stdint.h>
#include <stddef.h>
#include <arm_math.h>


typedef struct {
    int32_t real;
    int32_t img;
} complex_i32_t;


typedef struct {
    float32_t real;
    float32_t img;
} complex_f32_t;


#endif
