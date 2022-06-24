#ifndef TRIGGER_H_
#define TRIGGER_H_

#include <stdbool.h>
#include "Array.h"



typedef enum {HIGH, LOW, RISING_EDGE, FALLING_EDGE} trigger_t;

typedef struct {
    trigger_t trigger_type; // define the type of trigger
    int32_t threshold; // define the threshold
    int32_t delay; // delay before the effective trig and the returned result
    int32_t min_interval; // minimum interval between two trig
    unsigned int  time; // time measurement (in count numbers)
    bool count_time; // flag to start to count the time
    bool old_thresh; // used for rising and falling edge detection
    bool ready;
} trigger_i32_t;

void triggerI32(int32_t src, bool* result, trigger_i32_t* trigger);

void triggerArrayI32(array_i32_t* src, bool* result, trigger_i32_t* trigger);



typedef struct {
    trigger_t trigger_type; // define the type of trigger
    float32_t threshold; // define the threshold
    int32_t delay; // delay before the effective trig and the returned result
    int32_t min_interval; // minimum interval between two trig
    unsigned int  time; // time measurement (in count numbers)
    bool count_time; // flag to start to count the time
    bool old_thresh; // used for rising and falling edge detection
    bool ready;
} trigger_f32_t;

void triggerF32(float32_t src, bool* result, trigger_f32_t* trigger);

void triggerArrayF32(array_f32_t* src, bool* result, trigger_f32_t* trigger);


#endif
