#include "headers/utils.h"
#include "headers/string.h"

void kmain(){
    rm_bg(0x0);
    putchar('W');
    putstr(" ciao mondo");
    print_at('x', 15, 40);
    print_str_at("sigma", 20, 60);
    putint(1);
    int len = strlen("sigma");
    putint(len);
}