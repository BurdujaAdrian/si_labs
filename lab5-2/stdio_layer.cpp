#include "stdio_layer.h"
#include "HardwareSerial.h"
#include "stdio.h"
#include <Arduino.h>

static int serial_getchar(FILE *) {
    if (!Serial.available()) {
        return _FDEV_EOF;
    }
    int c = Serial.read();
    if (c == '\r') return '\n';
    return c;
}

static int serial_putchar(char c, FILE *){
    return Serial.write(c);
}

static FILE serial_stdio;

void stdio_init() {
    fdev_setup_stream(&serial_stdio, serial_putchar, serial_getchar, _FDEV_SETUP_RW);
    stdin = &serial_stdio;
    stdout = &serial_stdio;
    Serial.begin(9600);
}
