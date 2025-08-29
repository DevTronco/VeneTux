#include "utils.h"

int shift = true;

unsigned char capture_char(uint8_t input, int shift){  
    if (shift){
        switch (input){ //cata el tasto
        case 0x1E: return 'A';
        case 0x30: return 'B';
        case 0x2E: return 'C';
        case 0x20: return 'D';
        case 0x12: return 'E';
        case 0x21: return 'F';
        case 0x22: return 'G';
        case 0x23: return 'H';
        case 0x17: return 'I';
        case 0x24: return 'J';
        case 0x25: return 'K';
        case 0x26: return 'L';
        case 0x32: return 'M';
        case 0x31: return 'N';
        case 0x18: return 'O';
        case 0x19: return 'P';
        case 0x10: return 'Q';
        case 0x13: return 'R';
        case 0x1F: return 'S';
        case 0x14: return 'T';
        case 0x16: return 'U';
        case 0x2F: return 'V';
        case 0x11: return 'W';
        case 0x2D: return 'X';
        case 0x15: return 'Y';
        case 0x2C: return 'Z';
        default: return '?';
    }
    }
    else{
        switch(input) {
        case 0x1E: return 'a';
        case 0x30: return 'b';
        case 0x2E: return 'c';
        case 0x20: return 'd';
        case 0x12: return 'e';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x17: return 'i';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x32: return 'm';
        case 0x31: return 'n';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x10: return 'q';
        case 0x13: return 'r';
        case 0x1F: return 's';
        case 0x14: return 't';
        case 0x16: return 'u';
        case 0x2F: return 'v';
        case 0x11: return 'w';
        case 0x2D: return 'x';
        case 0x15: return 'y';
        case 0x2C: return 'z';
        default:   return '?';
    }
}
}

uint8_t read_scancode(){
    uint8_t status;
    uint8_t scancode;

    // waits input buffer to be full
    do {
        __asm__ __volatile__ ("inb $0x64, %0" : "=a"(status));
    } while ((status & 1) == 0);

    // reads scancode
    __asm__ __volatile__ ("inb $0x60, %0" : "=a"(scancode));
    return scancode;
}

void putchar(char c){
    volatile char* vidmem = (volatile char*) 0xb8000;
    vidmem[pos++] = c;
    vidmem[pos++] = 0x07;
}

void key_main(void){
    while(true){
        uint8_t code = read_scancode();

        if (code == 0x2a || code == 0x36){
            shift = false;
            continue;
        }
        else if (code == 0xaa || code == 0xb6){
            shift = true;
            continue;
        }
        if (code & 0x80) {
            continue;
        }

        unsigned char c = capture_char(code, shift);
        if (c != '?'){
            putchar(c);
        }
    }
}