#include "stm32l412_system.h"

typedef void(*prvt_vector_handler)(void);

extern volatile uint32_t _estack;
extern volatile uint32_t _sdata;
extern volatile uint32_t _edata;
extern volatile uint32_t _sbss;
extern volatile uint32_t _ebss;
extern volatile uint32_t _sidata;

extern int main(void);
void Reset_Handler(void);
void Default_Handler(void);

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((naked));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Debug_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));
void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_PVM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_TAMP_STAMP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_ALARM_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void COMP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void LPTIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USB_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Channel7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void LPUART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void QUADSPI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TSC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RNG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FPU_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CRS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

void Reset_Handler()
{

    volatile uint32_t *src, *dst, *edata_addr, *ebss_addr;
    src = &_sidata;
    dst = &_sdata;
    edata_addr = &_edata;
    ebss_addr = &_ebss;

    /*Copy flash data section to sram data section*/
    while (dst < edata_addr)
    {
        *dst++ = *src++;
    }

    /*Empty bss section from uninitialized global variables*/
    dst = &_sbss;
    while(dst < ebss_addr)
    {
        *dst++ = 0x0U;
    }

    /*Start timekeeping*/
    set_tick();

    main();
}

void Default_Handler()
{
    while (1);
}

const prvt_vector_handler prvt_vector_table[] __attribute__((section(".isr_vector"))) =
{ 
    (prvt_vector_handler)((uint32_t)&_estack),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    Debug_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,
    PVD_PVM_IRQHandler,
    RTC_TAMP_STAMP_IRQHandler,
    RTC_WKUP_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_IRQHandler,
    DMA1_Channel3_IRQHandler,
    DMA1_Channel4_IRQHandler,
    DMA1_Channel5_IRQHandler,
    DMA1_Channel6_IRQHandler,
    DMA1_Channel7_IRQHandler,
    ADC1_2_IRQHandler,
    0,
    0,
    0,
    0,
    EXTI9_5_IRQHandler,
    TIM1_BRK_TIM15_IRQHandler,
    TIM1_UP_TIM16_IRQHandler,
    TIM1_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    0,
    0,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_ALARM_IRQHandler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    TIM6_IRQHandler,
    0,
    DMA2_Channel1_IRQHandler,
    DMA2_Channel2_IRQHandler,
    DMA2_Channel3_IRQHandler,
    DMA2_Channel4_IRQHandler,
    DMA2_Channel5_IRQHandler,
    0,
    0,
    0,
    COMP_IRQHandler,
    LPTIM1_IRQHandler,
    LPTIM2_IRQHandler,
    USB_IRQHandler,
    DMA2_Channel6_IRQHandler,
    DMA2_Channel7_IRQHandler,
    LPUART1_IRQHandler,
    QUADSPI_IRQHandler,
    I2C3_EV_IRQHandler,
    I2C3_ER_IRQHandler,
    0,
    0,
    0,
    TSC_IRQHandler,
    0,
    0,
    RNG_IRQHandler,
    FPU_IRQHandler,
    CRS_IRQHandler
};

void HardFault_Handler()
{

#if (!NDEBUG)
    __asm__("BKPT");
#else
    NVIC_SystemReset();
#endif
}
