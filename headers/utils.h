
//creation of inb and outb ASM functions
//
//uint8_t inb(uint16_t port){ //per ora non serveono
   // uint8_t value;
    //__asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    //return value; 
//}
//
void putchar(char c){
    volatile char* vidmem = (volatile char*) 0xb8000;
    static int pos = 0;
    vidmem[pos++] = c;
    vidmem[pos++] = 0x07;
}