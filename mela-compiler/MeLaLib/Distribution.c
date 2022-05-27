#include "Distribution.h"


// Cumulative distribution function

void cumulativeDistributionFunctionI32(distribution_i32_t* distribution, int32_t ref, int32_t* result) {
    int i = 0;
    *result = 0;
    while (distribution->data[i] <= ref && i < distribution->len) {
        *result += distribution->proba[i];
        i++;
    }
}

void cumulativeDistributionFunctionF32(distribution_f32_t* distribution, float32_t ref, float32_t* result) {
    int i = 0;
    *result = 0;
    while (distribution->data[i] <= ref && i < distribution->len) {
        *result += distribution->proba[i];
        i++;
    }
}
