#include "Buffer.h"
#include "Serial.h"



void pushBufferInt32(buffer_i32_t* buffer, int32_t val) {
    if (!buffer->isFull) {
        buffer->i += 1;
        if (buffer->i == buffer->array->len) {
            buffer->isFull = true;
        }
        buffer->array->data[buffer->i] = val;
    }
}

void popBufferInt32(buffer_i32_t* buffer) {
    if (buffer->i > 0) {
        buffer->i -= 1;
    }
    buffer->isFull = false;
}

bool isFullBufferInt32(buffer_i32_t* buffer) {
    return buffer->isFull;
}

void clearBufferInt32(buffer_i32_t* buffer) {
    buffer->i = 0;
    buffer->isFull = false;
}



void pushBufferF32(buffer_f32_t* buffer, float32_t val) {
    if (!buffer->isFull) {
        buffer->i += 1;
        if (buffer->i == buffer->array->len) {
            buffer->isFull = true;
        }
        buffer->array->data[buffer->i] = val;
    }
}

void popBufferF32(buffer_f32_t* buffer) {
    if (buffer->i > 0) {
        buffer->i -= 1;
    }
    buffer->isFull = false;
}

bool isFullBufferF32(buffer_f32_t* buffer) {
    return buffer->isFull;
}

void clearBufferF32(buffer_f32_t* buffer) {
    buffer->i = 0;
    buffer->isFull = false;
}

