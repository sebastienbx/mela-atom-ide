
#ifndef CDF24_H
#define CDF24_H

#include "Array.h"

typedef struct {
    int K;
    int edges_correction;
    int normalized;
    int len;
    int32_t* a;
    int32_t* d;
} cdf24_i32_t;

void cdf24I32(array_i32_t* x, cdf24_i32_t* cdf24);

int cdf24ScalesPowerI32 (array_i32_t* x, size_t n0, size_t n1, array_i32_t* scales_pow, cdf24_i32_t* cdf24);


typedef struct {
    int K;
    int edges_correction;
    int normalized;
    int len;
    float32_t* a;
    float32_t* d;
} cdf24_f32_t;

void cdf24F32(array_f32_t* x, cdf24_f32_t* cdf24);

int cdf24ScalesPowerF32 (array_f32_t* x, size_t n0, size_t n1, array_f32_t* scales_pow, cdf24_f32_t* cdf24);

#endif
