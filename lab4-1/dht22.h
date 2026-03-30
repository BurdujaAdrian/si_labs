#pragma once
#include <DHT.h>

#define DHT_PIN            10
#define DHT_TYPE           DHT22

#define ACQUIRE_INTERVAL   2000UL
#define REPORT_INTERVAL    500UL

#define TEMP_THRESHOLD     25.0f
#define TEMP_HYSTERESIS     1.0f
#define PERSIST_REQUIRED    3

struct RawData {
    float temperature;
    float humidity;
    bool  valid;
};

extern DHT dht; 

extern RawData    g_data       ;
extern bool       g_is_alert   ;
extern int        g_persist    ;


RawData dht_read();
void process_threshold();
void report_temperature(unsigned long now);
