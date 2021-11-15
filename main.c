#include "stm32f103xb.h"
#include <stddef.h>
#include <limits.h>
#include "stm32f1xx.h"

#include "nextion.h"
#include "uart.h"

/// bit_word_addr = bit_band_base + (byte_offset * 32) + (bit_number * 4)
#define BB_PERIPH(byteoff, bitnum)                                             \
	(PERIPH_BB_BASE + (byteoff - PERIPH_BASE) * 32 + (bitnum * 4))

/// Simplified macro to get a pointer to a bit representing a pin
#define BB_GET_PIN(baseaddr, regoffset, bit)                                   \
	*((volatile uint32_t *)(BB_PERIPH(                                     \
		baseaddr + regoffset * sizeof(uint32_t), bit)))

/// Heartbeat led (unused on the motor pcb)
#define LEDS(x) BB_GET_PIN(GPIOB_BASE, 3, (x + 8))

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

/* a rather slow memset implementation that doesn't use libc */
static inline void memset(void *dest, uint8_t num, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++) {
		((uint8_t *)dest)[i] = num;
	}
}

static inline size_t strlen_s(char *str, size_t size)
{
	size_t i = 0;

	while (*str != '\0' && i < size) {
		i++;
		str++;
	}
	return i;
}

static inline void strcat_s(char *str1, size_t str1_max, char *str2,
			    size_t str2_max)
{
	size_t i;
	size_t str1_size = strlen_s(str1, str1_max);
	size_t str2_size = strlen_s(str2, str2_max);

	if (str1_max < str1_size + str2_size) {
		return;
	}

	for (i = 0; i < str2_size; i++) {
		if (str2_max > i) {
			str1[i + str1_size] = str2[i];
		}
	}
}

static inline void *memcpy(void *dest, const void *src, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++) {
		((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
	}
	return dest;
}

char *itoa_x(int number, char *dest, size_t dest_size, int base)
{
	if (dest == NULL || base < 2 || base > 36) {
		return NULL;
	}

	char buf[sizeof number * CHAR_BIT +
		 2]; /* worst case: itoa(INT_MIN,,,2) */
	char *p = &buf[sizeof buf - 1];

	/* Work with negative absolute value to avoid UB of `abs(INT_MIN)` */
	int neg_num = number < 0 ? number : -number;

	/* Form string */
	*p = '\0';
	do {
		*--p = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[-(neg_num % base)];
		neg_num /= base;
	} while (neg_num);
	if (number < 0) {
		*--p = '-';
	}

	/* Copy string */
	size_t src_size = (size_t)(&buf[sizeof buf] - p);
	if (src_size > dest_size) {
		/* Not enough room */
		return NULL;
	}
	return memcpy(dest, p, src_size);
}

#pragma GCC diagnostic pop

static void wait_ms(int ms)
{
	uint16_t i, j;

	for (i = 0; i < ms; i++) {
		for (j = 0; j < 14355 / 2; j++) {
		}
	}
}

void touch_event(char out[], size_t size)
{
	struct D_TOUCH_EVENT touch;

	if (size >= sizeof(struct D_TOUCH_EVENT)) {
		memcpy(&touch, out + 1, sizeof(struct D_TOUCH_EVENT));

		/* choose between the different buttons */
		switch (touch.component_id) {
		case 0x1:
			if (touch.event == D_PRESS) {
				LEDS(7) = 1;
			} else {
				LEDS(7) = 0;
			}
			break;

		case 0x2:
			if (touch.event == D_PRESS) {
				LEDS(6) = 1;
			} else {
				LEDS(6) = 0;
			}
			break;
		}
	}
}

void num_event(char out[], size_t size)
{
	struct D_NUM num;

	if (size >= sizeof(struct D_NUM)) {
		memcpy(&num, out + 1, sizeof(struct D_NUM));

		/* dim the display using the number returned from the get request */
		char temp[20];
		char out[20] = { "dim=" };

		itoa_x(num.num, temp, 20, 10);
		strcat_s(out, 20, temp, 20);
		display_send(out, 20);

		LEDS(5) = !LEDS(5);
	}
}

void ready_event(char out[], size_t size)
{
	LEDS(1) = 1;
}

int main()
{
	size_t counter;

	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRH = 0x33333333;

	/* setup uart1 */
	uart_init(115200, 72000000);

	/* setup some events and init the event handler  */
	display_event_init();

	/* on touch of some button */
	g_d_events[0].event_type = D_TOUCH_EVENT;
	g_d_events[0].handler = touch_event;

	/* on a number received */
	g_d_events[1].event_type = D_NUM;
	g_d_events[1].handler = num_event;

	/* on startup of the display */
	g_d_events[2].event_type = D_READY;
	g_d_events[2].handler = ready_event;

	counter = 0;
	while (1) {
		if (counter == 10) {
			display_send("get h0.val", 10);
			counter = 0;

			/* send an invalid command */
			display_send("t1.val=\"dingdong\"", 20);
			if (display_clear_err() != UINT8_MAX) {
				LEDS(0) = 1;
			}
		}

		/* run 1 event handler per call */
		display_event_loop();

		wait_ms(1);
		counter++;
	}
	return 0;
}
