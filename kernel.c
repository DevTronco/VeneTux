#include "headers/utils.h"
#include "headers/string.h"

void putchar(char c){
    volatile char* vidmem = (volatile char*) 0xb8000;
    static int pos = 0;
    vidmem[pos++] = c;
    vidmem[pos++] = 0x07;
}

void putstr(u_string *sentence){
    volatile unsigned char* vidmem = (volatile unsigned char*) 0xb8000;
    static int pos;
    while(*sentence){
        vidmem[pos++] = sentence++;
        vidmem[pos++] = 0x07;
    }
}

void k_clear_screen(int bg) {
    volatile char* video = (volatile char*)0xB8000; //video memory
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = bg;
    }
}

void kmain(){
    putchar('A');
    putstr("test");
}