#include "../utils.h"


#define MAX_INPUT 128
char input_buffer[MAX_INPUT];

bool shift = false;

uint8_t capture_char(uint8_t c, bool shift){
    if (shift){
        switch (c){ 
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
        case 0x39: return ' ';
        case 0x1c: return '\n';
        default: return '?';
        }
    }
    else{
        switch(c) {
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
        case 0x39: return ' ';
        case 0x1c: return '\n';
        default:   return '?';
        }
    }
}

uint8_t read_raw_scancode(){
    uint8_t status;
    do{
        status = inb(0x64);
    } while (!(status & 1));
    return inb(0x60);
}

void key_putchar(char c){
    if (c == '\n'){
        pos += (160 - (pos % 160));
    }
    else{
        vidmem[pos] = c;
        vidmem[pos + 1] = 0x07;
        pos += 2;
    }

    if (pos >= 80 * 25 * 2){
        scroll_screen();
        pos = (80 * 24) * 2;
    }
}

void key_main(void){
    while(true){
        uint8_t code = read_raw_scancode();

        if (code == 0x2a || code == 0x36){
            shift = true;
            continue;
        }
        else if (code == 0xaa || code == 0xb6){
            shift = false;
            continue;
        }

        if (code & 0x80){
            continue;
        }
            
        if (code == 0x0e){
            if (pos > 0){
                pos -= 2;
                vidmem[pos] = ' ';
                vidmem[pos + 1] = 0x07;
            }
            continue;
        }

        char c = capture_char(code, shift);

        if (c != '?'){
            key_putchar(c);
        }

        sleep(1);
    }
}

string get_user_input(){
    int input_pos = 0;
        while(true){
        uint8_t code = read_raw_scancode();

        if (code == 0x2a || code == 0x36){
            shift = true;
            continue;
        }
        else if (code == 0xaa || code == 0xb6){
            shift = false;
            continue;
        }

        if (code & 0x80){
            continue;
        }
            
        if (code == 0x0e){
            if (input_pos > 0){
                input_pos -= 2;
                vidmem[input_pos] = ' ';
                vidmem[input_pos + 1] = 0x07;
                input_buffer[input_pos] = '\0';

                input_pos *= 1;
                vidmem[input_pos * 2] = ' ';
                vidmem[input_pos * 2 + 1] = 0x07;
            }
            continue;
        }

        if (code == 0x1c){
            key_putchar('\n');
            input_buffer[input_pos] = '\0';
            return input_buffer;
        }

        char c = capture_char(code, shift);

        if (c != '?'){
            key_putchar(c);
        }

        sleep(1);
    }
}