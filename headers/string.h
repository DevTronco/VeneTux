#include "utils.h"

typedef const char* u_string;
typedef char* string;

void putstr(u_string sentence){
    while(*sentence){
        videomem[pos++] = *sentence++;
        videomem[pos++] = 0x07;
    }
}

void more_args_str(u_string strings[], int count){
    for (int i = 0; i < count; i++){
        putstr(strings[i]);
    }
}