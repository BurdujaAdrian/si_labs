#include <Arduino.h>
#include "motor.h"
#include "stdio_layer.h"
#include "tasks.h"

int main() {
	init();
	motor_setup();
	stdio_init();
	tasks_init();
	
	for (;;){
		input_task();
		motor_task();
		report_task();
	}

	return 0;
}
