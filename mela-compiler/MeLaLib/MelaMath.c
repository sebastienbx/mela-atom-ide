#include <arm_math.h>
#include <stdlib.h>
#include "MelaMath.h"
#include "Serial.h"



void absI32(int32_t x, int32_t* y){
    *y = abs(x);
}

void absF32(float32_t x, float32_t* y){
    *y = fabsf(x);
}

/*
void log10I32(int32_t x, int32_t* y) {
    *y = (int32_t)log10 (x);
}
 */

void log10F32(float32_t x, float32_t* y) {
    *y = log10 (x);
}


void powF32(float32_t x, float32_t p, float32_t* y){
    *y = pow(x, p);
}




void maxArrayI32(array_i32_t* in, int32_t* result, int32_t* index){
    arm_max_q31(in->data, in->len, result, (uint32_t*)index);
}

void sumArrayI32(array_i32_t* in, int32_t* result){
    int i = 0;
    *result = 0;
    for (i=0; i < in->len; i++) {
        *result += in->data[i];
    }
}

void meanArrayI32(array_i32_t* in, int32_t* result){
    arm_mean_q31(in->data, in->len, result);
}

void minArrayI32(array_i32_t* in, int32_t* result, int32_t* index){
    arm_min_q31(in->data, in->len, result, (uint32_t*)index);
}

void energyArrayI32(array_i32_t* in, float32_t* result){
    int64_t r;
    arm_power_q31(in->data, in->len, &r);
    *result = (float32_t)r;
}

void rmsArrayI32(array_i32_t* in, int32_t* result){
    arm_rms_q31(in->data, in->len, result);
}

void stdDevArrayI32(array_i32_t* in, int32_t* result){
    arm_std_q31(in->data, in->len, result);
}

void varArrayI32(array_i32_t* in, int32_t* result){
    arm_var_q31(in->data, in->len, result);
}

void absArrayI32(array_i32_t* in, array_i32_t* out){
    arm_abs_q31(in->data, out->data, in->len);
}

void addArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out){
    arm_add_q31(in1->data, in2->data, out->data, in1->len);
}

void subArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out){
    arm_sub_q31(in1->data, in2->data, out->data, in1->len);
}

void dotProductArrayI32(array_i32_t* in1, array_i32_t* in2, float32_t* result){
    int64_t r;
    arm_dot_prod_q31(in1->data, in2->data, in1->len, &r);
    *result = (float32_t)r;
}

void multArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out){
    arm_mult_q31(in1->data, in2->data, out->data, in1->len);
}

void multWithIntArrayI32(array_i32_t* in, int coeff, array_i32_t* out){
    int i;
    for (i = 0; i < in->len; i++) {
        out->data[i] = coeff*in->data[i];
    }
}

void divArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out){
    int i;
    for (i=0; i < in1->len; i++) {
        out->data[i] = in1->data[i] / in2->data[i];
    }
}

void divWithIntArrayI32(array_i32_t* in1, int32_t in2, array_i32_t* out){
    int i;
    for (i=0; i < in1->len; i++) {
        out->data[i] = in1->data[i] / in2;
    }
}

void negateArrayI32(array_i32_t* in, array_i32_t* out){
    arm_negate_q31(in->data, out->data, in->len);
}

void offsetArrayI32(array_i32_t* in, int32_t offset, array_i32_t* out){
    arm_offset_q31(in->data, offset, out->data, in->len);
}

void scaleArrayI32(array_i32_t* in, int32_t num, int32_t den, array_i32_t* out){
    int i;
    int64_t tmp;
    for (i = 0; i < in->len; i++) {
        tmp = (int64_t)num * in->data[i];
        out->data[i] = (int32_t)(tmp/den);
    }
}

void convArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out) {
    arm_conv_q31(in1->data, in1->len, in2->data, in2->len, out->data);
}

void corrArrayI32(array_i32_t* in1, array_i32_t* in2, array_i32_t* out) {
    arm_correlate_q31(in1->data, in1->len, in2->data, in2->len, out->data);
}

