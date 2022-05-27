#ifndef PROBABILITY_
#define PROBABILITY_

#include "Array.h"


typedef struct {
    int32_t* data;
    int32_t* proba;
    int len;
} distribution_i32_t;

void cumulativeDistributionFunctionI32(distribution_i32_t* distribution, int32_t ref, int32_t* result);


typedef struct {
    float32_t* data;
    float32_t* proba;
    int len;
} distribution_f32_t;

void cumulativeDistributionFunctionF32(distribution_f32_t* distribution, float32_t ref, float32_t* result);



#endif
