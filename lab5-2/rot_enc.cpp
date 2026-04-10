#include "rot_enc.h"
#include <Arduino.h>

#define ENCODER_CLK 2  // interrupt pin
#define ENCODER_DT  3


#define ENCODER_STEP 5

volatile int encoder_delta = 0;

static void encoder_isr() {
	// CLK went LOW; DT HIGH = clockwise, DT LOW = counterclockwise
	if (digitalRead(ENCODER_DT) == HIGH) {
		encoder_delta += ENCODER_STEP;
	} else {
		encoder_delta -= ENCODER_STEP;
	}
}

void encoder_setup() {
    pinMode(ENCODER_CLK, INPUT);
    pinMode(ENCODER_DT,  INPUT);

    attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), encoder_isr, FALLING);
}

int encoder_read() {
	noInterrupts();
	int delta = encoder_delta;
	encoder_delta = 0;
	interrupts();
	return delta;
}
