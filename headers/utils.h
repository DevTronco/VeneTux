#ifndef UTILS_H
#define UTILS_H

#define VGA_COLS 80
#define VGA_ROW 25


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

void itoa(int value, char* str) {
    char* p = str;
    char* p1, tmp_char;
    int tmp_value;

    if (value == 0) {
        *p++ = '0';
        *p = '\0';
        return;
    }

    if (value < 0) {
        *p++ = '-';
        value = -value;
    }

    p1 = p;

    while (value) {
        tmp_value = value % 10;
        *p++ = '0' + tmp_value;
        value /= 10;
    }
    *p = '\0';

    // Reverse
    while (--p1 < --p) {
        tmp_char = *p;
        *p = *p1;
        *p1 = tmp_char;
    }
}

unsigned int rm_bg(int x){
    for (int i = 0; i < VGA_ROW * VGA_COLS * 2; i+=2){
        vidmem[i] = ' ';
        vidmem[i+1] = 0x0f;
    }
}
unsigned char putchar(char c){
    vidmem[pos++] = c;
    vidmem[pos++] = 0x0f; //white
}

int putint(int x){
    char buffer[16];
    itoa(x, buffer);
    char* s = buffer;
    while (*s){
        vidmem[pos++] = *s++;
        vidmem[pos++] = 0x0f;
    }

    return s;
}

#endif