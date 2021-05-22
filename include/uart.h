#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "queue.h"

// bit_word_addr = bit_band_base + (byte_offset * 32) + (bit_number * 4)
#define BB_PERIPH(byteoff, bitnum)                                             \
	(PERIPH_BB_BASE + (byteoff - PERIPH_BASE) * 32 + (bitnum * 4))

extern struct queue g_uart1_input;

// init uart1 interface and queue
void uart_init(const uint_fast32_t baud, const uint_fast32_t sysclock);
void uart_send_str(const char out[], size_t size);
void uart_send_char(const char out);
#endif
