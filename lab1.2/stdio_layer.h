#pragma once
#include <stdio.h>

// forward decl for Arduino.h function
int strcmp(const char *, const char *);

int lcd_putchar(char c, FILE *stream);

char* buffer();
int bufflen();

void init_stdout();

void read_input();
void print_input();

