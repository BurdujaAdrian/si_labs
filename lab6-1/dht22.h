#pragma once
#include <DHT.h>
#include "conditioning.h"

#define DHT_PIN            10
#define DHT_TYPE           DHT22


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

extern int g_temp_pos, g_temp_cnt;
extern int g_humi_pos, g_humi_cnt;

RawData dht_read();
void process_threshold();
void report_temperature(unsigned long now);


ConditionResults dht_condition_humi();
ConditionResults dht_condition_temp();
