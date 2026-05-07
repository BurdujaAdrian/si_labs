#include <Arduino.h>
#include "stdio_layer.h"
#include "tasks.h"

int main() {
	init();
	stdio_init();
	tasks_init();
	
	for (;;){
		input_task();
		fan_task();
		controll_task();
		report_task();
	}

	return 0;
}
