#pragma once

#define MAX_STACK 255

typedef struct {
	unsigned long els[MAX_STACK]; 
	int  idx;
}Button_deltas;

void push(Button_deltas *stack, unsigned long in_item);
unsigned long pop(Button_deltas *stack);
