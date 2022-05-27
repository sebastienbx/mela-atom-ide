
#ifndef MATH_H
#define MATH_H

#include "Array.h"



void absI32(int32_t x, int32_t* y);

void absF32(float32_t x, float32_t* y);

//void log10I32(int32_t x, int32_t* y);

void log10F32(float32_t x, float32_t* y);

void powF32(float32_t x, float32_t p, float32_t* y);




void maxArrayI32(array_i32_t* in, int32_t* result, int32_t* index);

void sumArrayI32(array_i32_t* in, int32_t* result);

void meanArrayI32(array_i32_t* in, int32_t* result);

void minArrayI32(array_i32_t* in, int32_t* result, int32_t* index);

void energyArrayI32(array_i32_t* in, float32_t* result);

void rmsArrayI32(array_i32_t* in, int32_t* result);

void stdDevArrayI32(array_i32_t* in, int32_t* result);

void varArrayI32(array_i32_t* in, int32_t* result);

void absArrayI32(array_i32_t* in, array_i32_t* out);

void addArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out);

void subArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out);

void dotProductArrayI32(array_i32_t* in1, array_i32_t* in2, float32_t* result);

void multArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out);

void multWithIntArrayI32(array_i32_t* in, int coeff, array_i32_t* out);

void divArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out);

void divWithIntArrayI32(array_i32_t* in1, int32_t in2, array_i32_t* out);

void negateArrayI32(array_i32_t* in, array_i32_t* out);

void offsetArrayI32(array_i32_t* in, int32_t offset, array_i32_t* out);

void scaleArrayI32(array_i32_t* in, int32_t num, int32_t den, array_i32_t* out);

void convArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out);

void corrArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out);

void sqrtArrayI32(array_i32_t* x, array_i32_t* y);

void cosArrayI32(array_i32_t* x, array_i32_t* y);

void sinArrayI32(array_i32_t* x, array_i32_t* y);

//void log10ArrayI32(array_i32_t* x, array_i32_t* y);

void diffArrayI32(array_i32_t* x, array_i32_t* y);






void maxArrayF32(array_f32_t* in, float32_t* result, int32_t* index);

void sumArrayF32(array_f32_t* in, float32_t* result);

void meanArrayF32(array_f32_t* in, float32_t* result);

void minArrayF32(array_f32_t* in, float32_t* result, int32_t* index);

void energyArrayF32(array_f32_t* in, float32_t* result);

void rmsArrayF32(array_f32_t* in, float32_t* result);

void stdDevArrayF32(array_f32_t* in, float32_t* result);

void varArrayF32(array_f32_t* in, float32_t* result);

void absArrayF32(array_f32_t* in, array_f32_t* out);

void addArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out);

void subArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out);

void dotProductArrayF32(array_f32_t* in1, array_f32_t* in2, float32_t* result);

void multArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out);

void multWithFloatArrayF32(array_f32_t* in1, float32_t in2, array_f32_t* out);

void divArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out);

void divWithFloatArrayF32(array_f32_t* in1, float32_t in2, array_f32_t* out);

void negateArrayF32(array_f32_t* in, array_f32_t* out);

void offsetArrayF32(array_f32_t* in, float32_t offset, array_f32_t* out);

//void scaleArrayF32(array_f32_t* in, float32_t scale, array_f32_t* out);

void convArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out);

void corrArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out);

void sqrtArrayF32(array_f32_t* x, array_f32_t* y);

void cosArrayF32(array_f32_t* x, array_f32_t* y);

void sinArrayF32(array_f32_t* x, array_f32_t* y);

void log10ArrayF32(array_f32_t* x, array_f32_t* y);

void powArrayF32(array_f32_t* x, float32_t p, array_f32_t* y);

void diffArrayF32(array_f32_t* x, array_f32_t* y);






void conjugateArrayCI32(array_ci32_t* in, array_ci32_t* out);

void magnitudeArrayCI32(array_ci32_t* in, array_i32_t* out);

void multcomplexArrayCI32(array_ci32_t* in1, array_ci32_t* in2, array_ci32_t* out);




void conjugateArrayCF32(array_cf32_t* in, array_cf32_t* out);

void magnitudeArrayCF32(array_cf32_t* in, array_f32_t* out);

void multcomplexArrayCF32(array_cf32_t* in1, array_cf32_t* in2, array_cf32_t* out);



#endif
