#include <stddef.h>

#include "nx4832t035.h"
#include "uart.h"

inline void display_send(const char instruction[], size_t size)
{
	const char surfix[] = { 0xff, 0xff, 0xff };
	const size_t surfix_size = 3;

	uart1_send_str(instruction, size);
	uart1_send_str(surfix, surfix_size);
}

size_t display_read(char out[], const size_t out_size)
{
	uint8_t ff_counter = 0;
	size_t i;
	volatile char *prev_read;

	prev_read = g_uart1_input.read_offset;

	for (i = 0; i < out_size - 1; i++) {
		if (ff_counter >= 3) {
			out[i] = '\0';
			return i;
		}

		out[i] = queue_get_char(&g_uart1_input);
		switch (out[i]) {
		case 0xff:
			ff_counter++;
			break;

		case 0x00:
			return 0;
		}
	}

	g_uart1_input.read_offset = prev_read;
	return 0;
}
