#include <Arduino.h>


int main(void){
  init();
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  for(;;){
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);

      delay(100);
  }

  return 0;
}
