#include "utils.h"

typedef const char* u_string;
typedef char* string;

void putstr(u_string sentence){
    volatile unsigned char* vidmem = (volatile unsigned char*) 0xb8000;
    while(*sentence){
        vidmem[pos++] = *sentence++;
        vidmem[pos++] = 0x07;
    }
}

void more_args_str(u_string strings[], int count){
    for (int i = 0; i < count; i++){
        putstr(strings[i]);
    }
}