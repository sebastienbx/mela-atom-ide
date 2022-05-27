#include "Array.h"



void toFloatI32(int32_t a, float32_t* b) {
    *b = (float)a;
}

void toIntF32(float32_t a, int32_t* b) {
    *b = (float)a;
}

/***
 * Integer 32 bits array
 ***/

void putArrayI32(array_i32_t* array, int i, int32_t val){
    array->data[i] = val;
}

void getArrayI32(array_i32_t* array, int i, int32_t* ret){
    *ret = array->data[i];
}

void copyArrayI32(array_i32_t* src, int i, array_i32_t* dst, int j, int len){
    arm_copy_q31 (src->data + i, dst->data + j, len);
}

void toComplexArrayI32(array_i32_t* src, array_ci32_t* dst){
    int i;
    for(i=0; i < src->len; i++){
        dst->data[i].real = src->data[i];
        dst->data[i].img = 0;
    }
}

void toFloatArrayI32(array_i32_t* src, array_f32_t* dst) {
    //arm_q31_to_float(src->data, dst->data, src->len);
    int i;
    for(i=0; i < src->len; i++){
        dst->data[i] = (float)src->data[i];
    }
}

void clearArrayI32(array_i32_t* array){
    int i;
    for(i=0; i < array->defaultLen; i++){
        array->defaultData[i] = 0;
    }
}



/***
 * Float 32 bits array
 ***/

void putArrayF32(array_f32_t* array, int i, float32_t val){
    array->data[i] = val;
}

void getArrayF32(array_f32_t* array, int i, float32_t* ret){
    *ret = array->data[i];
}

void copyArrayF32(array_f32_t* src, int i, array_f32_t* dst, int j, int len){
    arm_copy_f32 (src->data + i, dst->data + j, len);
}

void toComplexArrayF32(array_f32_t* src, array_cf32_t* dst){
    int i;
    for(i=0; i < src->len; i++){
        dst->data[i].real = src->data[i];
        dst->data[i].img = 0;
    }
}

void toIntArrayF32(array_f32_t* src, array_i32_t* dst){
    //arm_float_to_q31(src->data, dst->data, src->len);
    int i;
    for(i=0; i < src->len; i++){
        dst->data[i] = (int32_t)src->data[i];
    }
}

void clearArrayF32(array_f32_t* array){
    int i;
    for(i=0; i < array->defaultLen; i++){
        array->defaultData[i] = 0;
    }
}



/***
 * Complex integer 32 bits array
 ***/

void putArrayCI32(array_ci32_t* array, int i, complex_i32_t val){
    array->data[i].real = val.real;
    array->data[i].img = val.img;
}

void getArrayCI32(array_ci32_t* array, int i, complex_i32_t* ret){
    ret->real = array->data[i].real;
    ret->img = array->data[i].img;
}

void copyArrayCI32(array_ci32_t* src, int i, array_ci32_t* dst, int j, int len){
    arm_copy_q31 ((int32_t*)src->data + (i*2), (int32_t*)dst->data + (j*2), len*2);
}

void clearArrayCI32(array_ci32_t* array){
    int i;
    for(i=0; i < array->defaultLen; i++){
        array->defaultData[i].img = 0;
        array->defaultData[i].real = 0;
    }
}



/***
 * Complex float 32 bits array
 ***/

void putArrayCF32(array_cf32_t* array, int i, complex_f32_t val){
    array->data[i].real = val.real;
    array->data[i].img = val.img;
}

void getArrayCF32(array_cf32_t* array, int i, complex_f32_t* ret){
    ret->real = array->data[i].real;
    ret->img = array->data[i].img;
}

void copyArrayCF32(array_cf32_t* src, int i, array_cf32_t* dst, int j, int len){
    arm_copy_f32 ((float32_t*)src->data + (i*2), (float32_t*)dst->data + (j*2), len*2);
}

void clearArrayCF32(array_cf32_t* array){
    int i;
    for(i=0; i < array->defaultLen; i++){
        array->defaultData[i].img = 0;
        array->defaultData[i].real = 0;
    }
}
