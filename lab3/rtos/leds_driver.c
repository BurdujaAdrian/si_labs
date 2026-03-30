#include "leds_driver.h"
#include <Arduino.h>

// Register controll
#define RED_LED_PIN 12
#define GREEN_LED_PIN 13
#define YL_LED_PIN 30

void init_leds(){
	pinMode(RED_LED_PIN,   OUTPUT);
	pinMode(GREEN_LED_PIN, OUTPUT);
	pinMode(YL_LED_PIN,    OUTPUT);

	yl_led_turn_off();
	red_led_turn_off();
	green_led_turn_off();
}

void red_led_turn_on()  { digitalWrite(RED_LED_PIN,HIGH); }
void red_led_turn_off() { digitalWrite(RED_LED_PIN, LOW); }

void green_led_turn_on()  { digitalWrite(GREEN_LED_PIN,HIGH); }
void green_led_turn_off() { digitalWrite(GREEN_LED_PIN, LOW); }

void yl_led_turn_on()  { digitalWrite(YL_LED_PIN,HIGH); }
void yl_led_turn_off() { digitalWrite(YL_LED_PIN, LOW); }
