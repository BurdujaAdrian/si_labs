#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include "stdio_layer.h"

// Register controll
#define LED_REGISTER PB7

void init_led(){
	DDRB |= (1 << LED_REGISTER);
}
void led_turn_on(){
	PORTB |= (1 << LED_REGISTER);
}
void led_turn_off(){
	PORTB &= ~(1 << LED_REGISTER);
}


// Commands
#define ledon_size 6
const char *led_on = "led on";

bool turn_on_command(){
	return ((bufflen() == ledon_size+1) && (strncmp(buffer(),led_on,ledon_size)==0));
}

#define ledoff_size 7
const char *led_off = "led off";

bool turn_off_command(){
	return ((bufflen() == ledoff_size+1) && (strncmp(buffer(),led_off,ledoff_size)==0));
}
