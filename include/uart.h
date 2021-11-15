/** @file
 *  @brief Contains some uart hardware abstraction functions.
*/
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "queue.h"

// bit_word_addr = bit_band_base + (byte_offset * 32) + (bit_number * 4)
#define BB_PERIPH(byteoff, bitnum)                                             \
	(PERIPH_BB_BASE + (byteoff - PERIPH_BASE) * 32 + (bitnum * 4))

extern struct queue g_uart_input;

/**
 * @brief Initialize UART1.
 * @param baud The baud rate of UART1 to be used.
 * @param sysclock The system clock in Hz.
 */
void uart_init(const uint_fast32_t baud, const uint_fast32_t sysclock);

/**
 * @brief Sends a null terminated string over UART.
 * @param out A char array to be sent.
 * @param size The maximum size of the char array.
 */
void uart_send_str(const char out[], size_t size);

/**
 * @brief Sends out one char.
 * @param out The char to be sent.
 */
void uart_send_char(const char out);
