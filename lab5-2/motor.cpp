#include "motor.h"
#include <Arduino.h>

void motor_setup(){ pinMode(MOTOR_PIN, OUTPUT); }

int speed = 0;

void motor_set_speed(int val){ speed = val; }
int motor_get_speed(){ return speed; }
void motor_switch_pwm(){ analogWrite(MOTOR_PIN, speed); }
