#include "queue.h"

void push(Button_deltas *stack, unsigned long in_item) {
	stack->els[stack->idx] = in_item;       
	stack->idx = (stack->idx+1) % MAX_STACK;
}

unsigned long pop(Button_deltas *stack){
	stack->idx = (stack->idx+MAX_STACK - 1) % MAX_STACK;
	return stack->els[stack->idx];                  
}
