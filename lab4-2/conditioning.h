#pragma once

#define MEDIAN_WINDOW 5

struct ConditionResults {
    float raw,saturated,median,weighted;
};

ConditionResults condition_value(float raw, float min_sat, float max_sat, float window[], int *window_pos, int *window_count);
