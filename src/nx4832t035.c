#include <stddef.h>

#include "nx4832t035.h"
#include "uart.h"

void display_send(const char instruction[], size_t size)
{
	const char surfix[] = { 0xff, 0xff, 0xff };
	const size_t surfix_size = 3;

	uart1_send_str(instruction, size);
	uart1_send_str(surfix, surfix_size);
}
