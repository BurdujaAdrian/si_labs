#include "tasks.h"
#include "Arduino.h"
#include "motor.h"
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long ulong;
ulong	motor_time,
	input_time,
	report_time;

// flags
bool conv_fail = false, no_input;

void tasks_init(){
	motor_time = millis() + 0;
	input_time = millis() + 1000;
	report_time =millis() + 2000; 
}

#define MOTOR_REC 1000 //milis
void motor_task(){
	ulong now = millis();
	if (now - motor_time >= MOTOR_REC) {
		motor_time = now;
		motor_switch_pwm();
	}
}

#define INPUT_REC 100 // milis

// unsigned long input_time; is actually defined above; ulong is alias for unsighend long
const int weights[5] = {7,6,5,5}; // in powers of 2
char input_buffer[4];
int  input_history[5];
void input_task(){
	ulong now = millis();
	if (now - input_time >= INPUT_REC) {
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
				if(input <   0) input =   0;
				if(input > 255) input = 255;

				input_history[0] = input;
			}
		} 


		// there's no need for impulse noise filter for stdio

		// weighted average
		int avg = 0;
		for(int i=0; i<5; ++i){ avg += input_history[i] << weights[i]; }
		avg >>= 8;

		// smooth acceleration
		int curr = motor_get_speed();
		/* a = dv / dt
		*  dv = a * dt
		*  a = 1 PWM / 20 millis
		*  ra = 1 / a = 20 millis / 1 PWN
		*  dv = dt / ra
		*/
		#define ra 20;
		int dv = 0;
		if (curr < avg) {
			// has to accelerate;
			dv = INPUT_REC / ra;
		} else if (curr > avg) {
			// has to decelerate;
			dv = - INPUT_REC / ra;
		}

		motor_set_speed(curr+dv);
	}
}

#define REPORT_REC 2000 //milis
void report_task(){
}
