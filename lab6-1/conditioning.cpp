#include "conditioning.h"
#include <Arduino.h>

static float saturate(float val, float mn, float mx) {
    if (val < mn) return mn;
    if (val > mx) return mx;
    return val;
}

static float median(float window[], int count) {
    float buff[MEDIAN_WINDOW];
    memcpy(buff, window, count * sizeof(float));

    for (int i = 1; i < count; i++) {
        float key = buff[i];
        int j = i - 1;
        while (j >= 0 && buff[j] > key) { buff[j+1] = buff[j]; j--; }
        buff[j+1] = key;
    }

    return buff[count / 2];
}

static float weighted(float window[], int pos, int count) {
    float sum = 0, weight = 0;
    for (int i = 0; i < count; i++) {
        int   p = (pos + i) % count;
        float w = (float)(i + 1);
        sum    += window[p] * w;
        weight += w;
    }
    return sum / weight;
}

ConditionResults condition_value(
    float raw,
    float min_sat, float max_sat,
    float window[], int *window_pos, int *window_count
) {
    ConditionResults res = {};
    res.raw       = raw;
    res.saturated = saturate(raw, min_sat, max_sat);

    window[*window_pos] = res.saturated;
    *window_pos         = (*window_pos + 1) % MEDIAN_WINDOW;
    if (*window_count < MEDIAN_WINDOW) (*window_count)++;

    res.median   = median(window, *window_count);
    res.weighted = weighted(window, *window_pos, *window_count);

    return res;
}
