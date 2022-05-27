#ifndef STALTA_H_
#define STALTA_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "CircularBuffer.h"

typedef struct {
    circular_buffer_i32_t* cbuff;     // array to store the data
    int stalen;                       // length of the short term average
    int ltalen;                       // length of the long term average
    int ltaoffset;                    // beginning of the long term average
    int64_t scale;                    // scale factor
    int64_t stasum;                   // sum of data
    int64_t ltasum;                   // sum of data
} stalta_i32_t;

void initStaltaI32(stalta_i32_t* stalta);

void staltaI32(stalta_i32_t* stalta, int32_t src, int32_t* dst);

void staltaArrayI32(stalta_i32_t* stalta, array_i32_t* src, array_i32_t* dst);



typedef struct {
    circular_buffer_f32_t* cbuff;     // array to store the data
    int stalen;                       // length of the short term average
    int ltalen;                       // length of the long term average
    int ltaoffset;                    // beginning of the long term average
    float32_t stasum;                 // sum of data
    float32_t ltasum;                 // sum of data
} stalta_f32_t;

void initStaltaF32(stalta_f32_t* stalta);

void staltaF32(stalta_f32_t* stalta, float32_t src, float32_t* dst);

void staltaArrayF32(stalta_f32_t* stalta, array_f32_t* src, array_f32_t* dst);



#endif
