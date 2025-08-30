//types
#ifndef UTILS_H
#define UTILS_H

#define true 1
#define false 0

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

#ifdef ARCH_64BIT
typedef uint64_t size_t;
#else
typedef uint32_t size_t;
#endif

volatile int pos = 0;
volatile char* videomem = (volatile char*) 0xb8000;

void newline(){
        if (pos >= 80 * 25 * 2) { // 80 chars x 25 rows x 2 bytes per char
        //scroll
        for (int i = 0; i < 80 * 24 * 2; i++) {
            ((volatile char*)0xB8000)[i] = ((volatile char*)0xB8000)[i + 80 * 2];
        }

        //clean 
        for (int i = 80 * 24 * 2; i < 80 * 25 * 2; i++) {
            ((volatile char*)0xB8000)[i] = ' ';
            ((volatile char*)0xB8000)[i + 1] = 0x0F; 
        }

            pos -= 80 * 2; 
        } else {
            pos = (pos / (80 * 2)) * (80 * 2) + 80 * 2; 
        }
}


void k_clear_screen(int bg) {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        videomem[i] = ' ';
        videomem[i + 1] = bg;
    }
}

#endif