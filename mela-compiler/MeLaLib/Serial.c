#include "Serial.h"
#include "Array.h"
#include <arm_math.h>
#include <stdio.h>



void serialPrintI32(int32_t val){
    printf("%d", val);
}

void serialPrintlnI32(int32_t val){
    serialPrintI32(val);
    printf("\n");
}

void serialPrintI32Array(array_i32_t* array){
    int i;
    for (i = 0; i < array->len; i++) {
        serialPrintI32(array->data[i]);
        if (i < array->len-1) {
            printf(", ");
        }
    }
    printf("\n");
}



void serialPrintF32(float32_t val){
    //printf("%f    <-> ", val);
    int intpart = (int) val;
    int decpart = (int) ((val - (float)intpart)*1000000.);
    if (decpart < 0) {
        decpart = -decpart;
    }
    printf("%d.%06d", intpart, decpart);

}

void serialPrintlnF32(float32_t val){
    serialPrintF32(val);
    printf("\n");
}

void serialPrintF32Array(array_f32_t* array){
    int i;
    for (i = 0; i < array->len; i++) {
        serialPrintF32(array->data[i]);
        if (i < array->len-1) {
            printf(", ");
        }
    }
    printf("\n");
}



void serialPrintString(const char* string){
    printf("%s", string);
}


void serialPrintlnString(const char* string){
    serialPrintString(string);
    printf("\n");
}

