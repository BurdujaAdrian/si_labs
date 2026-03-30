#pragma  once
#include <stdio.h>

typedef struct {
	uint8_t cnt;
	uint8_t offset;
	uint8_t rec;
} context_t;

typedef void context_proc(void);

typedef struct{
	context_t context;
	context_proc* proc;
} task_t ;
enum {
	TASK_1 = 0,
	TASK_2,
	TASK_3,
	TASK_N
};


void task1_proc(void);
void task2_proc(void);
void task3_proc(void);

void init_tasks(task_t *tasks);
