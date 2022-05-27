#ifndef ARRAY_
#define ARRAY_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <arm_math.h>
#include "Complex.h"


void toFloatI32(int32_t a, float32_t* b);

void toIntF32(float32_t a, int32_t* b);


typedef struct {
    int32_t* data;
    int len;
    int32_t* defaultData;
    int defaultLen;
} array_i32_t;


typedef struct {
    float32_t* data;
    int len;
    float32_t* defaultData;
    int defaultLen;
} array_f32_t;


typedef struct {
    complex_i32_t* data;
    int len;
    complex_i32_t* defaultData;
    int defaultLen;
} array_ci32_t;


typedef struct {
    complex_f32_t* data;
    int len;
    complex_f32_t* defaultData;
    int defaultLen;
} array_cf32_t;




void putArrayI32(array_i32_t* array, int i, int32_t val);

void getArrayI32(array_i32_t* array, int i, int32_t* ret);

void copyArrayI32(array_i32_t* src, int i, array_i32_t* dst, int j, int len);

void toComplexArrayI32(array_i32_t* src, array_ci32_t* dst);

void toFloatArrayI32(array_i32_t* src, array_f32_t* dst);

void clearArrayI32(array_i32_t* array);



void putArrayF32(array_f32_t* array, int i, float32_t val);

void getArrayF32(array_f32_t* array, int i, float32_t* ret);

void copyArrayF32(array_f32_t* src, int i, array_f32_t* dst, int j, int len);

void toComplexArrayF32(array_f32_t* src, array_cf32_t* dst);

void toIntArrayF32(array_f32_t* src, array_i32_t* dst);

void clearArrayF32(array_f32_t* array);



void putArrayCI32(array_ci32_t* array, int i, complex_i32_t val);

void getArrayCI32(array_ci32_t* array, int i, complex_i32_t* ret);

void copyArrayCI32(array_ci32_t* src, int i, array_ci32_t* dst, int j, int len);

void clearArrayCI32(array_ci32_t* array);




void putArrayCF32(array_cf32_t* array, int i, complex_f32_t val);

void getArrayCF32(array_cf32_t* array, int i, complex_f32_t* ret);

void copyArrayCF32(array_cf32_t* src, int i, array_cf32_t* dst, int j, int len);

void clearArrayCF32(array_cf32_t* array);



#endif
