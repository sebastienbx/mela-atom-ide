#include "CircularBuffer.h"
#include "StaLta.h"
#include <arm_math.h>
#include <stdio.h>



void _increaseBuffSizeI32(circular_buffer_i32_t* buff) {
    // if buffer is empty, do not increment index,
    // the buffer will contains only one value, with equals begin and end index
    if (buff->isEmpty) {
        buff->isEmpty = false;
        return;
    }

    // increase end index
    buff->end += 1;
    if (buff->end == buff->len) {
        buff->end = 0;
    }

    // increase begin index
    if (buff->end == buff->beg) {
        buff->beg += 1;
        if (buff->beg == buff->len) {
            buff->beg = 0;
        }
    }
}

void getFromBegCircularBufferI32(circular_buffer_i32_t* buff, int index, int32_t* val) {
    int buffindex;
    buffindex = (buff->beg + index) % buff->len;
    *val = buff->data[buffindex];
}

void getFromEndCircularBufferI32(circular_buffer_i32_t* buff, int index, int32_t* val) {
    int buffindex;
    buffindex = (buff->end - index + buff->len) % buff->len;
    //printf("end %d index %d len %d\n", buff->end, index, buff->len);
    //printf("index %d buffindex %d val %d\n", index, buffindex, buff->data[buffindex]);
    *val = buff->data[buffindex];
}

void pushCircularBufferI32(circular_buffer_i32_t* buff, int32_t val){
    //printf("index %d val %d\n", buff->end, val);
    _increaseBuffSizeI32(buff);
    buff->data[buff->end] = val;
}

void pushArrayCircularBufferI32(circular_buffer_i32_t* buff, array_i32_t* src){
    int i;
    for (i = 0; i < src->len; i++) {
        pushCircularBufferI32(buff, src->data[i]);
    }
}

int toArrayCircularBufferI32(circular_buffer_i32_t* buff, array_i32_t* dst){
    // TODO: define a parameter "index" and "length" and rename to getArrayCircularBufferI32
    // TODO: or copy from the end of the circular buffer until to reach the beg of the circular buffer or the end of dest array
    if (buff->len > dst->len) {
        return -1;
    }

    int i;
    int j = 0;
    for (i = buff->beg; i < buff->len; i++) {
        putArrayI32(dst, j, buff->data[i]);
        j ++;
    }
    for (i = 0; i <= buff->end; i++) {
        putArrayI32(dst, j, buff->data[i]);
        j ++;
    }

    return 0;
}

int amountFilledCircularBufferI32(circular_buffer_i32_t* buff) {
    return (buff->end - buff->beg + buff->len) % buff->len + 1;
}

bool isFullCircularBufferI32(circular_buffer_i32_t* buff) {
    if ((buff->end + 1)%buff->len == buff->beg) {
        return true;
    } else {
        return false;
    }
}

void initCircularBufferI32(circular_buffer_i32_t* buff) {
    int i;
    for(i = 0; i < buff->len; i++) {
        buff->data[i] = 0;
    }
    buff->isEmpty = true;
    buff->end = 0;
    buff->beg = 0;
}







void _increaseBuffSizeF32(circular_buffer_f32_t* buff) {
    // if buffer is empty, do not increment index,
    // the buffer will contains only one value, with equals begin and end index
    if (buff->isEmpty) {
        buff->isEmpty = false;
        return;
    }

    // increase end index
    buff->end += 1;
    if (buff->end == buff->len) {
        buff->end = 0;
    }

    // increase begin index
    if (buff->end == buff->beg) {
        buff->beg += 1;
        if (buff->beg == buff->len) {
            buff->beg = 0;
        }
    }
}

void getFromBegCircularBufferF32(circular_buffer_f32_t* buff, int index, float32_t* val) {
    int buffindex;
    buffindex = (buff->beg + index) % buff->len;
    *val = buff->data[buffindex];
}

void getFromEndCircularBufferF32(circular_buffer_f32_t* buff, int index, float32_t* val) {
    int buffindex;
    buffindex = (buff->end - index + buff->len) % buff->len;
    *val = buff->data[buffindex];
}

void pushCircularBufferF32(circular_buffer_f32_t* buff, float32_t val){
    _increaseBuffSizeF32(buff);
    buff->data[buff->end] = val;
}

void pushArrayCircularBufferF32(circular_buffer_f32_t* buff, array_f32_t* src){
    int i;
    for (i = 0; i < src->len; i++) {
        pushCircularBufferF32(buff, src->data[i]);
    }
}

int toArrayCircularBufferF32(circular_buffer_f32_t* buff, array_f32_t* dst){
    if (buff->len > dst->len) {
        return -1;
    }

    int i;
    int j = 0;

    if (buff->beg <= buff->end) {
        for (i = buff->beg; i <= buff->end; i++) {
            putArrayF32(dst, j, buff->data[i]);
            j ++;
        }
    } else {
        for (i = buff->beg; i < buff->len; i++) {
            putArrayF32(dst, j, buff->data[i]);
            j ++;
        }
        for (i = 0; i <= buff->end; i++) {
            putArrayF32(dst, j, buff->data[i]);
            j ++;
        }
    }

    return 0;
}

int amountFilledCircularBufferF32(circular_buffer_f32_t* buff) {
    return (buff->end - buff->beg + buff->len) % buff->len + 1;
}

bool isFullCircularBufferF32(circular_buffer_f32_t* buff) {
    if ((buff->end + 1)%buff->len == buff->beg) {
        return true;
    } else {
        return false;
    }
}

void initCircularBufferF32(circular_buffer_f32_t* buff) {
    int i;
    for(i = 0; i < buff->len; i++) {
        buff->data[i] = 0;
    }
    buff->isEmpty = true;
    buff->end = 0;
    buff->beg = 0;
}