void sqrtArrayI32(array_i32_t* x, array_i32_t* y) {
    //arm_vsqrt_q31(in->data, out->data, in->len);
    int i;
    for (i=0; i<x->len; i++) {
        arm_sqrt_q31 (x->data[i], &x->data[i]);
    }
}

void cosArrayI32(array_i32_t* x, array_i32_t* y) {
    int i;
    for (i=0; i<x->len; i++) {
        y->data[i] = arm_cos_q31 (x->data[i]);
    }
}

void sinArrayI32(array_i32_t* x, array_i32_t* y) {
    int i;
    for (i=0; i<x->len; i++) {
        y->data[i] = arm_sin_q31 (x->data[i]);
    }
}

void log10ArrayI32(array_i32_t* x, array_i32_t* y) {
    int i;
    for (i=0; i<x->len; i++) {
        y->data[i] = (int32_t)log10 (x->data[i]);
    }
}

void diffArrayI32(array_i32_t* x, array_i32_t* y) {
    int i;
    for (i=1; i<x->len; i++) {
        x->data[i] = x->data[i] - x->data[i-1];
    }
    x->data[0] = x->data[1];
}











void maxArrayF32(array_f32_t* in, float32_t* result, int32_t* index){
    arm_max_f32(in->data, in->len, result, (uint32_t*)index);
}

void meanArrayF32(array_f32_t* in, float32_t* result){
    arm_mean_f32(in->data, in->len, result);
}

void sumArrayF32(array_f32_t* in, float32_t* result){
    int i = 0;
    *result = 0;
    for (i=0; i < in->len; i++) {
        *result += in->data[i];
    }
}

void minArrayF32(array_f32_t* in, float32_t* result, int32_t* index){
    arm_min_f32(in->data, in->len, result, (uint32_t*)index);
}

void energyArrayF32(array_f32_t* in, float32_t* result){
    arm_power_f32(in->data, in->len, result);
}

void rmsArrayF32(array_f32_t* in, float32_t* result){
    arm_rms_f32(in->data, in->len, result);
}

void stdDevArrayF32(array_f32_t* in, float32_t* result){
    arm_std_f32(in->data, in->len, result);
}

void varArrayF32(array_f32_t* in, float32_t* result){
    arm_var_f32(in->data, in->len, result);
}

void absArrayF32(array_f32_t* in, array_f32_t* out){
    arm_abs_f32(in->data, out->data, in->len);
}

void addArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out){
    arm_add_f32(in1->data, in2->data, out->data, in1->len);
}

void subArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out){
    arm_sub_f32(in1->data, in2->data, out->data, in1->len);
}

void dotProductArrayF32(array_f32_t* in1, array_f32_t* in2, float32_t* result){
    arm_dot_prod_f32(in1->data, in2->data, in1->len, result);
}

void multArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out){
    arm_mult_f32(in1->data, in2->data, out->data, in1->len);
}

void multWithFloatArrayF32(array_f32_t* in1, float32_t in2, array_f32_t* out){
    int i;
    for (i=0; i < in1->len; i++) {
        out->data[i] = in1->data[i] * in2;
    }
}

void divArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out){
    int i;
    for (i=0; i < in1->len; i++) {
        out->data[i] = in1->data[i] / in2->data[i];
    }
}

void divWithFloatArrayF32(array_f32_t* in1, float32_t in2, array_f32_t* out){
    int i;
    for (i=0; i < in1->len; i++) {
        out->data[i] = in1->data[i] / in2;
    }
}

void negateArrayF32(array_f32_t* in, array_f32_t* out){
    arm_negate_f32(in->data, out->data, in->len);
}

void offsetArrayF32(array_f32_t* in, float32_t offset, array_f32_t* out){
    arm_offset_f32(in->data, offset, out->data, in->len);
}

/*
void scaleArrayF32(array_f32_t* in, float32_t scale, array_f32_t* out){
    arm_scale_f32(in->data, scale, out->data, in->len);
}
 */

void convArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out) {
    arm_conv_f32(in1->data, in1->len, in2->data, in2->len, out->data);
}

void corrArrayF32(array_f32_t* in1, array_f32_t* in2, array_f32_t* out) {
    arm_correlate_f32(in1->data, in1->len, in2->data, in2->len, out->data);
}

void sqrtArrayF32(array_f32_t* x, array_f32_t* y) {
    //arm_vsqrt_f32(in->data, out->data, in->len);
    int i;
    for (i=0; i<x->len; i++) {
        arm_sqrt_f32 (x->data[i], &y->data[i]);
    }
}

void cosArrayF32(array_f32_t* x, array_f32_t* y) {
    int i;
    for (i=0; i<x->len; i++) {
        y->data[i] = arm_cos_f32 (x->data[i]);
    }
}

void sinArrayF32(array_f32_t* x, array_f32_t* y) {
    int i;
    for (i=0; i<x->len; i++) {
        y->data[i] = arm_sin_f32 (x->data[i]);
    }
}

void log10ArrayF32(array_f32_t* x, array_f32_t* y) {
    int i;
    for (i=0; i<x->len; i++) {
        y->data[i] = log10 (x->data[i]);
    }
}

void powArrayF32(array_f32_t* x, float32_t p, array_f32_t* y){
    int i;
    for (i=0; i<x->len; i++) {
        y->data[i] = pow(x->data[i], p);
    }
}

void diffArrayF32(array_f32_t* x, array_f32_t* y) {
    int i;
    for (i=0; i<x->len-1; i++) {
        y->data[i] = x->data[i+1] - x->data[i];
    }
    // i is incremented for the last test
    y->data[i] = y->data[i-1];
}






void conjugateArrayCI32(array_ci32_t* in, array_ci32_t* out){
    arm_cmplx_conj_q31((int32_t*)in->data, (int32_t*)out->data, in->len);
}

void magnitudeArrayCI32(array_ci32_t* in, array_i32_t* out){
    arm_cmplx_mag_q31 ((int32_t*)in->data, out->data, in->len);
}

void multcomplexArrayCI32(array_ci32_t* in1, array_ci32_t* in2, array_ci32_t* out){
    arm_cmplx_mult_cmplx_q31((int32_t*)in1->data, (int32_t*)in2->data, (int32_t*)out->data, in1->len);
}





void conjugateArrayCF32(array_cf32_t* in, array_cf32_t* out){
    arm_cmplx_conj_f32((float32_t*)in->data, (float32_t*)out->data, in->len);
}

void magnitudeArrayCF32(array_cf32_t* in, array_f32_t* out){
    arm_cmplx_mag_f32 ((float32_t*)in->data, out->data, in->len);
}

void multcomplexArrayCF32(array_cf32_t* in1, array_cf32_t* in2, array_cf32_t* out){
    arm_cmplx_mult_cmplx_f32((float32_t*)in1->data, (float32_t*)in2->data, (float32_t*)out->data, in1->len);
}





