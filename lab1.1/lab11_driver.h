#pragma once
#include <stdbool.h>

void init_led();
void init_stdout();

void led_turn_on();
void led_turn_off();

bool turn_on_command();
bool turn_off_command();
