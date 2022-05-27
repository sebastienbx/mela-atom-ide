
#ifndef Filter_H
#define Filter_H

#include "Array.h"
#include "CircularBuffer.h"


//typedef arm_biquad_casd_df1_inst_q31 iir_i32_t;

typedef struct {
    int32_t* numCoeffs;
    int32_t* denCoeffs;
    circular_buffer_i32_t* numState;
    circular_buffer_i32_t* denState;
    int numLen;
    int denLen;
} iir_i32_t;

void initIirI32(iir_i32_t* iir);

void iirI32(iir_i32_t* iir, array_i32_t* in, array_i32_t* out);


typedef struct {
    arm_fir_instance_q31* S;
    int blockSize;
} fir_i32_t;

void initFirI32(fir_i32_t* fir);

void firI32(fir_i32_t* fir, array_i32_t* in, array_i32_t* out);




//typedef arm_biquad_casd_df1_inst_f32 iir_f32_t;

typedef struct {
    float32_t* numCoeffs;
    float32_t* denCoeffs;
    circular_buffer_f32_t* numState;
    circular_buffer_f32_t* denState;
    int numLen;
    int denLen;
} iir_f32_t;

void initIirF32(iir_f32_t* iir);

void iirF32(iir_f32_t* iir, array_f32_t* in, array_f32_t* out);


typedef struct {
    arm_fir_instance_f32* S;
    int blockSize;
} fir_f32_t;

void initFirF32(fir_f32_t* fir);

void firF32(fir_f32_t* fir, array_f32_t* in, array_f32_t* out);


#endif
