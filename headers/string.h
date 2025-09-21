#include "utils.h"

typedef const char* u_string;
typedef char* string;

void putstr(u_string sentence){
    while(*sentence){
       putchar(*sentence++);
    }
}

void print_at(unsigned char c, int row, int col){
    if (row >= VGA_ROW || col >= VGA_COLS) return;

    int offset = (row * VGA_COLS + col) * 2;
    vidmem[offset] = c;
    vidmem[offset + 1] = 0x0f;
}

print_str_at(u_string str, int row, int col){
    if (row >= VGA_ROW || col >= VGA_COLS) return;

    int offset = (row * VGA_COLS + col) * 2;
    while (*str){
        vidmem[offset] = *str;
        vidmem[offset + 1] = 0x0f;
        offset += 2;
        str++;
    }
}

int strlen(u_string str){
    int len = 0;

    while (str[len] != '\0'){
        len++;
    }

    return len;
}