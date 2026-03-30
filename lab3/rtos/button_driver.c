#include "button_driver.h"
#include <Arduino.h>

#define BUTT_PIN 10

void init_button()  { pinMode(BUTT_PIN, INPUT_PULLUP); }
uint8_t button_state() { return digitalRead(BUTT_PIN);    }
