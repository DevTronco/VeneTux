#include "headers/utils.h"
#include "headers/string.h"
#include "headers/drivers/keyboard.h"

void kmain(){
    rm_bg(0x0);
    putstr("Hello! \r\n");
    while(true){
        putstr("CMD >> ");
        const char* input = get_user_input();
        //putstr("hai scritto: ");
        //putstr(input);
        //putstr("\r\n");

        if (strcmp(input, "help") == 0){
            putstr("Avaiable commands: \r\n");
            putstr("help: you just wrote it gang\r\n");
            putstr("info: shows VeneTux verison\r\n");
            putstr("author_info: shows author socials\r\n");
            putstr("clear: clears screen\r\n");
            putstr("stop: stops shell\r\n");
            putstr("reboot: reboots the system \r\n");
            putstr("shutdown: shutdowns the system \r\n");
        }
        else if (strcmp(input, "clear") == 0){
            rm_bg(0x0);
        }
        else if (strcmp(input, "info") == 0){
            putstr("VeneTux version 0.0.1 beta \r\n");
        }
        else if(strcmp(input, "author_info") == 0){
            putstr("Add me on Discord: _tr0nc0_ \r\n");
            putstr("Star VeneTux on GitHub! https://github.com/DevTronco/VeneTux! \r\n");
        }
        else if (strcmp(input, "stop") == 0){
            break;
        }
        else if (strcmp(input, "reboot") == 0){
            reboot();
        }
        else if (strcmp(input, "shutdown") == 0){
            shutdown();
        }
        else{
            putstr("Command not found \r\n");
        }
    }

    


    rm_bg(0x0);
    putchar('W');
    putstr(" ciao mondo ");
    print_at('x ', 15, 40);
    print_str_at("sigma", 20, 60);
    int len = strlen("sigma");
    putint(len);
    put_int_at(1334, 24, 43);
    print_color("Ciao! ", 0x03);
    print_color_at("Ciao ma in un posto diverso ", 15, 25, 0x3c);
    print_change_color("Ciao!!");
    print_change_color_at("Ciao di nuovo!", 17, 25);
    key_main();
}