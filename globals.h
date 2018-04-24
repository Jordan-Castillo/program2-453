//Global defines

#ifndef GLOBALS_H
#define GLOBALS_H
//#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//place defines and prototypes here

#define BLACK 0x30
#define RED 0x31
#define GREEN 0x32
#define YELLOW 0x33
#define BLUE 0x34
#define MAGENTA 0x35
#define CYAN 0x36
#define WHITE 0x37


void stayHere(void);
void lightOn(void);
void lightOff(void);
void blink(void);
uint8_t read_byte();
void serial_init();
unsigned int write_byte(unsigned int b);
void print_string(char* s);
void print_int(uint16_t i);
void print_int32(uint32_t i);
void print_hex(uint16_t i);
void print_hex32(uint32_t i);
void set_cursor(uint8_t row, uint8_t col);
void set_color(uint8_t color);
void clear_screen(void);
void work(void);

#endif
