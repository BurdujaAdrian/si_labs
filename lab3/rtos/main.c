#include <Arduino.h>
#include "task_procs.h"


int main(void){
	init();
	init_tasks();

	for(;;){ }

	return 0;
}

