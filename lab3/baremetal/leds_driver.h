#pragma once

#include <stdbool.h>
void init_leds();
void init_button();

void red_led_turn_on();
void red_led_turn_off();
void green_led_turn_on();
void green_led_turn_off();
void yl_led_turn_on();
void yl_led_turn_off();

void yl_exec_blink();
void yl_setup_blink(int);

bool is_button_up();
