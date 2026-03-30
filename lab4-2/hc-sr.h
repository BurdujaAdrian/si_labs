#pragma once
#include "conditioning.h"

#define TRIG_PIN              3
#define ECHO_PIN              2

#define DIST_THRESHOLD       20.0f   // cm
#define DIST_HYSTERESIS       2.0f   // ±cm  → alert below 18, clear above 22
#define DIST_PERSIST_REQUIRED 3

#define HCSR_T_MIN -40
#define HCSR_T_MAX  80

extern float g_distance    ;
extern  bool g_dist_alert  ;
extern   int g_dist_persist;

float hcsr_read();
void process_distance();
void report_distance();
ConditionResults hcsr_condition_dist();

void hcsr_init();
