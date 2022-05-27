#ifndef BUFFER_
#define BUFFER_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "Array.h"


typedef struct {
    array_i32_t* array;
    int i;
    bool isFull;
} buffer_i32_t;

void pushBufferInt32(buffer_i32_t* buffer, int32_t val);

void popBufferInt32(buffer_i32_t* buffer);

bool isFullBufferInt32(buffer_i32_t* buffer);

void clearBufferInt32(buffer_i32_t* buffer);


typedef struct {
    array_f32_t* array;
    int i;
    bool isFull;
} buffer_f32_t;

void pushBufferF32(buffer_f32_t* buffer, float32_t val);

void popBufferF32(buffer_f32_t* buffer);

bool isFullBufferF32(buffer_f32_t* buffer);

void clearBufferF32(buffer_f32_t* buffer);

#endif
