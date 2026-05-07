#include "fan.h"

#include <stdbool.h>
#include <Arduino.h>

// TODO: figure out if these should be switched
#define FAN_ON LOW
#define FAN_OFF HIGH
uint8_t fan_state;

bool fan_is_on(){
	return fan_state == FAN_ON;
}


void fan_turn_on(bool comfirm){
	if (comfirm) {
		digitalWrite(FAN_PIN,FAN_ON);
	} else {
		digitalWrite(FAN_PIN,FAN_OFF);
	}
}
