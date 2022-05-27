#include "Trigger.h"

void triggerI32(trigger_i32_t* trigger, int32_t src, bool* result) {

    //printf("trigger function\n");

    // Default result is false
    *result = false;

    // Check trigger state
    if (!trigger->count_time) {
        switch (trigger->trigger_type) {
            case HIGH:
                if (src > trigger->threshold) {
                    trigger->count_time = true;
                }
                break;
            case LOW:
                if (src < trigger->threshold) {
                    trigger->count_time = true;
                }
                break;
            case RISING_EDGE:
                if (src > trigger->threshold) {
                    //printf("%d > %d\n", src, trigger->threshold);
                    if (trigger->old_thresh == false) {
                        trigger->count_time = true;
                    }
                    trigger->old_thresh = true;
                } else {
                    trigger->old_thresh = false;
                }
                break;
            case FALLING_EDGE:
                if (src < trigger->threshold) {
                    if (trigger->old_thresh == false) {
                        trigger->count_time = true;
                    }
                    trigger->old_thresh = true;
                } else {
                    trigger->old_thresh = false;
                }
                break;
        }
    }

    // Pass one sample, then the trigger is ready
    if(!trigger->ready && trigger->count_time) {
        trigger->count_time = false;
    }
    trigger->ready = true;

    // If counter is active
    if ( trigger->count_time) {

        //printf("trigger count is active\n");

        // Set the result to true if the delay since the trigger is reached, else, result is false
        if (trigger->time == trigger->delay) {
            *result = true;
        } else {
            *result = false;
        }

        // Increment the time
        trigger->time++;

        // Disable the counter if the time since the last trigger is above the trigger delay plus the min_interval
        if ( trigger->time > trigger->delay + trigger->min_interval) {
            trigger->count_time = false;
            trigger->time = 0;
        }
    }

}

void triggerArrayI32(trigger_i32_t* trigger, array_i32_t* src, bool* result) {
    int i;
    bool temp_result = false;
    // Default final result is false
    bool final_result = false;

    for(i = 0; i < src->len; i++) {
        triggerI32(trigger, src->data[i], &temp_result);
        // If a trigger is detected one time in the array, return a true result
        if (temp_result == true) {
            final_result = true;
        }
    }
    *result = final_result;
}



void triggerF32(trigger_f32_t* trigger, float32_t src, bool* result) {

    // Default result is false
    *result = false;

    // Check trigger state
    if (!trigger->count_time) {
        switch (trigger->trigger_type) {
            case HIGH:
                if (src > trigger->threshold) {
                    trigger->count_time = true;
                }
                break;
            case LOW:
                if (src < trigger->threshold) {
                    trigger->count_time = true;
                }
                break;
            case RISING_EDGE:
                if (src > trigger->threshold) {
                    if (trigger->old_thresh == false) {
                        trigger->count_time = true;
                    }
                    trigger->old_thresh = true;
                } else {
                    trigger->old_thresh = false;
                }
                break;
            case FALLING_EDGE:
                if (src < trigger->threshold) {
                    if (trigger->old_thresh == false) {
                        trigger->count_time = true;
                    }
                    trigger->old_thresh = true;
                } else {
                    trigger->old_thresh = false;
                }
                break;
        }
    }

    // Pass one sample, then the trigger is ready
    if(!trigger->ready && trigger->count_time) {
        trigger->count_time = false;
    }
    trigger->ready = true;

    // If counter is active
    if (trigger->count_time && trigger->ready) {

        // Set the result to true if the delay since the trigger is reached
        if (trigger->time == trigger->delay) {
            *result = true;
        }

        // Increment the time
        trigger->time++;

        // Disable the counter if the time since the last trigger is above the trigger delay plus the min_interval
        if ( trigger->time > trigger->delay + trigger->min_interval) {
            trigger->count_time = false;
            trigger->time = 0;
        }
    }
}

void triggerArrayF32(trigger_f32_t* trigger, array_f32_t* src, bool* result) {
    int i;
    bool temp_result = false;
    // Default final result is false
    bool final_result = false;

    for(i = 0; i < src->len; i++) {
        triggerF32(trigger, src->data[i], &temp_result);
        // If a trigger is detected one time in the array, return a true result
        if (temp_result == true) {
            final_result = true;
        }
    }
    *result = final_result;
}

