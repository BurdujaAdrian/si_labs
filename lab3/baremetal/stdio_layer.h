#pragma once
#include <stdio.h>

// forward decl for Arduino.h function
int strncmp(const char *, const char *, unsigned int);

void uart_init(unsigned long baud);
int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

char* buffer();
int bufflen();

void init_stdout();

void read_input();
void print_input();

