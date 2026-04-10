#pragma once

extern volatile int encoder_delta;

void encoder_setup();
int  encoder_read();
