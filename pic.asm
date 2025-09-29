bits 32
extern key_main
extern putchar
extern rtc_handler

global keyboard_isr

init_pic:

    ;covers every irq
    mov al, 0xff
    out 0x21, al ;irq in pic1
    out 0xa1, al ;irq in pic2

    ;initialize comand for pic1 (0x20)
    mov al, 0x11
    out 0x20, al ;initialize irq0
    out 0xa0, al ;initialize irq8

    ;sets vectors of interrupt for pic1
    mov al, 0x20
    out 0x21, al ;irq = vector 0x20
    mov al, 0x28 
    out 0xa1, al ;irq8 = vector 0x28 (1 byte difference)

    ;sets working mode (pic1 && pic2)
    mov al, 0x04
    out 0x21, al ;sets pic1 to use pic2
    mov al, 0x02 
    out 0xa1, al ;sets pic2 to use another pic

    mov al, 0x01
    out 0x21, al ;pic1 sends EOI comand with 0x20
    out 0xa1, al ;pic2 sends eoi

    ;turns on interrupt
    mov al, 0x7d
    out 0x21, al ;covers any irq except irq1 (keyboard)
    mov al, 0xfe
    out 0xa1, al ;covers any irq in pic2

    sti ;enables interrupts

keyboard_isr:
    pusha               ;saves registers
    call key_main      ;calls key_main (defined in headers/drivers/keyboard_driver.h)\
    mov al, 0x20        
    out 0x20, al        ;eoi
    popa                ;resets registers
    iret

rtc_isr:
    pusha
    call rtc_handler
    mov al, 0x20
    out 0xA0, al 
    out 0x20, al 
    popa
    iret

section .note.GNU-stack,"",@progbits
