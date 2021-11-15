
#include "stm32f103xb.h"
#include <stdint.h>

#include "stm32f1xx.h"

/* TODO
 * Global variables are not always initalized
 * */

// bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number × 4)
#define BB_PERIPH(byteoff, bitnum)                                             \
	((PERIPH_BB_BASE + (byteoff - PERIPH_BASE) * 32 + (bitnum * 4)))

// pb0
#define SOS                                                                    \
	*((volatile uint32_t *)(BB_PERIPH(GPIOA_BASE + 3 * sizeof(uint32_t),   \
					  5)))

// linker script section declarations
extern uint32_t _data_flash;
extern uint32_t _data_begin;
extern uint32_t _data_end;
extern uint32_t _bss_begin;
extern uint32_t _bss_end;
extern uint32_t _stack_end;
extern uint32_t _heap_start;
extern uint32_t _heap_end;

extern int main();

void Fault_Handler();

void __attribute__((weak)) NMI_Handler()
{
	Fault_Handler();
}

void __attribute__((weak)) HardFault_Handler()
{
	Fault_Handler();
}

void __attribute__((weak)) MemManage_Handler()
{
	Fault_Handler();
}

void __attribute__((weak)) BusFault_Handler()
{
	Fault_Handler();
}

void __attribute__((weak)) UsageFault_Handler()
{
	Fault_Handler();
}

void __attribute__((weak)) SVC_Handler()
{
	Fault_Handler();
}

void __attribute__((weak)) DebugMon_Handler()
{
	Fault_Handler();
}

void __attribute__((weak)) PendSV_Handler()
{
	Fault_Handler();
}

void __attribute__((weak)) SysTick_Handler()
{
	Fault_Handler();
}

// declare interrupt handlers
void __attribute__((weak)) WWDG_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) PVD_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TAMPER_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) RTC_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) FLASH_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) RCC_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) EXTI0_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) EXTI1_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) EXTI2_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) EXTI3_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) EXTI4_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA1_Channel1_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA1_Channel2_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA1_Channel3_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA1_Channel4_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA1_Channel5_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA1_Channel6_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA1_Channel7_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) ADC1_2_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) USB_HP_CAN1_TX_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) USB_LP_CAN1_RX0_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) CAN1_RX1_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) CAN1_SCE_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) EXTI9_5_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM1_BRK_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM1_UP_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM1_TRG_COM_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM1_CC_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM2_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM3_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM4_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) I2C1_EV_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) I2C1_ER_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) I2C2_EV_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) I2C2_ER_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) SPI1_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) SPI2_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) USART1_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) USART2_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) USART3_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) EXTI15_10_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) RTCAlarm_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) USBWakeUp_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM5_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) SPI3_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) UART4_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) UART5_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM6_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) TIM7_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA2_Channel1_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA2_Channel2_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA2_Channel3_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA2_Channel4_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) DMA2_Channel5_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) ETH_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) ETH_WKUP_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) CAN2_TX_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) CAN2_RX0_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) CAN2_RX1_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) CAN2_SCE_IRQHandler()
{
	Fault_Handler();
}

void __attribute__((weak)) OTG_FS_IRQHandler()
{
	Fault_Handler();
}

// reset handler gets called on reset exception
void Reset_Handler()
{
	{
		uint32_t *source;
		uint32_t *destination;

		// Copy data from Flash to RAM
		source = &_data_flash;
		for (destination = &_data_begin; destination < &_data_end;) {
			*(destination++) = *(source++);
		}
		// Zero bss region
		for (destination = &_bss_begin; destination < &_bss_end;) {
			*(destination++) = 0;
		}
	}

	// set flash latency
	FLASH->ACR = 0x12;

	// enable external oscilator and wait for it to stable
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) {
	}

	// Clock pipeline
	// 8MHz [HSE] -> x9 [PLL] -> 72MHz [SYSCLK] -> /1 [AHB/HPRE] -.-> /2 [APB1/PPRE1]
	//                                                            |-> /1 [APB2/PPRE2] -> /6 ADCPRE
	RCC->CFGR |= RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC | RCC_CFGR_SW_PLL |
		     RCC_CFGR_ADCPRE_DIV6 | RCC_CFGR_PPRE1_2 |
		     RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_HPRE_DIV1;

	// Enable and wait for clock
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY)) {
	}

	// run main function
	main();
}

static inline void wait_1u(uint32_t us)
{
	uint32_t i, j;
	for (i = 0; i < us; i++) {
		for (j = 0; j < 4; j++) {
		}
	}
}

void __attribute__((weak)) Fault_Handler()
{
	uint8_t i, j;
	uint16_t h;

	__disable_irq();
	__disable_fault_irq();

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	GPIOA->CRL = 0x00300000;

	SOS = 0x0;
	while (1) {
		// 3x short x2
		for (i = 0; i < 2; i++) {
			for (j = 0; j < 3; j++) {
				for (h = 0; h < 100; h++) {
					SOS = !SOS;
					wait_1u(1000);
				}
				SOS = 0x0;

				wait_1u(200 * 1000);
			}
			wait_1u(1000 * 1000);
		}

		// 3x long
		for (j = 0; j < 3; j++) {
			for (h = 0; h < 100; h++) {
				SOS = !SOS;
				wait_1u(1000);
			}
			SOS = 0x0;

			wait_1u(400 * 1000);
		}
	}
}

