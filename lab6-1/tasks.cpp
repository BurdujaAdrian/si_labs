#include "tasks.h"
#include "Arduino.h"
#include "dht22.h"
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long ulong;
ulong	fan_time,
	input_time,
	report_time,
	temp_time;

// flags
bool conv_fail, no_input, overflow,underflow, encoder_input;

void tasks_init(){
	fan_time = millis() + 0;
	input_time = millis() + 1000;
	report_time =millis() + 2000; 

}

#ifndef CONTROLL
#define CONTROLL
// Controll implementation
#endif // CONTROLL


#define CONTR_TASK_REC 100 // milis
void controll_task(){
	// TODO: Implement controll by turning the fan on/off if the temperature is too high/low and when it's outside the band
}

#define FAN_TASK_REC 100 // milis
void fan_task(){
	// TODO: Implement fanning
}


#define INPUT_REC 1000 // milis

// unsigned long input_time; is actually defined above; ulong is alias for unsighend long
const int weights[5] = {6,5,4,3,3}; // in powers of 2
char input_buffer[4];
int  input_history[5];
void input_task(){
	ulong now = millis();
	if(now - input_time >= INPUT_REC) {
		input_time = now;

		// fgets will return error (null) if no input was provided
		// so the previous input will be used
		void* out = fgets(input_buffer, 4, stdin);
		no_input = (out == NULL);

		// move all items one over
		for (int i=3; i>=0; --i) {
			input_history[i+1] = input_history[i];
		}
		// input_history[0] == input_history[1]
		// the history always moves along, othwerwise, due to
		// weighted average the motor will never reach the inputed
		// speed umless it keeps getting re-inputed

		if(!no_input){
			// saturation
			char* end;
			int input = strtol(input_buffer,&end,10); 
			
			conv_fail = (end == input_buffer);

			if (!conv_fail){
				underflow = input <   0;
				if(underflow) { input =   0; }

				overflow = input > 255;
				if(overflow) { input = 255; }

				input_history[0] = input;
			}
		} else {
			conv_fail = false;
		}

		// there's no need for impulse noise filter for serial input

		// weighted average
		int avg = 0;
		for(int i=0; i<5; ++i){ avg += input_history[i] << weights[i]; }
		avg >>= 7;

		int target = avg;

		// TODO: controll fan based on data
	}
}

#define TEMP_REC 100
void temp_task() {
    ulong now = millis();
    if (now - temp_time >= TEMP_REC) {
        temp_time = now;
        dht_read();
    }
}

// these are defined somewhere above this code: bool conv_fail, no_input, overflow,underflow; ulong report_time;
#define REPORT_REC 2000 //milis
void report_task(){

	ulong now = millis();
	if (now - report_time >= REPORT_REC) {
		report_time = now;
		printf("status: %s%s%s%s; speed: %d\n",
			conv_fail  ? "conv_fail "  : "",
			no_input && encoder_input  ? "encoder_input "   : 
	 			no_input ? "no_input": "",
			overflow   ? "overflow "   : "",
			underflow  ? "underflow "  : "",
	 		0 // TODO: put motor speed here
		);

		printf("Input history: {");
		for (int i =0; i<5; ++i) {
			printf("%d,", input_history[i]);
		}
		printf("}\n\n");
	}
}
