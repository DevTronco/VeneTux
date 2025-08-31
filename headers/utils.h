#ifndef UTILS_H
#define UTILS_H

unsigned char putchar(char c){
    volatile char* vidmem = (volatile char*) 0xb8000;
    static int pos = 0;
    vidmem[pos++] = c;
    vidmem[pos++] = 0x0f; //white
}

#endif