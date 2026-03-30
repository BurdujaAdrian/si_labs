#include "leds_driver.h"
#include <Arduino.h>

// Register controll
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define YL_LED_PIN 11

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

#define BLINK_LEN 100

int blink_counter = 0;
int blink = LOW;
bool executing;
void yl_exec_blink(){
	if (blink_counter == 0) { return; }

	int now = millis();
	if(now % 100 == 0){
		blink = blink? LOW:HIGH;
		blink_counter -=1;
	}
	
	digitalWrite(YL_LED_PIN, blink );
}

void yl_setup_blink(int n){
	blink_counter = n*2;
}


