//made by MalwareLab150, full credits to him for this file 

#include "../utils.h"

void restr() {

    uint8_t ready = 0x02;
    while (ready & 0x02)
        ready = inb(0x64); 

    outb(0x64, 0xFE);  
}

void reboot() {
    restr();

    while (1) {
        restr();
    }
}
