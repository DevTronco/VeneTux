#include "headers/utils.h"

void k_clear_screen(int bg) {
    volatile char* video = (volatile char*)0xB8000; //video memory
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = bg;
    }
}

void write(void){
    k_clear_screen(0x0);
    putchar('N');
    putchar('i');
    putchar('g'),
    putchar('g');
    putchar('a');

}

void kmain(){
    write();
}