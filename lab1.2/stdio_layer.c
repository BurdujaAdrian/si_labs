#include "stdio_layer.h"
#include <stdio.h>
#include <Arduino.h>

// int uart_putchar(char c, FILE *stream) {
// 	if (c == '\n') { uart_putchar('\r', stream); }
// 	while(!(UCSR0A & (1 << UDRE0)));
// 	UDR0 = c;
// 	return 0;
// }
//
// int uart_getchar(FILE *stream) {
// 	while(!(UCSR0A & (1 << RXC0)));
// 	return UDR0;
// }
// void uart_init(unsigned long baud){
// 	unsigned int ubrr = F_CPU/16/baud - 1;
// 	UBRR0H = (ubrr >> 8);
// 	UBRR0L = ubrr;
// 	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
// 	UCSR0C = (3 << UCSZ00);
//
// 	stdout = &uart_str;
// 	stdin = &uart_str;
// }

int lcd_putchar(char c, FILE *stream) {
	// TODO: implement this
	return 0;
}
FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);


// end

void init_stdout(){ 
	stdout = &lcd_str;
}

// IO
#define BUFFER_SIZE 255
char _buffer[BUFFER_SIZE+1];
char* buffer(){return _buffer;}

int _bufflen = 0;
int bufflen(){return _bufflen;}

void read_input(){
	fgets(_buffer, BUFFER_SIZE, stdin);
	_bufflen = strlen(_buffer);
}

void print_input(){ printf("%s", _buffer); }
