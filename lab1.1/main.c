#include <stdio.h>
#include <Arduino.h>
#include "lab11_driver.h"
#include "lab12_driver.h"
#include "stdio_layer.h"
#include "strings.h"


int main(void){
	init();
	
	// setup
	init_led();
	init_stdout();

	init_leds();
	init_keypad();
	
	// loop
	while(1){

		// lab11 code
		read_input();

		if (turn_on_command()) {
			printf("Led on\n");
			led_turn_on();
		} else if(turn_off_command()){
			printf("Led off\n");
			led_turn_off();
		} else if (read_key_command()){// lab12 code
			#define VALID_CODE "1234"
			const char* code = read_code();
			if (string_cmp(VALID_CODE,code)) {
				green_led_turn_on();
				red_led_turn_off();
			} else {
				green_led_turn_off();
				red_led_turn_on();
			}
			print_input();

			printf("\n");
		} else {
			printf("Unknown command:");
			print_input();
			printf("\n");
		}
	}
	printf("End of loop");
	return 0;
}

