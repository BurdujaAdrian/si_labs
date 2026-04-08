#include "stdio_layer.h"
#include "stdio.h"
#include <Arduino.h>

static int serial_getchar(FILE *) {
    if (Serial.available()) {
        return _FDEV_EOF;
    }
    return Serial.read();
}

static FILE serial_stdin;

void stdio_init() {
    fdev_setup_stream(&serial_stdin, NULL, serial_getchar, _FDEV_SETUP_READ);
    stdin = &serial_stdin;
    Serial.begin(9600);
}
