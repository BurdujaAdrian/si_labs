#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdio.h>

#include "Arduino.h"

#include "task_procs.h"
#include "button_driver.h"
#include "leds_driver.h"
#include "stdio_layer.h"

typedef struct {
	unsigned long sum_shorts,sum_longs;
	int presses, n_shorts,n_longs;
}stats_t ;

QueueHandle_t duration_queue;
QueueHandle_t stats_queue;
void init_tasks(){
	init_button();
	init_leds();
	init_stdout();

	duration_queue = xQueueCreate(10,sizeof(unsigned long));
	stats_queue = xQueueCreate(10,sizeof(stats_t));

	xTaskCreate(task1_proc, "Task1", 128, NULL, 2, NULL);
	xTaskCreate(task2_proc, "Task2", 128, NULL, 1, NULL);
	xTaskCreate(task3_proc, "Task3", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}

// manage press intervals
void task1_proc(void* pvParameters){
	(void)pvParameters;

	for (;;){
		// while button has not been pressed, wait
		while (button_state() == HIGH ) { vTaskDelay(1); }
		
		unsigned long start = millis();

		// while the button is still held, wait
		while (button_state() == LOW) { vTaskDelay(1); }

		unsigned long finish = millis();
		unsigned long duration = finish - start;

		// notify task2 that there is data to consume
		//		//xQueueSend copies the data internally
		xQueueSend(duration_queue, &duration, 0);

		if (duration < 500){
			// short hold
			green_led_turn_on();
			red_led_turn_off();
		} else {
			// long hold
			red_led_turn_on();
			green_led_turn_off();
		}
	}
}

#define LONG_PRESS 500
// manage press statistics
void task2_proc(void* pvParameters){
	(void)pvParameters;

	for (;;){
		unsigned long duration = 0;

		xQueueReceive(duration_queue, &duration,portMAX_DELAY);

		// process the input
		stats_t stats = {0}; 
		stats.presses +=1;
		int blink_n = 0;
		if (duration < LONG_PRESS) {
			stats.sum_shorts += duration;
			stats.n_shorts += 1;
			blink_n = 5;
		} else {
			stats.sum_longs += duration;
			stats.n_longs += 1;
			blink_n = 10;
		}

		xQueueSend(stats_queue, &stats, 0);

		// blink blink_n times
		for (/**/; blink_n>0; blink_n-=1) {
			yl_led_turn_on();
			vTaskDelay(pdMS_TO_TICKS(100));
			yl_led_turn_off();
			vTaskDelay(pdMS_TO_TICKS(100));
		}

	}
}


#define REPORT_INTERVAL 10

void task3_proc(void* pvParameters){
	(void)pvParameters;

	for(;;){
		vTaskDelay(pdMS_TO_TICKS(REPORT_INTERVAL*1000));

		stats_t total_stats = {0};
		BaseType_t recieved;

		// process all the items in the queue imediately
		do {
			stats_t stats = {0}; 
			recieved = xQueueReceive(stats_queue, &stats, 0);
			total_stats.presses += stats.presses;
			total_stats.n_longs += stats.n_longs;
			total_stats.n_shorts += stats.n_shorts;
			total_stats.sum_longs += stats.sum_longs;
			total_stats.sum_shorts += stats.sum_shorts;
		
		}while (recieved != pdFALSE);
		


		unsigned long averege_holds = total_stats.sum_longs + total_stats.sum_shorts;
		
		if (total_stats.presses > 0) {
			averege_holds = averege_holds / (total_stats.presses);
		}


		printf(
			"Numarul de apasari: %d\n"
			"Numarul de apasari scurte: %d\n"
			"Numarul de apasari lungi:  %d\n"
			"Durata medie a apasarilor: %lu\n",
			total_stats.presses,
			total_stats.n_shorts,
			total_stats.n_longs,
			averege_holds
		);

	}
}
