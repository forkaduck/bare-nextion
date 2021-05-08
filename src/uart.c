#include <limits.h>

#include "stm32f1xx.h"

#include "queue.h"
#include "uart.h"

struct queue g_uart1_output;
struct queue g_uart1_input;

void USART1_IRQHandler()
{
	/* if some error occurred, discard the rx byte*/
	if (USART1->SR &
	    (USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE)) {
		return;
	}

	/* check if the receive register is not empty */
	if (USART1->SR & USART_SR_RXNE) {
		queue_append_char(&g_uart1_input, USART1->DR);
	}

	/* check if the transmit register is empty*/
	if (USART1->SR & USART_SR_TC) {
		char temp;

		temp = queue_get_char(&g_uart1_output);
		if (temp != CHAR_MAX) {
			USART1->DR = temp;
		} else {
			/* if queue is empty, unset sending */
			USART1->SR &= ~USART_SR_TC;
		}
	}
}

void uart1_init(const uint_fast32_t baud, const uint_fast32_t sysclock)
{
	/* reset queues */
	queue_reset(&g_uart1_input);
	queue_reset(&g_uart1_output);

	/* enable clock for usart1 */
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

	/* set PA10 input floating and PA9 pushpull */
	GPIOA->CRH = ((0x4 << (4 * 2)) | (0xb << 4));

	/* receive / transmit interrupt enable, receive / transmit enable */
	USART1->CR1 =
		USART_CR1_RXNEIE | USART_CR1_TCIE | USART_CR1_TE | USART_CR1_RE;

	/* reset control register 2 & 3 to make sure nothing set the registers */
	USART1->CR2 = 0x0000;
	USART1->CR3 = 0x0000;

	/* set baud like the example 8Mhz / 16 * 9600b/s = 52.08333 */
	USART1->BRR = (sysclock / (16 * baud)) << 4;

	/* Enable IRQ */
	NVIC_SetPriority(USART1_IRQn, 1);
	NVIC_ClearPendingIRQ(USART1_IRQn);
	NVIC_EnableIRQ(USART1_IRQn);

	/* enable uart1 unit */
	USART1->CR1 |= USART_CR1_UE;
}

inline void uart1_send_str(const char out[], size_t size)
{
	size_t i;

	for (i = 0; i < size; i++) {
		queue_append_char(&g_uart1_output, out[i]);
	}
	USART1_IRQHandler();
}
