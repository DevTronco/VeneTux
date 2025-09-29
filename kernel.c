#include "headers/utils.h"
#include "headers/string.h"
#include "headers/drivers/keyboard.h"
#include "headers/memory.h"
#include "headers/drivers/shutdown.h"
#include "headers/drivers/reboot.h"
#include "headers/time.h"

void command_handler(string cmd, string args) {
    if (strcmp(cmd, "echo") == 0) {
        putstr(args);
    }
}

bool process_input(string input){
    char cmd[16];
    int i = 0;

    //first word
    while (input[i] != ' ' && input[i] != '\0' && i < 15) {
        cmd[i] = input[i];
        i++;
    }
    cmd[i] = '\0';

    int arg_start = i;
    if (input[arg_start] == ' ') arg_start++;

    if (strcmp(cmd, "help") == 0){
        putstr("Avaiable commands: \r\n");
        putstr("help: you just wrote it gang\r\n");
        putstr("info: shows VeneTux verison\r\n");
        putstr("author_info: shows author socials\r\n");
        putstr("clear: clears screen\r\n");
        putstr("echo: puts your text as output \r\n");
        putstr("credits: shows the other people that helped in making VeneTux! \r\n");
        putstr("stop: stops shell\r\n");
        putstr("reboot: reboots the system \r\n");
        putstr("shutdown: shutdowns the system \r\n");
        putstr("time: prints current time \r\n");
        return true;
    }
    else if (strcmp(cmd, "clear") == 0){
        rm_bg(0x0);
        return true;
    }
    else if (strcmp(cmd, "info") == 0){
        putstr("VeneTux version 0.0.1 beta \r\n");
        return true;
    }
    else if(strcmp(cmd, "author_info") == 0){
        putstr("Add me on Discord: _tr0nc0_ \r\n");
        putstr("Star VeneTux on GitHub! https://github.com/DevTronco/VeneTux ! \r\n");
        return true;
    }
    else if (strcmp(cmd, "stop") == 0){
        return false;
    }
    else if (strcmp(cmd, "reboot") == 0){
        reboot();
        return true;
    }
    else if (strcmp(cmd, "shutdown") == 0){
        shutdown();
        return true;
    }
    else if (strcmp(cmd, "credits") == 0){
        putstr("Tronco (owner) \r\n");
        putstr("MalwareLab 150: made ACPI driver \r\n");
        return true;
    }
    else if (strcmp(cmd, "echo") == 0){
        command_handler(cmd, &input[arg_start]);
        putstr("\r\n");
        return true;
    }
    else if (strcmp(cmd, "time") == 0){
        print_time();
    }
    else{
        putstr("Command not found \r\n");
        return true;
    }
}

void kmain(){
    rm_bg(0x0);
    putstr("Hello! \r\n");
    putstr("Digit 'help' to see the commands. \r\n");
    while(true){
        print_time();
        putstr("CMD >> ");
        string input = get_user_input();
        bool should_continue = process_input(input);
        if (!should_continue){
            break;
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
}