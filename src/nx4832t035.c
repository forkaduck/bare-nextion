#include <stddef.h>

#include "stm32f1xx.h"

#include "nx4832t035.h"
#include "uart.h"

struct display_event d_events[DISPLAY_EVENT_SIZE];

size_t display_read(char out[], const size_t out_size)
{
	size_t i = 0;
	size_t ff_count = 0;

	volatile char *prev_read;

	prev_read = g_uart1_input.read_offset;

	while (g_uart1_input.write_offset != g_uart1_input.read_offset &&
	       out_size > i) {
		out[i] = queue_get_char(&g_uart1_input);

		if (out[i] == 0xff) {
			ff_count++;
		}

		if (ff_count > 2) {
			return i;
		}

		i++;
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

	size = display_read(temp, 100);
	if (size == 0) {
		return;
	}

	for (i = 0; i < DISPLAY_EVENT_SIZE; i++) {
		if (d_events[i].event_type == temp[0]) {
			d_events[i].handler(temp);
		}
	}
}
