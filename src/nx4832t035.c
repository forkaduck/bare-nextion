#include <stddef.h>

#include "stm32f1xx.h"

#include "nx4832t035.h"
#include "uart.h"

struct display_event d_events[DISPLAY_EVENT_SIZE];

size_t display_read(char out[], const size_t out_size)
{
	size_t i = 0;
	size_t ff_count = 0;

	volatile size_t prev_read;
	char rv = 0;

	prev_read = g_uart1_input.read_offset;

	for (i = 0; i < out_size; i++) {
		rv = queue_get_char(&g_uart1_input);

		if (rv == QUEUE_EMPTY) {
			break;
		}

		if (rv == 0xff) {
			ff_count++;

		} else {
			out[i] = rv;
		}

		if (ff_count > 2) {
			return i - ff_count;
		}
	}
	g_uart1_input.read_offset = prev_read;

	return 0;
}

inline void display_send(const char instruction[], size_t size)
{
	const char surfix[3] = { 0xff, 0xff, 0xff };

	uart1_send_str(instruction, size);
	uart1_send_str(surfix, 3);
}

void display_event_init()
{
	size_t i;

	for (i = 0; i < DISPLAY_EVENT_SIZE; i++) {
		d_events[i].event_type = 0;
		d_events[i].handler = NULL;
	}
}

void display_event_loop()
{
	size_t i;
	size_t size;
	char temp[QUEUE_SIZE];

	size = display_read(temp, QUEUE_SIZE);
	if (size == 0) {
		return;
	}

	for (i = 0; i < DISPLAY_EVENT_SIZE; i++) {
		if (d_events[i].event_type == temp[0]) {
			d_events[i].handler(temp, size);
		}
	}
}
