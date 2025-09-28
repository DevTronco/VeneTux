#ifndef UTILS_H
#define UTILS_H

#define VGA_COLS 80
#define VGA_ROW 25

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

#if ARCH_64BIT 
typedef uint64_t size_t;
#else
typedef uint32_t size_t;
#endif

volatile char* vidmem = (volatile char*) 0xb8000;
static int pos = 0;

int cursor_rows = 0;
int cursor_cols = 0;

typedef enum{
    false = 0,
    true = 1
} bool;

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void scroll_screen() {
    //moves
    for (int row = 1; row < VGA_ROW; row++) {
        for (int col = 0; col < VGA_COLS; col++) {
            int from = (row * VGA_COLS + col) * 2;
            int to   = ((row - 1) * VGA_COLS + col) * 2;

            vidmem[to]     = vidmem[from];     
            vidmem[to + 1] = vidmem[from + 1]; 
        }
    }
    
    //cleans
    int last_row_offset = (VGA_ROW - 1) * VGA_COLS * 2;
    for (int col = 0; col < VGA_COLS * 2; col += 2) {
        vidmem[last_row_offset + col] = ' ';
        vidmem[last_row_offset + col + 1] = 0x0f; 
    }
}

void itoa(int value, char* str) {
    char* p = str;
    char* p1, *p2;
    char tmp_char;
    int is_negative = 0;

    if (value == 0) {
        *p++ = '0';
        *p = '\0';
        return;
    }

    if (value < 0) {
        is_negative = 1;
        *p++ = '-';
        value = -value;
    }

    p1 = p;

    while (value) {
        *p++ = '0' + (value % 10);
        value /= 10;
    }

    *p = '\0';

    // Reverse only the digits 
    p2 = p - 1;
    while (p1 < p2) {
        tmp_char = *p1;
        *p1 = *p2;
        *p2 = tmp_char;
        p1++;
        p2--;
    }
}

uint32_t rm_bg(int x){
    for (int i = 0; i < VGA_ROW * VGA_COLS * 2; i+=2){
        vidmem[i] = ' ';
        vidmem[i+1] = 0x0f;
    }

    cursor_cols = 0;
    cursor_rows = 0;
    pos = 0;
}
void putchar(char c){
    if (c == '\n'){
        cursor_cols = 0;
        cursor_rows++;
        if (cursor_rows >= VGA_ROW){
            cursor_rows = VGA_ROW - 1;
        }
        return;
    }

    int offset = (cursor_rows * VGA_COLS + cursor_cols) * 2;
    vidmem[pos++] = c;
    vidmem[pos++] = 0x0f; //white

    cursor_cols++;
    if (cursor_cols >= VGA_COLS){
        cursor_cols = 0;
        cursor_rows++;
        if (cursor_rows >= VGA_ROW){
            cursor_rows = VGA_ROW - 1;
            scroll_screen();
            pos = (cursor_rows * VGA_COLS + cursor_cols) * 2;
        }
    }
}

void putint(int x){
    char buffer[16];
    itoa(x, buffer);
    putstr(buffer);
}

void put_int_at(int x, int rows, int cols){
    if (rows >= VGA_ROW || cols >= VGA_COLS) return;

    char buffer[16];
    itoa(x, buffer);

    int offset = (rows * VGA_COLS + cols) * 2;
    for (int i = 0; buffer[i] != '\0'; i++){
        if (cols + i >= VGA_COLS) break;

        vidmem[offset] = buffer[i];
        vidmem[offset + 1] = 0x0f;

        offset += 2;
    }
}

void sleep(int seconds){
    for(int i = 0; i <= seconds; i++){
        for (volatile int s = 0; s > 100000; s++){

        }
    }
}

#endif