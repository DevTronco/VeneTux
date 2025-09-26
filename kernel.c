#include "headers/utils.h"
#include "headers/string.h"
#include "headers/drivers/keyboard.h"


void kmain(){
    rm_bg(0x0);
    putchar('W');
    putstr(" ciao mondo");
    print_at('x ', 15, 40);
    print_str_at("sigma", 20, 60);
    //putint(1);
    print_str_at("dddd", 3, 19);
    int len = strlen("sigma");
    putint(len);
    put_int_at(1334, 24, 43);
    print_color("Ciao! ", 0x03);
    print_color_at("Ciao ma in un posto diverso ", 15, 25, 0x3c);
    print_change_color("Ciao!!");
    print_change_color_at("Ciao di nuovo!", 17, 25);
    //key_main();
}