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

void print_color(u_string str, int attr){
    while(*str){
        vidmem[pos] = *str;
        vidmem[pos + 1] = attr;
        pos += 2;
        str++;
    }
}

void print_color_at(u_string str, int x, int y, int attr){
    if (x >= VGA_ROW || y >= VGA_COLS) return;

    int offset = (x * VGA_COLS + y) * 2;
    while(*str){
        vidmem[offset] = *str;
        vidmem[offset + 1] = attr;
        offset += 2;
        str++;
    }
}

void print_change_color(u_string str){

    int color = 0x0f;

    while (*str){
        vidmem[pos] = *str;
        vidmem[pos + 1]  = color;
        pos += 2;
        color += 0x10;
        str++;
    }
}

void print_change_color_at(u_string str, int x, int y){
    if (x >= VGA_ROW || y >= VGA_COLS) return;

    int color = 0x0f;

    int offset = (x * VGA_COLS + y) * 2;
    while(*str){
        vidmem[offset] = *str;
        vidmem[offset + 1] = color;
        offset += 2;
        color += 0x10;
        str++;
        sleep(2);
    }
}