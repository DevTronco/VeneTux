#ifndef TIME_H
#define TIME_H

#include "utils.h"
#include "string.h"

typedef struct{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t days;
    uint8_t months;
    uint8_t years; 
} time;

uint8_t read_cmos(uint8_t reg){
    //CMOS registry
    outb(0x70, reg);
    return inb(0x71);
}

void rtc_handler(){
    outb(0x70, 0x0c);
    inb(0x71);
}

uint8_t bcd_to_bin(uint8_t val){
    return (val & 0x0f) + ((val / 16) * 10);
}

uint8_t read_time_reg(uint8_t reg, bool is_bcd){
    uint8_t val = read_cmos(reg);
    return is_bcd ? bcd_to_bin(val) : val;
}

int get_update_in_progress_flag() {
    outb(0x70, 0x0A);         
    return (inb(0x71) & 0x80); 
}

time read_time(){
    time t1, t2;
    uint8_t statusB = read_cmos(0x0B);
    bool is_bcd = !(statusB & 0x04);

    int max_attempts = 10;
    int attempts = 0;

    do {
        attempts++;
        if (attempts > max_attempts) {
            print_str_at("TIME READ FAIL", 0, 65);
            break;
        }

        
        //asm volatile ("cli");

        while (get_update_in_progress_flag());

        t1.seconds = read_time_reg(0x00, is_bcd);
        t1.minutes = read_time_reg(0x02, is_bcd);
        t1.hours   = read_time_reg(0x04, is_bcd);
        t1.days    = read_time_reg(0x07, is_bcd);
        t1.months  = read_time_reg(0x08, is_bcd);
        t1.years   = read_time_reg(0x09, is_bcd);

        while (get_update_in_progress_flag());

        t2.seconds = read_time_reg(0x00, is_bcd);
        t2.minutes = read_time_reg(0x02, is_bcd);
        t2.hours   = read_time_reg(0x04, is_bcd);
        t2.days    = read_time_reg(0x07, is_bcd);
        t2.months  = read_time_reg(0x08, is_bcd);
        t2.years   = read_time_reg(0x09, is_bcd);

        //asm volatile ("sti");  

    } while (
        t1.seconds != t2.seconds ||
        t1.minutes != t2.minutes ||
        t1.hours   != t2.hours   ||
        t1.days    != t2.days    ||
        t1.months  != t2.months  ||
        t1.years   != t2.years
    );

    return t1;
}

void print_time(){
    time Time = read_time();
    //print_str_at("Start read_time", 0, 60);
    if (Time.hours == 0 && Time.minutes == 0 && Time.seconds == 0){
        print_str_at("Time read error", 0, 70);
        return;
    }

    char buffer[16];

    Time.hours = (Time.hours + 2) % 24;

    itoa(Time.hours, buffer);
    print_str_at(buffer, 0, 72);
    print_str_at(":", 0, 74);

    itoa(Time.minutes, buffer);
    print_str_at(buffer, 0, 75);
    print_str_at(":", 0, 77);

    itoa(Time.seconds, buffer);
    print_str_at(buffer, 0, 78);

    //sleep(1);
}

#endif