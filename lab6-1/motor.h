#pragma once

#define MOTOR_PIN 6

void motor_setup();
void motor_set_speed(int val);
unsigned int motor_get_speed();
void motor_switch_pwm();
