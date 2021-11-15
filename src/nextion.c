/** @file
 *  @brief Contains most of the user facing functions for use with the displays.
*/

#include <stddef.h>

#include "stm32f1xx.h"

#include "nextion.h"
#include "uart.h"

struct display_event g_devents[DISPLAY_EVENT_SIZE];

size_t display_read(char out[], const size_t out_size)
{
	size_t i = 0;
	size_t ff_count = 0;

	volatile size_t prev_read;
	char rv = 0;

	/* safe previous queue offset to be able to restore it later */
	prev_read = g_uart_input.read_offset;

	for (i = 0; i < out_size; i++) {
		rv = queue_get_char(&g_uart_input);

		if (rv == QUEUE_EMPTY) {
			break;
		}

		if (rv == 0xff) {
			ff_count++;

		} else {
			out[i] = rv;
		}

		/* wait for 3 0xff and then stop */
		if (ff_count > 2) {
			return i - (ff_count - 1);
		}
	}

	/* reset the queue if no chars were read */
	g_uart_input.read_offset = prev_read;

	return 0;
}

inline void display_send(const char instruction[], size_t size)
{
	const char surfix[3] = { 0xff, 0xff, 0xff };

	uart_send_str(instruction, size);
	uart_send_str(surfix, 3);
}

void display_event_init()
{
	size_t i;

	for (i = 0; i < DISPLAY_EVENT_SIZE; i++) {
		g_devents[i].event_type = 0;
		g_devents[i].handler = NULL;
	}

	/* increment loglevel of the display to catch all errors and success messages */
	display_send("bkcmd=3", 7);
}

uint8_t display_event_loop()
{
	size_t i;
	size_t size;
	char temp[QUEUE_SIZE];

	size = display_read(temp, QUEUE_SIZE);
	if (size == 0) {
		return UINT8_MAX;
	}

	/* if the retuned code is not an error call the handler function */
	if (temp[0] > DISPLAY_LAST_ERR) {
		for (i = 0; i < DISPLAY_EVENT_SIZE; i++) {
			if (g_devents[i].event_type == temp[0]) {
				g_devents[i].handler(temp, size);
				break;
			}
		}
	} else {
		return temp[0];
	}
	return UINT8_MAX;
}
