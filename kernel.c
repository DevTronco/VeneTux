#include "headers/utils.h"
#include "headers/string.h"

int pos = 0;

void newline(){
    int row = pos / (80 * 2);
    row++;
    pos = row * 80 * 2;
}

void putchar(char c){
    volatile char* vidmem = (volatile char*) 0xb8000;
    vidmem[pos++] = c;
    vidmem[pos++] = 0x07;
}

void k_clear_screen(int bg) {
    volatile char* video = (volatile char*)0xB8000; //video memory
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = bg;
    }
}

void kmain(){
    u_string idk[] = {"idk", "idk2"};
    k_clear_screen(0x0);
    putchar('A');
    newline();
    putstr("sono un sigma");
    newline();
    more_args_str(idk, 2);
}