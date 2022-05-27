#include "Filter.h"
#include <arm_math.h>
#include "Serial.h"



void initIirI32(iir_i32_t* iir) {
    //arm_biquad_cascade_df1_init_q31 (iir, iir->numStages, iir->pCoeffs, iir->pState, iir->postShift);
}

void iirI32(iir_i32_t* iir, array_i32_t* in, array_i32_t* out) {
    //arm_biquad_cascade_df1_fast_q31 (iir, in->data, out->data, in->len);
    int i, j;
    int32_t x, y, t;
    int64_t tmp;

    // For each sample
    for (i=0; i < in->len; i++) {
        x = in->data[i];

        /* y0 = (a0*x0 + a1*x1 + ... + an*xn - y1*b1 - y2*b2 - ... - ym*bm)/b0 */
        pushCircularBufferI32(iir->numState, x);

        tmp = 0;
        for (j=0; j < iir->numLen; j++) {
            getFromEndCircularBufferI32(iir->numState, j, &t);
            tmp += (int64_t)t*(int64_t)iir->numCoeffs[j];
        }
        for (j=1; j < iir->denLen; j++) {
            getFromEndCircularBufferI32(iir->denState, j-1, &t);
            tmp -= (int64_t)t*(int64_t)iir->denCoeffs[j];
        }
        y = (int32_t)(tmp/iir->denCoeffs[0]);

        pushCircularBufferI32(iir->denState, y);
        out->data[i] = y;
    }
}

void initFirI32(fir_i32_t* fir) {
    arm_fir_init_q31 (fir->S, fir->S->numTaps, fir->S->pCoeffs, fir->S->pState, fir->blockSize);
}

void firI32(fir_i32_t* fir, array_i32_t* in, array_i32_t* out) {
    arm_fir_q31 (fir->S, in->data, out->data, fir->blockSize);
}



void initIirF32(iir_f32_t* iir) {
    //arm_biquad_cascade_df1_init_f32 (iir, iir->numStages, iir->pCoeffs, iir->pState);
}

void iirF32(iir_f32_t* iir, array_f32_t* in, array_f32_t* out) {
    //arm_biquad_cascade_df1_f32 (iir, in->data, out->data, in->len);
    int i, j;
    float32_t x, y, t;
    double tmp;

    // For each sample
    for (i=0; i < in->len; i++) {
        x = in->data[i];

        /* y0 = (a0*x0 + a1*x1 + ... + an*xn - y1*b1 - y2*b2 - ... - ym*bm)/b0 */
        pushCircularBufferF32(iir->numState, x);

        tmp = 0;
        for (j=0; j < iir->numLen; j++) {
            getFromEndCircularBufferF32(iir->numState, j, &t);
            tmp += t*iir->numCoeffs[j];
        }
        for (j=1; j < iir->denLen; j++) {
            getFromEndCircularBufferF32(iir->denState, j-1, &t);
            tmp -= t*iir->denCoeffs[j];
        }
        y = (float32_t) (tmp/iir->denCoeffs[0]);

        pushCircularBufferF32(iir->denState, y);
        out->data[i] = y;
    }
}

void initFirF32(fir_f32_t* fir) {
    arm_fir_init_f32 (fir->S, fir->S->numTaps, fir->S->pCoeffs, fir->S->pState, fir->blockSize);
}

void firF32(fir_f32_t* fir, array_f32_t* in, array_f32_t* out) {
    arm_fir_f32 (fir->S, in->data, out->data, fir->blockSize);
}