__attribute__((section(
	".interrupt_vector"))) void (*const table_interrupt_vector[])(void) = {
	(void (*const)(void)) & _stack_end, // 0 - stack
	// exceptions
	Reset_Handler, // 0x4 reset
	NMI_Handler, // 0x8 nmi
	HardFault_Handler, // 0xc Hard Fault
	MemManage_Handler, // 0x10 Mem Manage
	BusFault_Handler, // 0x14 Bus Fault
	UsageFault_Handler, // 0x18 Usage Fault
	0, // 0x1c reserved
	0, // 0x20 reserved
	0, // 0x24 reserved
	0, // 0x28 reserved
	SVC_Handler, // 0x2c SVCall
	DebugMon_Handler, // 0x30 Debug Monitor
	0, // 0x34 reserved
	PendSV_Handler, // 0x38 PendSV
	SysTick_Handler, // 0x3c SysTick

	// peripherals interrupts
	WWDG_IRQHandler, // 0x40 WWDG
	PVD_IRQHandler, // 0x44 PVD
	TAMPER_IRQHandler, // 0x48 TAMPER
	RTC_IRQHandler, // 0x4c RTC
	FLASH_IRQHandler, // 0x50 FLASH
	RCC_IRQHandler, // 0x54 RCC
	EXTI0_IRQHandler, // 0x58 EXTI0
	EXTI1_IRQHandler, // 0x5c EXT1
	EXTI2_IRQHandler, // 0x60 EXTI2
	EXTI3_IRQHandler, // 0x64 EXTI3
	EXTI4_IRQHandler, // 0x64 EXTI4
	DMA1_Channel1_IRQHandler, // 0x6c DMA1_Channel1
	DMA1_Channel2_IRQHandler, // 0x70 DMA1_Channel2
	DMA1_Channel3_IRQHandler, // 0x74 DMA1_Channel3
	DMA1_Channel4_IRQHandler, // 0x78 DMA1_Channel4
	DMA1_Channel5_IRQHandler, // 0x7c DMA1_Channel5
	DMA1_Channel6_IRQHandler, // 0x80 DMA1_Channel6
	DMA1_Channel7_IRQHandler, // 0x84 DMA1_Channel7
	ADC1_2_IRQHandler, // 0x88 ADC1_2
	USB_HP_CAN1_TX_IRQHandler, // 0x8c CAN1_TX
	USB_LP_CAN1_RX0_IRQHandler, // 0x90 CAN1_RX0
	CAN1_RX1_IRQHandler, // 0x94 CAN1_RX1
	CAN1_SCE_IRQHandler, // 0x98 CAN1_SCE
	EXTI9_5_IRQHandler, // 0x9c EXTI9_5
	TIM1_BRK_IRQHandler, // 0xa0 TIM1_BRK
	TIM1_UP_IRQHandler, // 0xa4 TIM1_UP
	TIM1_TRG_COM_IRQHandler, // 0xa8 TIM1_TRG_COM
	TIM1_CC_IRQHandler, // 0xac TIM1_CC
	TIM2_IRQHandler, // 0xb0 TIM2
	TIM3_IRQHandler, // 0xb4 TIM3
	TIM4_IRQHandler, // 0xb8 TIM4
	I2C1_EV_IRQHandler, // 0xbc I2C1_EV
	I2C1_ER_IRQHandler, // 0xc0 I2C1_ER
	I2C2_EV_IRQHandler, // 0xc4 I2C2_EV
	I2C2_ER_IRQHandler, // 0xc8 I2C2_ER
	SPI1_IRQHandler, // 0xcc SPI1
	SPI2_IRQHandler, // 0xd0 SPI2
	USART1_IRQHandler, // 0xd4 USART1
	USART2_IRQHandler, // 0xd8 USART2
	USART3_IRQHandler, // 0xdc USART3
	EXTI15_10_IRQHandler, // 0xe0 EXTI15_10
	RTCAlarm_IRQHandler, // 0xe4 RTC Alarm
	USBWakeUp_IRQHandler, // 0xe8 OTG_FS_WKUP
	0, // 0xec reserved
	0, // 0xf0 reserved
	0, // 0xf4 reserved
	0, // 0xf8 reserved
	0, // 0xfc reserved
	0, // 0x100 reserved
	0, // 0x104 reserved
	TIM5_IRQHandler, // 0x108 TIM5
	SPI3_IRQHandler, // 0x10c SPI3
	UART4_IRQHandler, // 0x110 UART4
	UART5_IRQHandler, // 0x114 UART5
	TIM6_IRQHandler, // 0x118 TIM6
	TIM7_IRQHandler, // 0x11c TIM7
	DMA2_Channel1_IRQHandler, // 0x120 DMA2_Channel1
	DMA2_Channel2_IRQHandler, // 0x124 DMA2_Channel2
	DMA2_Channel3_IRQHandler, // 0x128 DMA2_Channel3
	DMA2_Channel4_IRQHandler, // 0x12c DMA2_Channel4
	DMA2_Channel5_IRQHandler, // 0x130 DMA2_Channel5
	ETH_IRQHandler, // 0x134 ETH
	ETH_WKUP_IRQHandler, // 0x138 ETH_WKUP
	CAN2_TX_IRQHandler, // 0x13c CAN2_TX
	CAN2_RX0_IRQHandler, // 0x140 CAN2_RX0
	CAN2_RX1_IRQHandler, // 0x144 CAN2_RX1
	CAN2_SCE_IRQHandler, // 0x148 CAN2_SCE
	OTG_FS_IRQHandler, // 0x14c OTG_FS
};
