#ifndef RECORD_H_
#define RECORD_H_


#include <stdint.h>
#include <stdbool.h>
#include "Array.h"
#include "CircularBuffer.h"


#include <stdio.h>


// File buffer: 256 ko
#define SD_BUFF_SZ 262144

// Buffer structure
typedef struct {
    char* data;
    unsigned int offset;
} buffer_t;

// File structure
typedef struct {
    char* fname;

    FILE* fil;
    buffer_t* buff;
} buffered_file_t;


union toChar {
    char    c[4];
    int32_t i;
    float32_t f;
};

void openFile(buffered_file_t* file);

void closeFile(buffered_file_t* file);

void flush_buffer_on_file(buffered_file_t* file);

void clearFile(buffered_file_t* file);


void recordI32(buffered_file_t* file, int32_t val);

void recordArrayI32 (buffered_file_t* file, array_i32_t* x_tab);

void recordCircularBufferI32(buffered_file_t* file, circular_buffer_i32_t* x_tab);


void recordF32(buffered_file_t* file, float32_t val);

void recordArrayF32 (buffered_file_t* file, array_f32_t* x_tab);

void recordCircularBufferF32(buffered_file_t* file, circular_buffer_f32_t* x_tab);


void recordString(buffered_file_t* file, char* string);


/*
void recordIntAsString(buffered_file_t* file, int32_t int32);

void recordIntArrayAsString(buffered_file_t* file, int32_array_t* x_tab);
 */

#endif
