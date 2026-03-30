#include "dht22.h"
#include <Arduino.h>

DHT dht(DHT_PIN, DHT_TYPE);


RawData    g_data       = { 0, 0, false };
bool       g_is_alert   = false;
int        g_persist    = 0;


RawData dht_read() {
    g_data.temperature = dht.readTemperature();
    g_data.humidity    = dht.readHumidity();
    g_data.valid       = !isnan(g_data.temperature) && !isnan(g_data.humidity);
    return g_data;
}

void process_threshold() {
    float temp = g_data.temperature;
    const float high_thresh = TEMP_THRESHOLD + TEMP_HYSTERESIS;
    const float low_thresh  = TEMP_THRESHOLD - TEMP_HYSTERESIS;

    if (g_is_alert == false) {
        if (temp > high_thresh) {
            if (++g_persist >= PERSIST_REQUIRED) { g_is_alert = true;  g_persist = 0; }
        } else {
            g_persist = 0;
        }
    } else {
        if (temp < low_thresh) {
            if (++g_persist >= PERSIST_REQUIRED) { g_is_alert = false; g_persist = 0; }
        } else {
            g_persist = 0;
        }
    }
}

void report_temperature(unsigned long now) {
    char buf[8];

    printf("------------------------------\r\n");
    printf("Uptime (ms) : %lu\r\n", now);

    if (!g_data.valid) {
        printf("Sensor      : READ ERROR\r\n");
        return;
    }

    printf("Temperature : %s C\r\n",         dtostrf(g_data.temperature, 5, 1, buf));
    printf("Humidity    : %s %%\r\n",         dtostrf(g_data.humidity,    5, 1, buf));
    printf("Threshold   : %s C  +/-",         dtostrf(TEMP_THRESHOLD,     5, 1, buf));
    printf("%s C\r\n",                         dtostrf(TEMP_HYSTERESIS,    4, 1, buf));
    printf("Persist     : %d/%d\r\n",          g_persist, PERSIST_REQUIRED);
    printf("State       : %s\r\n",             g_is_alert == true ? "!!! ALERT !!!" : "NORMAL");
}
