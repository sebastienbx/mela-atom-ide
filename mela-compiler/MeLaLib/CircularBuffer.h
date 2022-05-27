#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "Array.h"



typedef struct {
    int32_t* data; // array to store the data
    int len;   // length of the buffer
    int beg;   // beginning of the circular buffer
    int end;   // end of the circular buffer
    bool isEmpty;
} circular_buffer_i32_t;

void getFromBegCircularBufferI32(circular_buffer_i32_t* buff, int index, int32_t* val);

void getFromEndCircularBufferI32(circular_buffer_i32_t* buff, int index, int32_t* val);

void pushCircularBufferI32(circular_buffer_i32_t* buff, int32_t val);

void pushArrayCircularBufferI32(circular_buffer_i32_t* buff, array_i32_t* array);

int toArrayCircularBufferI32(circular_buffer_i32_t* buff, array_i32_t* dst);

int amountFilledCircularBufferI32(circular_buffer_i32_t* buff);

bool isFullCircularBufferI32(circular_buffer_i32_t* buff);

void initCircularBufferI32(circular_buffer_i32_t* buff);

#define clearCircularBufferI32(x) initCircularBufferI32(x)


typedef struct {
    float32_t* data; // array to store the data
    int len;   // length of the buffer
    int beg;   // beginning of the circular buffer
    int end;   // end of the circular buffer
    bool isEmpty;
} circular_buffer_f32_t;

void getFromBegCircularBufferF32(circular_buffer_f32_t* buff, int index, float32_t* val);

void getFromEndCircularBufferF32(circular_buffer_f32_t* buff, int index, float32_t* val);

void pushCircularBufferF32(circular_buffer_f32_t* buff, float32_t val);

void pushArrayCircularBufferF32(circular_buffer_f32_t* buff, array_f32_t* array);

int amountFilledCircularBufferF32(circular_buffer_f32_t* buff);

int toArrayCircularBufferF32(circular_buffer_f32_t* buff, array_f32_t* dst);

bool isFullCircularBufferF32(circular_buffer_f32_t* buff);

void initCircularBufferF32(circular_buffer_f32_t* buff);

#define clearCircularBufferF32(x) initCircularBufferF32(x)

#endif
