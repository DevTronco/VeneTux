#ifndef UTILS_H
#define UTILS_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

#if ARCH_64BIT 
typedef uint64_t size_t;
#else
typedef uint32_t size_t;
#endif

volatile char* vidmem = (volatile char*) 0xb8000;
static int pos = 0;

unsigned int rm_bg(int x){
    for (int i = 0; i < VGA_HEIGHT * VGA_WIDTH * 2; i+=2){
        vidmem[i] = ' ';
        vidmem[i+1] = 0x0f;
    }
}


unsigned char putchar(char c){
    vidmem[pos++] = c;
    vidmem[pos++] = 0x0f; //white
}

#endif