#include "button_driver.h"
#include <Arduino.h>

#define BUTT_PIN 2

void init_button()  { pinMode(BUTT_PIN, INPUT_PULLUP); }
bool is_button_up() { return digitalRead(BUTT_PIN);    }



