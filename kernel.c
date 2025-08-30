#include "headers/utils.h"
#include "headers/string.h"
#include "headers/keyboard_driver.h"

void kmain(){
    u_string idk[] = {"idk", "idk2"};
    k_clear_screen(0x0);
    putchar('A');
    newline();
    putstr("sono un sigma");
    newline();
    more_args_str(idk, 2);

    newline();
    key_main();    
}