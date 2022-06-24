#include "StaLta.h"
#include <stdio.h>


void initStaltaI32(stalta_i32_t* stalta) {
    stalta->stasum = 0;
    stalta->ltasum = 0;
    initCircularBufferI32(stalta->cbuff);
}


void staltaI32(int32_t src, int32_t* dst, stalta_i32_t* stalta){
    int32_t val;
    int64_t sta_mean_tmp;
    int64_t lta_mean_tmp;

    // Amount of samples in the STA/LTA buffer
    int amountFilled = amountFilledCircularBufferI32(stalta->cbuff);

    // Substract old values (initial values are equals to 0)
    getFromEndCircularBufferI32(stalta->cbuff, stalta->stalen - 1, &val);
    stalta->stasum -= (int64_t)val;
    //printf("sta sub %d\n", val);
    getFromEndCircularBufferI32(stalta->cbuff, stalta->ltaoffset + stalta->ltalen - 1, &val);
    stalta->ltasum -= (int64_t)val;

    // Add values to the circular buffer
    pushCircularBufferI32(stalta->cbuff, src);
    amountFilled++;
    //printf("push %d\n", src->data[i]);

    // Add new values to the sums
    getFromEndCircularBufferI32(stalta->cbuff, 0, &val);
    stalta->stasum += (int64_t)val;
    //printf("sta add %d\n", val);
    getFromEndCircularBufferI32(stalta->cbuff, stalta->ltaoffset, &val);
    stalta->ltasum += (int64_t)val;

    sta_mean_tmp = (stalta->scale*stalta->stasum)/stalta->stalen;
    lta_mean_tmp = stalta->ltasum/stalta->ltalen;
    //printf("sta mean %d\n", sta_mean_tmp);

    if (amountFilled < stalta->ltalen + stalta->ltaoffset) {
        *dst = 1;
    } else if (lta_mean_tmp != 0) {
        //printf("stalta mean %d\n", (int32_t)(sta_mean_tmp / lta_mean_tmp));
        *dst = (int32_t)(sta_mean_tmp / lta_mean_tmp);
    } else if (sta_mean_tmp == 0) {
        *dst = 0;
    } else if ( (lta_mean_tmp > 0 && sta_mean_tmp > 0) || (lta_mean_tmp < 0 && sta_mean_tmp < 0) ) {
        *dst = INT32_MIN;
    } else {
        *dst = INT32_MAX;
    }
}

void staltaArrayI32(array_i32_t* src, array_i32_t* dst, stalta_i32_t* stalta){
    int i;
    for(i = 0; i < src->len; i++) {
        staltaI32(src->data[i], &(dst->data[i]), stalta);
    }
}




void initStaltaF32(stalta_f32_t* stalta) {
    stalta->stasum = 0;
    stalta->ltasum = 0;
    initCircularBufferF32(stalta->cbuff);
}

void staltaF32(float32_t src, float32_t* dst, stalta_f32_t* stalta){
    float32_t val;

    // Amount of samples in the STA/LTA buffer
    int amountFilled = amountFilledCircularBufferF32(stalta->cbuff);

    // Substract old values (initial values are equals to 0)
    getFromEndCircularBufferF32(stalta->cbuff, stalta->stalen - 1, &val);
    stalta->stasum -= val;
    //printf("sta sub %d\n", val);
    getFromEndCircularBufferF32(stalta->cbuff, stalta->ltaoffset + stalta->ltalen - 1, &val);
    stalta->ltasum -= val;

    // Add values to the circular buffer
    pushCircularBufferF32(stalta->cbuff, src);
    //printf("push %d\n", src->data[i]);

    // Add new values to the sums
    getFromEndCircularBufferF32(stalta->cbuff, 0, &val);
    stalta->stasum += val;
    //printf("sta add %d\n", val);
    getFromEndCircularBufferF32(stalta->cbuff, stalta->ltaoffset, &val);
    stalta->ltasum += val;

    if (amountFilled < stalta->ltalen + stalta->ltaoffset) {
        *dst = 1;
    } else {
        *dst = (stalta->stasum/(float32_t)stalta->stalen)/(stalta->ltasum/(float32_t)stalta->ltalen);
    }
}

void staltaArrayF32(array_f32_t* src, array_f32_t* dst, stalta_f32_t* stalta){
    int i;
    for(i = 0; i < src->len; i++) {
        staltaF32(src->data[i], &(dst->data[i]), stalta);
    }
}

