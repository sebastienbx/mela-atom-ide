#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdint.h>
#include "Array.h"


void serialPrintI32(int32_t val);

void serialPrintlnI32(int32_t val);

void serialPrintI32Array(array_i32_t* array);



void serialPrintF32(float32_t val);

void serialPrintlnF32(float32_t val);

void serialPrintF32Array(array_f32_t* array);



void serialPrintString(const char* string);

void serialPrintlnString(const char* string);

#endif
