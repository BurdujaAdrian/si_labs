#include <Arduino.h>
#include <stdio.h>
#include "stdio_layer.h"
#include "leds.h"
#include "keypad_driver.h"

int main(void){
  init();
  
  init_stdio();
  init_leds();
  init_keypad();

  // input buffer
  char input[255] = {};
  int i = 0;
  for(;;){
    // read the keypress
    input[i] = getchar();
    putchar(input[i]);

    // wrapping increment
    i = (i+1)%255;
    
    if (input[i-1] == '#') {
        // end the cstring
        input[i] = '\0';

        // string compare with the password
        if (strcmp(input,"1234#") == 0) {
          toggle_green();
          printf("\nCorrect password");
        } else {
          toggle_red();
          printf("\nIncorrect password");
        }

        // keep displaying the messege for a second
        delay(1000);

        // reset
        putchar('\n');
        i = 0;
    }

    // debaunce
    delay(100);
  }

  return 0;
}
