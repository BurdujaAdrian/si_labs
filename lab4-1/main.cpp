#include <Arduino.h>
#include "stdio_layer.h"
#include "dht22.h"
#include "hc-sr.h"

int main() {
    init();

    stdio_init();

    dht.begin();
    hcsr_init();

    printf("=== DHT22 Temperature Monitor (Mega) ===\r\n");

    unsigned long lastAcquire = 0;
    unsigned long lastReport  = 0;

    for (;;) {
        unsigned long now = millis();

        if (now - lastAcquire >= ACQUIRE_INTERVAL) {
            lastAcquire = now;
            RawData data = dht_read();
            float dist = hcsr_read();
            if (data.valid) { process_threshold(); }
            if (dist >= 0) { process_distance(); }
        }

        if (now - lastReport >= REPORT_INTERVAL) {
            lastReport = now;
            report_temperature(now);
            report_distance();
        }


    }

    return 0;
}
