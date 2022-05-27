
#include "Record.h"

#define SIMULATION 1;

void openFile(buffered_file_t* file) {
#ifndef SIMULATION
    FRESULT fr;
    fr = f_open(file->fil, file->fname, FA_OPEN_APPEND | FA_WRITE);
    if (fr) {
        printf("ERR: Cannot open %s\n", file->fname);
    }
#else
    file->fil = fopen(file->fname, "a");
#endif
}


void closeFile(buffered_file_t* file) {
#ifndef SIMULATION
    f_close(file->fil);
#else
    fclose(file->fil);
#endif
}


void flush_buffer_on_file(buffered_file_t* file){
#ifndef SIMULATION
    UINT bw = 0;
    f_write(file->fil, file->buff->data, file->buff->offset, &bw);
    file->buff->offset = 0;
#else
    //printf("offset: %d\n", file->buff->offset);
    unsigned long written;
    written = fwrite(file->buff->data, 1, file->buff->offset, file->fil);
    //printf("written: %d\n", written);

    file->buff->offset = 0;
#endif
}


void clearFile(buffered_file_t* file) {
#ifndef SIMULATION
    f_open(file->fil, file->fname, FA_CREATE_ALWAYS | FA_WRITE);
    f_close(file->fil);
#else
    file->fil = fopen(file->fname, "w");
    fclose(file->fil);
#endif
}


void recordI32(buffered_file_t* file, int32_t val){
    if(file->buff->offset+4 >= SD_BUFF_SZ) {
        printf("Buffer of %s is full, flush it\n", file->fname);
        flush_buffer_on_file(file);
    }

    // Invert byte order
    
    union toChar toc;
    toc.i = val;

    file->buff->data[file->buff->offset] = *(toc.c);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c+1);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c+2);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c+3);
    file->buff->offset++;
    
    
    // Do not invert byte order
    /*
    union toChar toc;
    toc.i = val;

    file->buff->data[file->buff->offset] = *(toc.c+3);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c+2);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c+1);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c);
    file->buff->offset++;
    */
}


void recordArrayI32(buffered_file_t* file, array_i32_t* x_tab) {
    if(x_tab->len*4 > SD_BUFF_SZ) {
        printf("ERR: Space in file buffer (%d) is less than space of array to record (%d) for file \"%s\"\n",
               SD_BUFF_SZ, x_tab->len*4, file->fname);
        return;
    }
    if(x_tab->len*4 > SD_BUFF_SZ - file->buff->offset) {
        printf("Buffer of %s is full, flush it\n", file->fname);
        flush_buffer_on_file(file);
    }

    int i;
    int32_t r;
    for (i = 0; i < x_tab->len; i++) {
        getArrayI32(x_tab, i, &r);
        recordI32(file, r);
    }
}


void recordCircularBufferI32(buffered_file_t* file, circular_buffer_i32_t* cbuff) {
    if(cbuff->len*4 > SD_BUFF_SZ) {
        printf("ERR: Space in file buffer (%d) is less than space of array to record (%d) for file \"%s\"\n",
               SD_BUFF_SZ, cbuff->len*4, file->fname);
        return;
    }
    if(cbuff->len*4 > SD_BUFF_SZ - file->buff->offset) {
        printf("Buffer of %s is full, flush it\n", file->fname);
        flush_buffer_on_file(file);
    }

    int i;
    int32_t r;

    for (i = 0; i < amountFilledCircularBufferI32(cbuff); i++) {
        getFromBegCircularBufferI32(cbuff, i, &r);
        recordI32(file, r);
    }
}







void recordF32(buffered_file_t* file, float32_t val){
    if(file->buff->offset+4 >= SD_BUFF_SZ) {
        //printf("Buffer of %s is full, flush it\n", file->fname);
        flush_buffer_on_file(file);
    }

    // Invert byte order
    union toChar toc;
    toc.f = val;

    file->buff->data[file->buff->offset] = *(toc.c);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c+1);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c+2);
    file->buff->offset++;
    file->buff->data[file->buff->offset] = *(toc.c+3);
    file->buff->offset++;
}


void recordArrayF32(buffered_file_t* file, array_f32_t* x_tab) {
    if(x_tab->len*4 > SD_BUFF_SZ) {
        printf("ERR: Space in buffer (%d) is less than space of array to record (%d) for file \"%s\"\n",
               SD_BUFF_SZ, x_tab->len*4, file->fname);
        return;
    }
    if(x_tab->len*4 > SD_BUFF_SZ - file->buff->offset) {
        //printf("Buffer of %s is full, flush it\n", file->fname);
        flush_buffer_on_file(file);
    }

    int i;
    float32_t r;
    for (i = 0; i < x_tab->len; i++) {
        getArrayF32(x_tab, i, &r);
        recordF32(file, r);
    }
}


void recordCircularBufferF32(buffered_file_t* file, circular_buffer_f32_t* x_tab) {
    if(x_tab->len*4 > SD_BUFF_SZ) {
        printf("ERR: Space in buffer (%d) is less than space of array to record (%d) for file \"%s\"\n",
               SD_BUFF_SZ, x_tab->len*4, file->fname);
        return;
    }
    if(x_tab->len*4 > SD_BUFF_SZ - file->buff->offset) {
        //printf("Buffer of %s is full, flush it\n", file->fname);
        flush_buffer_on_file(file);
    }

    int i;
    float32_t r;
    for (i = 0; i < x_tab->len; i++) {
        getFromBegCircularBufferF32(x_tab, i, &r);
        recordF32(file, r);
    }
}








// Clear files
/*
void recordString(buffered_file_t* file, char* string){
    char buff [80];
    int n, ret;
    n = sprintf(buff, "%s", string);
    if (n > 0) {
        ret = _memcopy_on_buffered_file(file,buff, (size_t)n);
        _check_ret_code(ret);
    } else {
        ERR("Error while copying string to buffer");
    }
}
*/

/*
void recordIntAsString(buffered_file_t* file, const int32_t int32){
    char buff [20];
    int n, ret;
    n = sprintf(buff, "%ld", int32);
    if (n > 0) {
        ret = _memcopy_on_buffered_file(file, buff, (size_t)n);
        _check_ret_code(ret);
    } else {
        DBG("Error while copying integer 32 to buffer");
    }
}

void recordIntArrayAsString(buffered_file_t* file, int32_array_t* x_tab) {
    int32_t i;
    for (i = 0; i < x_tab->len; i++) {
        recordInt(file, x_tab->data[i]);
        recordString(file, ",");
    }
}
*/

/*
int _memcopy_on_buffered_file(buffered_file_t* file, char* to_write, size_t size){
    size_t wmax = 0;

    // Check if we can write all data in the same buffer
    wmax = (size_t)(SD_BUFF_SZ - file->buff->offset);
    if(size > wmax) {
        return -1;
    }

    // Copy data into the file buffer
    memcpy(file->buff->data + file->buff->offset, to_write, size);
    file->buff->offset += size;

    return 0;
}
*/