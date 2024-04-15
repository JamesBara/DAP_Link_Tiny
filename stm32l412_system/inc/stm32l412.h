#ifndef STM32L412_H
#define STM32L412_H

#ifdef __cplusplus
extern "C" {
#endif 

#define __CM4_REV                 0x0000U
#define __MPU_PRESENT             1U
#define __VTOR_PRESENT            1U
#define __NVIC_PRIO_BITS          4U
#define __Vendor_SysTickConfig    0U
#define __FPU_PRESENT             1U


typedef enum
{
	NMI_IRQn = -14,
	HardFault_IRQn = -13,
	MemManage_IRQn = -12,
	BusFault_IRQn = -11,
	UsageFault_IRQn = -10,
	SVC_IRQn = -5,
	PendSV_IRQn = -2,
	SysTick_IRQn = -1,
	WWDG_IRQn = 0,
	PVD_PVM_IRQn = 1,
	RTC_TAMP_STAMP_IRQn = 2,
	RTC_WKUP_IRQn = 3,
	FLASH_IRQn = 4,
	RCC_IRQn = 5,
	EXTI0_IRQn = 6,
	EXTI1_IRQn = 7,
	EXTI2_IRQn = 8,
	EXTI3_IRQn = 9,
	EXTI4_IRQn = 10,
	DMA1_Channel1_IRQn = 11,
	DMA1_Channel2_IRQn = 12,
	DMA1_Channel3_IRQn = 13,
	DMA1_Channel4_IRQn = 14,
	DMA1_Channel5_IRQn = 15,
	DMA1_Channel6_IRQn = 16,
	DMA1_Channel7_IRQn = 17,
	ADC1_2_IRQn = 18,
	EXTI9_5_IRQn = 23,
	TIM1_BRK_TIM15_IRQn = 24,
	TIM1_UP_TIM16_IRQn = 25,
	TIM1_TRG_COM_IRQn = 26,
	TIM1_CC_IRQn = 27,
	TIM2_IRQn = 28,
	I2C1_EV_IRQn = 31,
	I2C1_ER_IRQn = 32,
	I2C2_EV_IRQn = 33,
	I2C2_ER_IRQn = 34,
	SPI1_IRQn = 35,
	SPI2_IRQn = 36,
	USART1_IRQn = 37,
	USART2_IRQn = 38,
	USART3_IRQn = 39,
	EXTI15_10_IRQn = 40,
	RTC_ALARM_IRQn = 41,
	TIM6_IRQn = 54,
	DMA2_Channel1_IRQn = 56,
	DMA2_Channel2_IRQn = 57,
	DMA2_Channel3_IRQn = 58,
	DMA2_Channel4_IRQn = 59,
	DMA2_Channel5_IRQn = 60,
	COMP_IRQn = 64,
	LPTIM1_IRQn = 65,
	LPTIM2_IRQn = 66,
	USB_IRQn = 67,
	DMA2_Channel6_IRQn = 68,
	DMA2_Channel7_IRQn = 69,
	LPUART1_IRQn = 70,
	QUADSPI_IRQn = 71,
	I2C3_EV_IRQn = 72,
	I2C3_ER_IRQn = 73,
	TSC_IRQn = 77,
	RNG_IRQn = 80,
	FPU_IRQn = 81,
	CRS_IRQn = 82
}IRQn_Type;

#include "core_cm4.h"

#ifdef __cplusplus
}
#endif
#endif //endif STM32L412_H