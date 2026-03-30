#include <Arduino.h>
#include "leds.h"

#define RED_LED 2
#define GREEN_LED 12

void init_leds(){
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);

  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
}

void toggle_red(){ 
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);

}
void toggle_green(){ 
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RED_LED,LOW);
}
