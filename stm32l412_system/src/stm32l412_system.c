#include "stm32l412.h"
#include "stm32l412_system.h"

static volatile uint32_t tick;
/*Set the starting frequency of the SystemCoreClock at 4Mhz*/
uint32_t hclk = 4000000U;

/*tick increments every 1ms (1KHz)*/
void set_tick(void)
{
	tick = 0;
	SysTick_Config(hclk / 1000);
}

void SysTick_Handler(void)
{
	++tick;
}

uint32_t get_tick(void)
{
	return tick;
}

void delay(uint32_t timeout)
{
	volatile uint32_t s = tick;
	while (tick - s < timeout);
}

/**
 * @brief Used to consume cpu cycles. Do not use as a delay.
 * @note Only for initialization of clock peripherals, or special cases.
 		 https://stackoverflow.com/questions/7083482/how-to-prevent-gcc-from-optimizing-out-a-busy-wait-loop
 * @param max Max delay.
*/
void __attribute__((noinline)) cpu_busy_wait(uint32_t max)
{
	for (volatile uint32_t i = 0U; i < max; i++)
	{
		__asm__ __volatile__("" : "+g" (i) : : );
	}
}