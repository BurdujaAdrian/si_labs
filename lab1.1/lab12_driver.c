#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "stdio_layer.h"

// Register controll
#define RED_LED_REGISTER PJ0
#define GREEN_LED_REGISTER PJ1
#define LED_DDR DDRJ
#define LEDS_PORT PORTJ

#define ROW_DDR DDRA
#define COL_DDR DDRC

void init_leds(){
	LED_DDR |= (1 << RED_LED_REGISTER);
	LED_DDR |= (1 << GREEN_LED_REGISTER);
	
}

void init_keypad(){
	COL_DDR &= ~((1 << PC0) | (1<<PC2) | (1<<PC4) | (1<<PC6));
	ROW_DDR |=   (1 << PA1) | (1<<PA3) | (1<<PA5) | (1<<PA7) ;
}

void red_led_turn_on() { LEDS_PORT |=  (1 << RED_LED_REGISTER); }
void red_led_turn_off(){ LEDS_PORT &= ~(1 << RED_LED_REGISTER); }

void green_led_turn_on() { LEDS_PORT |=  (1 << GREEN_LED_REGISTER); }
void green_led_turn_off(){ LEDS_PORT &= ~(1 << GREEN_LED_REGISTER); }

// KeyPadControll
#define ROW_PORT PORTA
#define MAT_SIZE 4
const uint8_t ROW_REGISTERS[MAT_SIZE] = { PA1, PA3, PA5, PA7, };

#define COL_PIN PINC
const uint8_t COL_REGISTERS[MAT_SIZE] = { PC0, PC2, PC4, PC6, };

const char characters[MAT_SIZE][MAT_SIZE] = { "123A", "456B", "789C", "*0#D" };

int read_col_reg(){
	int out = -1;
	for(int i=0; i<MAT_SIZE;++i){
		if(COL_PIN & (1<<COL_REGISTERS[i])){
			out = i;
			break;
		}
	}
	return out;
}

typedef struct pair{ int e[2]; } pair;

pair read_matrix(){
	pair res = { .e = {-1,-1} };

	for(int row=0; row<MAT_SIZE;++row){
		ROW_PORT |=  (1 << ROW_REGISTERS[row]);
		int col = read_col_reg();
		ROW_PORT &= ~(1 << ROW_REGISTERS[row]);
		if(col != -1) {
			res = (pair){.e = {col,row}};
			break;
		}

	}
	return res;
}


char read_key(){
	pair res;

	for(;;){
		res = read_matrix();
		if (res.e[0] != -1) { break; }
	}

	int col = res.e[0];
	int row = res.e[1];

	return characters[col][row];
}

const char* read_code(){
	char* input = buffer(); 
	int buff_index = 0;
	
	for (;;) {
		char in = read_key();
		printf("Read key:%c\n",in);

		if (in == '#') {
			// terminate string
			input[buff_index % bufflen()] = 0;
			break;
		}
		
		input[buff_index % bufflen()] = in;
		buff_index +=1;
		// wait a little
		_delay_ms(1000);
	}

	return input;
}
// Commands
#define key_size 8
const char *read_key_str = "read key";

bool read_key_command(){
	return ((bufflen() == key_size+1) && (strncmp(buffer(),read_key_str,key_size)==0));
}

