
#ifndef FFT_H
#define FFT_H

#include "Array.h"

typedef const arm_cfft_instance_q31 fft_i32_t;

//void fftInitI32(fft_i32_t* fft);

void fftI32(fft_i32_t* fft, array_ci32_t* src);



typedef const arm_cfft_instance_f32 fft_f32_t;

//void fftInitF32(fft_f32_t* fft);

void fftF32_deprecated(fft_f32_t* fft, array_cf32_t* src);

void fftF32(array_f32_t* src, int length, char* window_name, array_f32_t* dst,
         fft_f32_t* fft, array_cf32_t* process, array_f32_t* window);

extern const float32_t __hanning_32_float_data[32];
extern const array_f32_t __hanning_32_float;
extern const float32_t __hanning_64_float_data[64];
extern const array_f32_t __hanning_64_float;
extern const float32_t __hanning_128_float_data[128];
extern const array_f32_t __hanning_128_float;
extern const float32_t __hanning_256_float_data[256];
extern const array_f32_t __hanning_256_float;
extern const float32_t __hanning_512_float_data[512];
extern const array_f32_t __hanning_512_float;
extern const float32_t __hanning_1024_float_data[1024];
extern const array_f32_t __hanning_1024_float;
extern const float32_t __hanning_2048_float_data[2048];
extern const array_f32_t __hanning_2048_float;
extern const float32_t __hanning_4096_float_data[4096];
extern const array_f32_t __hanning_4096_float;

#endif
