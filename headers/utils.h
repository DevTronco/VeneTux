#ifndef UTILS_H
#define UTILS_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

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