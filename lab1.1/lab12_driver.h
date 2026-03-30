#pragma once
#include <stdbool.h>

void init_leds();
void init_keypad();

void red_led_turn_on();
void red_led_turn_off();

void green_led_turn_on();
void green_led_turn_off();

const char* read_code(); 

bool read_key_command();
