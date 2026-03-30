#include "task_procs.h"

#include "button_driver.h"
#include "leds_driver.h"
#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include "Arduino.h"

#define TASK1_OFFSET 0
#define TASK2_OFFSET 1
#define TASK3_OFFSET 255

#define TASK1_REC 0
#define TASK2_REC 1
#define TASK3_REC 255

void init_tasks(task_t *tasks){ 
	tasks[0] = (task_t){
		.context = (context_t) {TASK1_OFFSET,TASK1_OFFSET,TASK1_REC},
		.proc = task1_proc,
	}; 
	tasks[1] = (task_t){
		.context = {TASK2_OFFSET,TASK2_OFFSET,TASK2_REC},
		.proc =task2_proc,	
	};
	tasks[2] = (task_t){
		.context = {TASK3_OFFSET,TASK3_OFFSET,TASK3_REC},
		.proc = task3_proc,
	};
}

// button state global vars
bool button_prev_state = HIGH; 
bool button_state = HIGH;
unsigned long button_timestamp; 
int button_duration;

// stack(unsigned long) Button_deltas;
Button_deltas button_deltas;

// manage press intervals
void task1_proc(void){
	bool button_state = is_button_up();

	// handle state of button changed
	if(button_state != button_prev_state) {

		unsigned long now = millis();

		// if the button was released 
		if (button_state) {
			button_duration = now - button_timestamp;
			push(&button_deltas, button_duration);
			printf("just pushed, %d\n",button_deltas.idx);

			if (button_duration < 500){
				// short hold
				green_led_turn_on();
				red_led_turn_off();
			} else {
				// long hold
				red_led_turn_on();
				green_led_turn_off();
			}

		} else {
			// if button was pressed
			button_timestamp = now;
		}
		button_prev_state = button_state;
	}
	// else, nothing happens
}

#define LONG_PRESS 500
int presses,sum_shorts,sum_longs,n_shorts,n_longs;
// manage press statistics
void task2_proc(void){
	yl_exec_blink();	
	
	// button was pressed and released, ie a delta was pushed onto the stack
	if (button_deltas.idx > 0) {
		unsigned long delta = pop(&button_deltas);
		printf("Pushed delta %lu\n",delta);
			
		presses +=1;
		if (delta < LONG_PRESS) {
			sum_shorts = sum_shorts + delta;
			n_shorts += 1;
			yl_setup_blink(5);
		} else {
			sum_longs = sum_longs + delta;
			n_longs += 1;
			yl_setup_blink(10);
		}
	}
}


#define REPORT_INTERVAL 10
unsigned long report_timestamp;

void task3_proc(void){

	unsigned long now = millis();
	if((now - report_timestamp)/1000 < REPORT_INTERVAL ) return;

	report_timestamp = now;

	unsigned long averege_holds = sum_longs + sum_shorts;
	printf("Durata medie a apasarilor: %lu\n",averege_holds);
		
	
	if (n_longs+n_shorts > 0) {
		averege_holds = averege_holds / (n_longs+n_shorts);
	}


	printf(
		"Numarul de apasari: %d\n"
		"Numarul de apasari scurte: %d\n"
		"Numarul de apasari lungi:  %d\n"
		"Durata medie a apasarilor: %lu\n",
		n_shorts+n_longs,
		n_shorts,
		n_longs,
		averege_holds
	);

	// reset
	n_shorts =0;
	n_longs = 0;
	sum_shorts = 0;
	sum_longs  = 0;
}


