bits 32
section .text
    align 4
    dd 0x1BADB002               ;magic num
    dd 0x00                     ;flags
    dd -(0x1BADB002 + 0x00)     ;checksum

global _start
extern kmain

;calls kmain after disabling interrupts and then halts the CPU
_start:
    cli
    call kmain
    hlt

;optional
section .bss
