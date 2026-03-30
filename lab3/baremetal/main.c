// baremetal version
#include <Arduino.h>
#include <stdbool.h>
#include <stdio.h>
#include "stdio_layer.h"
#include "task_procs.h"
#include "button_driver.h"
#include "leds_driver.h"
#include "inter.h"


task_t tasks[3];

int main(void){
	init();
	init_button();
	init_leds();
	init_stdout();
	init_tasks(tasks);

	for (int i=0; i<TASK_N;++i) {
		printf("%d context count  %d\n",i,tasks[i].context.cnt);
		printf("%d context offset %d\n",i,tasks[i].context.offset);
		printf("%d context rec    %d\n",i,tasks[i].context.rec);
	
	}

	init_clock();
	
	for(;;){
	}
	return 0;
}

ISR(TIMER1_COMPA_vect){ // main loop
	for (int i=0; i<TASK_N;++i) {
		context_t ctx = tasks[i].context;
		context_proc* proc = tasks[i].proc;
		if (ctx.cnt > 0) { 
			ctx.cnt -=1; 
		} else {
			ctx.cnt = ctx.offset;
			proc();
		}
		tasks[i].context = ctx;
	}
}
