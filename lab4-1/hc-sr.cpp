#include "hc-sr.h"
#include <Arduino.h>

float g_distance    = 0.0f;
 bool g_dist_alert  = false;
  int g_dist_persist= 0;

// for string formatting
char buf[8];

float hcsr_read(){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL); // 30ms timeout ~= 5m max
    g_distance = duration / 58.0f;
    if (duration == 0) g_distance -= 1.0f;                  // timeout = out of range
    return g_distance;
}

void process_distance(){
    float dist = g_distance;
    if (dist < 0) { g_dist_persist = 0; return; }     // ignore invalid reads

    const float THRESH_NEAR = DIST_THRESHOLD - DIST_HYSTERESIS;
    const float THRESH_FAR  = DIST_THRESHOLD + DIST_HYSTERESIS;

    if (dist < THRESH_NEAR && !g_dist_alert) {
        if (++g_dist_persist >= DIST_PERSIST_REQUIRED) {
            g_dist_alert  = true;
            g_dist_persist = 0;
        }
    } else if (dist > THRESH_FAR && g_dist_alert) {
        if (++g_dist_persist >= DIST_PERSIST_REQUIRED) {
            g_dist_alert  = false;
            g_dist_persist = 0;
        }
    } else {
        g_dist_persist = 0;
    } 
}

void hcsr_init(){
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void report_distance(){

    printf("Distance    : %s cm\r\n",  dtostrf(g_distance,     5, 1, buf));
    printf("Dist Thresh : %s cm\r\n",  dtostrf(DIST_THRESHOLD, 5, 1, buf));
    printf("Dist State  : %s\r\n",     g_dist_alert ? "!!! TOO CLOSE !!!" : "NORMAL");
}

