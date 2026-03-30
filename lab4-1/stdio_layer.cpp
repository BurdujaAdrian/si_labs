#include "stdio_layer.h"
#include "HardwareSerial.h"
#include <Arduino.h>

static int serial_putchar(char c, FILE *) {
    Serial.write(c);
    return 0;
}

static FILE g_stdout;

void stdio_init() {
    fdev_setup_stream(&g_stdout, serial_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &g_stdout;
    Serial.begin(9600);
}
