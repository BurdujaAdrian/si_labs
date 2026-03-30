#include <Arduino.h>
#include "keypad_driver.h"

#define ROWS 4
#define COLS 4

const char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

// uint8_t row_pins[ROWS] = {23, 25, 27, 29};
// uint8_t col_pins[COLS] = {31, 33, 35, 37};

uint8_t row_pins[ROWS] = {22, 24, 26, 28};
uint8_t col_pins[COLS] = {30, 32, 34, 36};

void init_keypad(void) {
    // setup row pins to pullup mode: they are on by default
    // when grounded, overwrites the pullup rezistor and sets it to low
    for (uint8_t r = 0; r < ROWS; r++) {
        pinMode(row_pins[r], INPUT_PULLUP);
    }
    for (uint8_t c = 0; c < COLS; c++) {
        pinMode(col_pins[c], OUTPUT);
        digitalWrite(col_pins[c], HIGH);
    }
}

char keypad_read(void) {
	for(;;){
    for (uint8_t c = 0; c < COLS; c++) {
        digitalWrite(col_pins[c], LOW);
        for (uint8_t r = 0; r < ROWS; r++) {
            if (digitalRead(row_pins[r]) == LOW) {
                delay(20);
                // wait for key to be released
                while (digitalRead(row_pins[r]) == LOW);
                digitalWrite(col_pins[c], HIGH);
                return keys[r][c];
            }
        }
        digitalWrite(col_pins[c], HIGH);
    }
	}
}
