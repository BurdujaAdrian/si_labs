#include <stdio.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "stdio_layer.h"
#include "keypad_driver.h"

#define LCD_ADDR 0x27
LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4);

FILE lcd_str ; 
int lcd_putchar(char c, FILE *stream) {
    (void)stream;
    if (c == '\n') {
        lcd.clear();
        lcd.setCursor(0, 0);
    } else {
        lcd.print(c);
    }
    return 0;
}

// keypad portion
FILE kp_str;
int kp_getchar(FILE *stream){
  (void)stream;
  return keypad_read();
}


void init_stdio(){ 

  lcd.init();
  lcd.backlight();
  fdev_setup_stream(&kp_str, NULL, kp_getchar, _FDEV_SETUP_READ);
  fdev_setup_stream(&lcd_str, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &lcd_str;
  stdin = &kp_str;
}
