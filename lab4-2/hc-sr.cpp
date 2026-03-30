#include "hc-sr.h"
#include "conditioning.h"
#include <Arduino.h>

char hcsr_buf[8];

float g_distance   = 0.0f;
bool  g_dist_alert = false;
int   g_dist_persist = 0;

float g_dists[MEDIAN_WINDOW];
int   g_dist_pos = 0, g_dist_cnt = 0;

float hcsr_read() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
    if (duration == 0) { g_distance = -1.0f; return g_distance; }
    g_distance = duration / 58.0f;
    return g_distance;
}

ConditionResults hcsr_condition_dist() {
    if (g_distance < 0) return ConditionResults{};
    return condition_value(g_distance, 2, 400, g_dists, &g_dist_pos, &g_dist_cnt);
}

void process_distance() {
    float dist = g_distance;
    if (dist < 0) { g_dist_persist = 0; return; }

    const float THRESH_NEAR = DIST_THRESHOLD - DIST_HYSTERESIS;
    const float THRESH_FAR  = DIST_THRESHOLD + DIST_HYSTERESIS;

    if (dist < THRESH_NEAR && !g_dist_alert) {
        if (++g_dist_persist >= DIST_PERSIST_REQUIRED) { g_dist_alert = true;  g_dist_persist = 0; }
    } else if (dist > THRESH_FAR && g_dist_alert) {
        if (++g_dist_persist >= DIST_PERSIST_REQUIRED) { g_dist_alert = false; g_dist_persist = 0; }
    } else { g_dist_persist = 0; }
}

void hcsr_init() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void report_distance() {
    printf("Distance    : %s cm\r\n", dtostrf(g_distance,     5, 1, hcsr_buf));
    printf("Dist Thresh : %s cm\r\n", dtostrf(DIST_THRESHOLD, 5, 1, hcsr_buf));
    printf("Dist State  : %s\r\n",    g_dist_alert ? "!!! TOO CLOSE !!!" : "NORMAL");
}
