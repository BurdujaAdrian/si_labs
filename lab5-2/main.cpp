#include <Arduino.h>
#include "motor.h"

int main() {
	init();
	motor_setup();
	
	for (;;){
		analogWrite(3, 127);
	}

	return 0;
}