/*

# define WHALES_FFT_LEN 256

static float32_t Whales_f32_sensor_data[WHALES_FFT_LEN];
static float32_t Whales_fft_complex_result[WHALES_FFT_LEN];
static float32_t Whales_fft_mag_result[WHALES_FFT_LEN];

int32_t whalesCallFinder(array_int32_t* x_array) {
    //printf("whalesCallFinder\n");
    int32_t callFinded;
    int i = 0;

    // Check data size
    if (x_array->len != WHALES_FFT_LEN) {
        printf("ERROR: size must be equal to %d\n", WHALES_FFT_LEN);
        return false;
    }

    // Convert integer array to float for FFT
    for (i = 0; i< WHALES_FFT_LEN; i++) {
        Whales_f32_sensor_data[i] = (float32_t) getArrayInt32(x_array, i);
    }

    // Compute FFT
    arm_rfft_fast_instance_f32 fftInstance;
    arm_rfft_fast_init_f32(&fftInstance, WHALES_FFT_LEN);
    arm_rfft_fast_f32(&fftInstance, Whales_f32_sensor_data, Whales_fft_complex_result, 0);
    arm_cmplx_mag_squared_f32(Whales_fft_complex_result, Whales_fft_mag_result, WHALES_FFT_LEN/2);

    // A whales is detected if a threshold is reached at a frequency of 10Hz
    // in FFT results array: frequency = index*fs/2/64  (with fs/2 = max freq of FFT and 64 = nb of data in FFT)
    // index = frequency * 256 / fs
    // For whales we are searching a frequency of 10Hz, sampling frequency is 40Hz:
    // index = 10 * 256 / 40 = 64
    float32_t _10hz_amplitude = Whales_fft_mag_result[64]/1.e9;
#ifndef MANIP_FINAL
    printf("whales FFT amplitude %d\n", (int32_t)_10hz_amplitude);
#endif
    if (_10hz_amplitude > 10000.0) {
        callFinded = 1;
    } else {
        callFinded = 0;
    }
    return callFinded;
}


int _computeAverage(array_int32_t* x_array, int offset, int length) {
    if (offset + length > x_array->len) {
        printf("ERROR: Length from %d to %d > array length %d\n", offset, offset + length, x_array->len);
        return 0;
    }
    int64_t sum = 0;
    int i = 0;
    for (i = offset; i < offset + length; i++) {
        sum += (int64_t)getArrayInt32(x_array, i);
    }
    return (int)(sum/length);
}


int _computeVariance(array_int32_t* x_array, int offset, int length) {
    if (offset + length > x_array->len) {
        printf("ERROR: Length from %d to %d > array length %d\n", offset, offset + length, x_array->len);
        return 0;
    }

    int mean = _computeAverage(x_array, offset, length);
    if (mean == 0) {
        mean = 1;
    }
    //printf("mean %d\n", mean);

    int i;
    int64_t spl;
    int64_t sum = 0;
    for (i = offset; i < offset+length; i++) {
        spl = (int64_t) getArrayInt32(x_array, i);
        spl -= (int64_t)mean;
        if (spl < 0) {
            sum = sum - spl;
        } else {
            sum = sum + spl;
        }
    }
    //printf("var %d\n", (int)(sum/x_array->len));

    return (int)(sum/length);
}



#define TRIGGER_LEVEL 200

static int current_var = 0;
static int last_var = INT32_MAX;
static bool current_trigger = false;
static bool last_trigger = false;
static int max_trig = 0;

bool seisDetection(array_int32_t* x_array) {
    //printf("seisDetection\n");
    bool detection = false;

    // Compute the variance
    current_var = _computeVariance(x_array, 0, x_array->len);
    if (current_var == 0) {
        current_var = 1;
    }
    //printf("var %d\n", current_var);

    // Update trigger
    float ftrigger = 100.*((float)current_var/(float)last_var);
    int trigger = (int)ftrigger;

    if (trigger > TRIGGER_LEVEL) {
#ifndef MANIP_FINAL
        printf("trigger true: %d = %d / %d \n", trigger, current_var, last_var);
#endif
        current_trigger = true;
    } else {
#ifndef MANIP_FINAL
        printf("trigger false: %d = %d / %d\n", trigger, current_var, last_var);
#endif
        current_trigger = false;
    }

    // Detection is valid
    if (last_trigger == true && current_trigger == false) {
#ifndef MANIP_FINAL
        printf("Detection\n");
#endif
        detection = true;
    } else {
        detection = false;
    }

    // Update for next round
    last_trigger = current_trigger;
    if (current_trigger == false) {
        last_var = current_var;
    }

    // Security 10 triggers in a row
    if (current_trigger == true) {
        max_trig += 1;
        if (max_trig > 10) {
            last_var = current_var;
        }
    } else {
        max_trig = 0;
    }

    return detection;
}


#define SEISMIC_FFT_LEN 1024
static float32_t Seismic_f32_sensor_data[SEISMIC_FFT_LEN];
static float32_t Seismic_fft_complex_result[SEISMIC_FFT_LEN];
static float32_t Seismic_fft_mag_result[SEISMIC_FFT_LEN];

float32_t seisDiscrimination(array_int32_t* x_array) {
    printf("seisDiscrimination\n");
    int i = 0;

    // Find raising edge
    int offset = 0;
    bool raising_detected = false;
    int _last_var = 0;
    int _current_var;
    int _trigger = 0;
    while (!raising_detected && (x_array->len - offset - 40) > SEISMIC_FFT_LEN) {
        _current_var = _computeVariance (x_array, offset, 40);
        //printf("_current_var %d\n", _current_var);
        _trigger = _current_var/_last_var;
        //printf("trigger %d\n", _trigger);
        if (_trigger > TRIGGER_LEVEL) {
            raising_detected = true;
            // TODO? offset -= 40;
        } else {
            offset += 40;
        }
        _last_var = _current_var;
        //printf ("guard1 %d\n", (x_array->len - offset - 40));
        //printf ("guard2 %d\n", !raising_detected);
    }

    // Convert integer array to float for FFT

    //printf("compute from offset %d samples = %d seconds to offset %d samples = %d seconds\n",
    //        offset, offset/40, offset + FFT_LEN, (offset + FFT_LEN)/40);

    for (i = 0; i < SEISMIC_FFT_LEN; i++) {
        Seismic_f32_sensor_data[i] = (float32_t) getArrayInt32(x_array, i + offset);
    }

    //for (i = 0; i < FFT_LEN; i++) {
    //    printf("data0 %d\n", (int32_t)(Seismic_f32_sensor_data[i]));
    //}

    // Compute FFT
    arm_rfft_fast_instance_f32 fftInstance;
    arm_rfft_fast_init_f32(&fftInstance, SEISMIC_FFT_LEN);
    arm_rfft_fast_f32(&fftInstance, Seismic_f32_sensor_data, Seismic_fft_complex_result, 0);
    arm_cmplx_mag_squared_f32(Seismic_fft_complex_result, Seismic_fft_mag_result, SEISMIC_FFT_LEN/2); // 64 = 128/2

    // A strong seismic event if a threshold is reached at a frequency of 2Hz
    // A weak seismic event if a threshold is reached at a frequency of 1Hz
    // in FFT results array: frequency = index*fs/2/32  (with fs/2 = max freq of FFT and 32 = nb of data in FFT)
    // index = frequency * 128 / fs
    // For strong seismic event, we are searching a frequency of 2Hz, sampling frequency is 40Hz:
    // index = 2 * 1024 / 40 = 51.2
    // For weak seismic event, we are searching a frequency of 1Hz, sampling frequency is 40Hz:
    // index = 1 * 128 / 40 = 25.6
    float32_t _2hz_amplitude = (Seismic_fft_mag_result[51] + Seismic_fft_mag_result[52])/2;
    _2hz_amplitude = _2hz_amplitude/1.e12;
    float32_t _1hz_amplitude = (Seismic_fft_mag_result[25] + Seismic_fft_mag_result[26])/2;
    _1hz_amplitude = _1hz_amplitude/1.e12;
    //int _2hz_amplitude = (int)(1000*Seismic_fft_mag_result[6]) + (int)(1000*Seismic_fft_mag_result[7]);
    //int _1hz_amplitude = (int)(1000*Seismic_fft_mag_result[3]) + (int)(1000*Seismic_fft_mag_result[4]);
#ifndef MANIP_FINAL
    printf("_2hz_amplitude %d\n", (int32_t)(_2hz_amplitude));
    printf("_1hz_amplitude %d\n", (int32_t)(_1hz_amplitude));
#endif
    //for (i = 0; i < FFT_LEN/2; i++) {
    //    printf("mfft %d\n", (int32_t)(Seismic_fft_mag_result[i]/1.e12));
    //}

    float32_t criterion = 0.1;
    if (_2hz_amplitude > 10000.0) {
        criterion = 0.9;
    } else if (_1hz_amplitude > 10000.0) {
        criterion = 0.5;
    }
    return criterion;
}

 */
