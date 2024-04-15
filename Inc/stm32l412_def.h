#ifndef STM32L412_DEF_H
#define STM32L412_DEF_H

#include "stm32l412_system.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
- GPIO for STM32L412
******************************************************************************/
typedef struct
{
	volatile uint32_t moder;
	volatile uint32_t otyper;
	volatile uint32_t ospeedr;
	volatile uint32_t pupdr;
	volatile uint32_t idr;
	volatile uint32_t odr;
	volatile uint32_t bsrr;
	volatile uint32_t lckr;
	volatile uint32_t afr[2];
	volatile uint32_t brr;
} gpio_reg_type;

#define GPIO_BASE_ADDR (0x48000000UL)

#define GPIOA ((gpio_reg_type*) GPIO_BASE_ADDR)
#define GPIOB ((gpio_reg_type*) (GPIO_BASE_ADDR + 0x400U))

/*USB PIN definitions*/
#define GPIO_USB_FS_PORT GPIOA
#define GPIO_USB_DM_PIN (0xBU)
#define GPIO_USB_DP_PIN (0xCU)

/*DAP SW definitions*/
#define GPIO_DAP_nRESET_PORT GPIOB
#define GPIO_DAP_SWCLK_PORT GPIOB
#define GPIO_DAP_SWDIO_PORT GPIOB
#define GPIO_DAP_nRESET_PIN (0x7U)
#define GPIO_DAP_SWCLK_PIN (0x8U)
#define GPIO_DAP_SWDIO_PIN (0x9U)

/*gpio helper definitions*/
#define GPIO_MODDER_POS(x) ((x) << 0x1U)
#define GPIO_OSPEEDR_POS(x) ((x) << 0x1U)
#define GPIO_PUPDR_POS(x) ((x) << 0x1U)

#define GPIO_MASK (0x3U)
#define GPIO_INPUT (0x0U)
#define GPIO_OUTPUT (0x1U)
#define GPIO_ALTERNATE_FUNCTION (0x2U)
#define GPIO_ANALOG (0x3U)

#define GPIO_VERY_HIGH_SPEED (0x3U)

#define GPIO_AFRN(x) ((x) >> 0x3U)
#define GPIO_AFSELN_POS(x) (((x) & 0x07U) << 0x2U)
#define GPIO_AFSELN_MASK (0xFU)

/*USB definitions*/
/*usb_dm gpio*/
#define GPIO_CLEAR_USB_DM_MODER() _MACRO_CLEAR_BIT_VAL(GPIO_USB_FS_PORT->moder, GPIO_MASK, GPIO_MODDER_POS(GPIO_USB_DM_PIN))
#define GPIO_CLEAR_USB_DM_OSPEEDR() _MACRO_CLEAR_BIT_VAL(GPIO_USB_FS_PORT->ospeedr, GPIO_MASK, GPIO_OSPEEDR_POS(GPIO_USB_DM_PIN))
#define GPIO_CLEAR_USB_DM_OTYPER() _MACRO_CLEAR_BIT(GPIO_USB_FS_PORT->otyper, GPIO_USB_DM_PIN)
#define GPIO_CLEAR_USB_DM_PUPDR() _MACRO_CLEAR_BIT_VAL(GPIO_USB_FS_PORT->pupdr, GPIO_MASK, GPIO_PUPDR_POS(GPIO_USB_DM_PIN))
#define GPIO_CLEAR_USB_DM_AFR() _MACRO_CLEAR_BIT_VAL(GPIO_USB_FS_PORT->afr[GPIO_AFRN(GPIO_USB_DM_PIN)], GPIO_AFSELN_MASK, GPIO_AFSELN_POS(GPIO_USB_DM_PIN))

#define GPIO_SET_USB_DM_MODER() _MACRO_SET_BIT_VAL(GPIO_USB_FS_PORT->moder, GPIO_ALTERNATE_FUNCTION, GPIO_MODDER_POS(GPIO_USB_DM_PIN))
#define GPIO_SET_USB_DM_OSPEEDR() _MACRO_SET_BIT_VAL(GPIO_USB_FS_PORT->ospeedr, GPIO_VERY_HIGH_SPEED, GPIO_OSPEEDR_POS(GPIO_USB_DM_PIN))
#define GPIO_SET_USB_DM_AFR() _MACRO_SET_BIT_VAL(GPIO_USB_FS_PORT->afr[GPIO_AFRN(GPIO_USB_DM_PIN)], 10U, GPIO_AFSELN_POS(GPIO_USB_DM_PIN))

/*usb_dp gpio*/
#define GPIO_CLEAR_USB_DP_MODER() _MACRO_CLEAR_BIT_VAL(GPIO_USB_FS_PORT->moder, GPIO_MASK, GPIO_MODDER_POS(GPIO_USB_DP_PIN))
#define GPIO_CLEAR_USB_DP_OSPEEDR() _MACRO_CLEAR_BIT_VAL(GPIO_USB_FS_PORT->ospeedr, GPIO_MASK, GPIO_OSPEEDR_POS(GPIO_USB_DP_PIN))
#define GPIO_CLEAR_USB_DP_OTYPER() _MACRO_CLEAR_BIT(GPIO_USB_FS_PORT->otyper, GPIO_USB_DP_PIN)
#define GPIO_CLEAR_USB_DP_PUPDR() _MACRO_CLEAR_BIT_VAL(GPIO_USB_FS_PORT->pupdr, GPIO_MASK, GPIO_PUPDR_POS(GPIO_USB_DP_PIN))
#define GPIO_CLEAR_USB_DP_AFR() _MACRO_CLEAR_BIT_VAL(GPIO_USB_FS_PORT->afr[GPIO_AFRN(GPIO_USB_DP_PIN)], GPIO_AFSELN_MASK, GPIO_AFSELN_POS(GPIO_USB_DP_PIN))

#define GPIO_SET_USB_DP_MODER() _MACRO_SET_BIT_VAL(GPIO_USB_FS_PORT->moder, GPIO_ALTERNATE_FUNCTION, GPIO_MODDER_POS(GPIO_USB_DP_PIN))
#define GPIO_SET_USB_DP_OSPEEDR() _MACRO_SET_BIT_VAL(GPIO_USB_FS_PORT->ospeedr, GPIO_VERY_HIGH_SPEED, GPIO_OSPEEDR_POS(GPIO_USB_DP_PIN))
#define GPIO_SET_USB_DP_AFR() _MACRO_SET_BIT_VAL(GPIO_USB_FS_PORT->afr[GPIO_AFRN(GPIO_USB_DP_PIN)], 10U, GPIO_AFSELN_POS(GPIO_USB_DP_PIN))






#define GPIO_USB_DM_DP_ENABLE() do \
{ \
	GPIO_CLEAR_USB_DM_MODER(); \
	GPIO_CLEAR_USB_DM_OSPEEDR(); \
	GPIO_CLEAR_USB_DM_OTYPER(); \
	GPIO_CLEAR_USB_DM_PUPDR(); \
	GPIO_CLEAR_USB_DM_AFR(); \
	GPIO_CLEAR_USB_DP_MODER(); \
	GPIO_CLEAR_USB_DP_OSPEEDR(); \
	GPIO_CLEAR_USB_DP_OTYPER(); \
	GPIO_CLEAR_USB_DP_PUPDR(); \
	GPIO_CLEAR_USB_DP_AFR(); \
	GPIO_SET_USB_DM_MODER(); \
	GPIO_SET_USB_DM_OSPEEDR(); \
	GPIO_SET_USB_DM_AFR(); \
	GPIO_SET_USB_DP_MODER(); \
	GPIO_SET_USB_DP_OSPEEDR(); \
	GPIO_SET_USB_DP_AFR(); \
}while(0)



/*DAP definitions*/
/*nreset gpio*/
#define GPIO_CLEAR_DAP_nRESET_MODER() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_nRESET_PORT->moder, GPIO_MASK, GPIO_MODDER_POS(GPIO_DAP_nRESET_PIN))
#define GPIO_CLEAR_DAP_nRESET_OSPEEDR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_nRESET_PORT->ospeedr, GPIO_MASK, GPIO_OSPEEDR_POS(GPIO_DAP_nRESET_PIN))
#define GPIO_CLEAR_DAP_nRESET_OTYPER() _MACRO_CLEAR_BIT(GPIO_DAP_nRESET_PORT->otyper, GPIO_DAP_nRESET_PIN)
#define GPIO_CLEAR_DAP_nRESET_PUPDR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_nRESET_PORT->pupdr, GPIO_MASK, GPIO_PUPDR_POS(GPIO_DAP_nRESET_PIN))
#define GPIO_CLEAR_DAP_nRESET_AFR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_nRESET_PORT->afr[GPIO_AFRN(GPIO_DAP_nRESET_PIN)], GPIO_AFSELN_MASK, GPIO_AFSELN_POS(GPIO_DAP_nRESET_PIN))

#define GPIO_SET_DAP_nRESET_MODER() _MACRO_SET_BIT_VAL(GPIO_DAP_nRESET_PORT->moder, GPIO_OUTPUT, GPIO_MODDER_POS(GPIO_DAP_nRESET_PIN))
#define GPIO_SET_DAP_nRESET_OSPEEDR() _MACRO_SET_BIT_VAL(GPIO_DAP_nRESET_PORT->ospeedr, GPIO_VERY_HIGH_SPEED, GPIO_OSPEEDR_POS(GPIO_DAP_nRESET_PIN))
#define GPIO_SET_DAP_nRESET_OTYPER() _MACRO_SET_BIT(GPIO_DAP_nRESET_PORT->otyper, GPIO_DAP_nRESET_PIN)

#define GPIO_GET_DAP_nRESET() (_MACRO_GET_BIT(GPIO_DAP_nRESET_PORT->odr, GPIO_DAP_nRESET_PIN))
#define GPIO_SET_DAP_nRESET() (GPIO_DAP_nRESET_PORT->bsrr = (0x1U << GPIO_DAP_nRESET_PIN))
#define GPIO_CLEAR_DAP_nRESET() (GPIO_DAP_nRESET_PORT->brr = (0x1U << GPIO_DAP_nRESET_PIN))

/*swclk gpio*/
#define GPIO_CLEAR_DAP_SWCLK_MODER() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_SWCLK_PORT->moder, GPIO_MASK, GPIO_MODDER_POS(GPIO_DAP_SWCLK_PIN))
#define GPIO_CLEAR_DAP_SWCLK_OSPEEDR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_SWCLK_PORT->ospeedr, GPIO_MASK, GPIO_OSPEEDR_POS(GPIO_DAP_SWCLK_PIN))
#define GPIO_CLEAR_DAP_SWCLK_OTYPER() _MACRO_CLEAR_BIT(GPIO_DAP_SWCLK_PORT->otyper, GPIO_DAP_SWCLK_PIN)
#define GPIO_CLEAR_DAP_SWCLK_PUPDR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_SWCLK_PORT->pupdr, GPIO_MASK, GPIO_PUPDR_POS(GPIO_DAP_SWCLK_PIN))
#define GPIO_CLEAR_DAP_SWCLK_AFR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_SWCLK_PORT->afr[GPIO_AFRN(GPIO_DAP_SWCLK_PIN)], GPIO_AFSELN_MASK, GPIO_AFSELN_POS(GPIO_DAP_SWCLK_PIN))

#define GPIO_SET_DAP_SWCLK_MODER() _MACRO_SET_BIT_VAL(GPIO_DAP_SWCLK_PORT->moder, GPIO_OUTPUT, GPIO_MODDER_POS(GPIO_DAP_SWCLK_PIN))
#define GPIO_SET_DAP_SWCLK_OSPEEDR() _MACRO_SET_BIT_VAL(GPIO_DAP_SWCLK_PORT->ospeedr, GPIO_VERY_HIGH_SPEED, GPIO_OSPEEDR_POS(GPIO_DAP_SWCLK_PIN))

#define GPIO_GET_DAP_SWCLK() (_MACRO_GET_BIT(GPIO_DAP_SWCLK_PORT->odr, GPIO_DAP_SWCLK_PIN))
#define GPIO_SET_DAP_SWCLK() (GPIO_DAP_SWCLK_PORT->bsrr = (0x1U << GPIO_DAP_SWCLK_PIN))
#define GPIO_CLEAR_DAP_SWCLK() (GPIO_DAP_SWCLK_PORT->brr = (0x1U << GPIO_DAP_SWCLK_PIN))

/*swdio gpio*/
#define GPIO_CLEAR_DAP_SWDIO_MODER() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_SWDIO_PORT->moder, GPIO_MASK, GPIO_MODDER_POS(GPIO_DAP_SWDIO_PIN))
#define GPIO_CLEAR_DAP_SWDIO_OSPEEDR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_SWDIO_PORT->ospeedr, GPIO_MASK, GPIO_OSPEEDR_POS(GPIO_DAP_SWDIO_PIN))
#define GPIO_CLEAR_DAP_SWDIO_OTYPER() _MACRO_CLEAR_BIT(GPIO_DAP_SWDIO_PORT->otyper, GPIO_DAP_SWDIO_PIN)
#define GPIO_CLEAR_DAP_SWDIO_PUPDR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_SWDIO_PORT->pupdr, GPIO_MASK, GPIO_PUPDR_POS(GPIO_DAP_SWDIO_PIN))
#define GPIO_CLEAR_DAP_SWDIO_AFR() _MACRO_CLEAR_BIT_VAL(GPIO_DAP_SWDIO_PORT->afr[GPIO_AFRN(GPIO_DAP_SWDIO_PIN)], GPIO_AFSELN_MASK, GPIO_AFSELN_POS(GPIO_DAP_SWDIO_PIN))

#define GPIO_SET_DAP_SWDIO_MODER() _MACRO_SET_BIT_VAL(GPIO_DAP_SWDIO_PORT->moder, GPIO_OUTPUT, GPIO_MODDER_POS(GPIO_DAP_SWDIO_PIN))
#define GPIO_SET_DAP_SWDIO_OSPEEDR() _MACRO_SET_BIT_VAL(GPIO_DAP_SWDIO_PORT->ospeedr, GPIO_VERY_HIGH_SPEED, GPIO_OSPEEDR_POS(GPIO_DAP_SWDIO_PIN))

#define GPIO_GET_DAP_SWDIO() (_MACRO_GET_BIT(GPIO_DAP_SWDIO_PORT->idr, GPIO_DAP_SWDIO_PIN))
#define GPIO_SET_DAP_SWDIO() (GPIO_DAP_SWDIO_PORT->bsrr = (0x1U << GPIO_DAP_SWDIO_PIN))
#define GPIO_CLEAR_DAP_SWDIO() (GPIO_DAP_SWDIO_PORT->brr = (0x1U << GPIO_DAP_SWDIO_PIN))

/*******************************************************************************
- PWR for STM32L412
******************************************************************************/
typedef struct
{
	volatile uint32_t cr1;
	volatile uint32_t cr2;
	volatile uint32_t cr3;
	volatile uint32_t cr4;
	volatile uint16_t sr1;
	volatile uint32_t sr2;
	volatile uint32_t scr;
	uint32_t reserved0;
	volatile uint32_t pucra;
	volatile uint32_t pdcra;
	volatile uint32_t pucrb;
	volatile uint32_t pdcrb;
	volatile uint32_t pucrc;
	volatile uint32_t pdcrc;
	volatile uint32_t pucrd;
	volatile uint32_t pdcrd;
	volatile uint32_t pucre;
	volatile uint32_t pdcre;
	uint32_t reserved1;
	uint32_t reserved2;
	uint32_t reserved3;
	uint32_t reserved4;
	volatile uint32_t pucrh;
	volatile uint32_t pdcrh;
} pwr_reg_type;

#define PWR_BASE_ADDR (0x40007000UL)

#define PWR ((pwr_reg_type *) PWR_BASE_ADDR)

#define PWR_LPMS_POS (0x0U)
#define PWR_LPMS_STOP_0 (0x0U)
#define PWR_LPMS_STOP_1 (0x1U)
#define PWR_LPMS_STOP_2 (0x2U)
#define PWR_LPMS_STANDBY (0x3U)
#define PWR_LPMS_SHUTDOWN (0x4U)
#define PWR_LPMS_MASK (0x7U)

#define PWR_USV_POS (0xAU)

#define PWR_SET_USB_SUPPLY_VALID() (_MACRO_SET_BIT(PWR->cr2, PWR_USV_POS))

#define PWR_CLEAR_LOW_POWER_MODE() (_MACRO_CLEAR_BIT_VAL(PWR->cr1, PWR_LPMS_MASK, PWR_LPMS_POS))
#define PWR_SET_LOW_POWER_MODE_STOP_0() PWR_CLEAR_LOW_POWER_MODE
#define PWR_SET_LOW_POWER_MODE_STOP_1() (_MACRO_SET_BIT_VAL(PWR->cr1, PWR_LPMS_STOP_1, PWR_LPMS_POS))

/*******************************************************************************
- RCC for STM32L412
******************************************************************************/
typedef struct
{
	volatile uint32_t cr;
	volatile uint32_t icscr;
	volatile uint32_t cfgr;
	volatile uint32_t pllcfgr;
	uint32_t reserved0;
	uint32_t reserved1;
	volatile uint32_t cier;
	volatile uint32_t cifr;
	volatile uint32_t cicr;
	uint32_t reserved2;
	volatile uint32_t ahb1rstr;
	volatile uint32_t ahb2rstr;
	volatile uint32_t ahb3rstr;
	uint32_t reserved3;
	volatile uint32_t apb1rstr1;
	volatile uint32_t apb1rstr2;
	volatile uint32_t apb2rstr;
	uint32_t reserved4;
	volatile uint32_t ahb1enr;
	volatile uint32_t ahb2enr;
	volatile uint32_t ahb3enr;
	uint32_t reserved5;
	volatile uint32_t apb1enr1;
	volatile uint32_t apb1enr2;
	volatile uint32_t apb2enr;
	uint32_t reserved6;
	volatile uint32_t ahb1smenr;
	volatile uint32_t ahb2smenr;
	volatile uint32_t ahb3smenr;
	uint32_t reserved7;
	volatile uint32_t apb1smenr1;
	volatile uint32_t apb1smenr2;
	volatile uint32_t apb2smenr;
	uint32_t reserved8;
	volatile uint32_t ccipr;
	uint32_t reserved9;
	volatile uint32_t bdcr;
	volatile uint32_t csr;
	volatile uint32_t crrcr;
} rcc_reg_type;

#define RCC_BASE_ADDR (0x40021000UL)

#define RCC ((rcc_reg_type*) RCC_BASE_ADDR)

#define RCC_MSI_MAX_FREQ_RANGE (0xBU)
#define RCC_BYP_MAX (0x1U)
#define RCC_PLLSRC_MAX (0x3U)
#define RCC_PLLM_MAX (0x7U)
#define RCC_PLLN_MIN (0x8U)
#define RCC_PLLN_MAX (0x56U)
#define RCC_PLLQ_MAX (0x3U)
#define RCC_PLLR_MAX (0x3U)
#define RCC_PPRE_MAX (0x7U)
#define RCC_SW_MAX (0x3U)
#define RCC_CSS_MAX (0x1U)
#define RCC_HPRE_MAX (0xFU)
#define RCC_CLK48SEL_MAX (0x3U)

/*cr register*/
#define RCC_MSION_POS (0x0U)
#define RCC_MSIRDY_POS (0x1U)
#define RCC_MSIRGSEL_POS (0x3U)
#define RCC_CR_MSIRANGE_POS (0x4U)
#define RCC_HSION_POS (0x8U)
#define RCC_HSIRDY_POS (0xAU)
#define RCC_HSEON_POS (0x10U)
#define RCC_HSERDY_POS (0x11U)
#define RCC_HSEBYP_POS (0x12U)
#define RCC_CSSON_POS (0x13U)
#define RCC_PLLON_POS (0x18U)
#define RCC_PLLRDY_POS (0x19U)

#define RCC_CR_MSIRANGE_MASK (0xFU)

/*Remove?*/
#define RCC_MSION (0x1U << RCC_MSION_POS)
#define RCC_MSIRDY (0x1U << RCC_MSIRDY_POS)
#define RCC_MSIRGSEL (0x1U << RCC_MSIRGSEL_POS)
#define RCC_HSION (0x1U << RCC_HSION_POS)
#define RCC_HSIRDY (0x1U << RCC_HSIRDY_POS)
#define RCC_HSERDY (0x1U << RCC_HSERDY_POS)
#define RCC_PLLRDY (0x1U << RCC_PLLRDY_POS)

/*cgfr register*/
#define RCC_SW_POS (0x0U)
#define RCC_SWS_POS (0x2U)
#define RCC_HPRE_POS (0x4U)
#define RCC_PPRE1_POS (0x8U)
#define RCC_PPRE2_POS (0xBU)
#define RCC_STOPWUCK_POS (0xFU)
#define RCC_MCOSEL_POS (0x18U)
#define RCC_MCOPRE_POS (0x1CU)

#define RCC_SW_MASK (0x3U)
#define RCC_SW_MSI (0x0U)
#define RCC_SW_HSI16 (0x1U)
#define RCC_SW_HSE (0x2U)
#define RCC_SW_PLL (0x3U)
#define RCC_SWS_MASK (0x3U)
#define RCC_SWS_MSI (0x0U)
#define RCC_SWS_HSI16 (0x1U)
#define RCC_SWS_HSE (0x2U)
#define RCC_SWS_PLL (0x3U)

#define RCC_HPRE_MASK (0xFU)
#define RCC_PPRE_MASK (0x7U)
#define RCC_MCOSEL_MASK (0xFU)
#define RCC_MCOPRE_MASK (0x7U)

#define RCC_SW (RCC_SW_MASK << RCC_SW_POS)
#define RCC_HPRE (RCC_HPRE_MASK << RCC_HPRE_POS)

/*pllcgfr register*/
#define RCC_PLLSRC_POS (0x0U)
#define RCC_PLLM_POS (0x4U)
#define RCC_PLLN_POS (0x8U)
#define RCC_PLLQEN_POS (0x14U)
#define RCC_PLLQ_POS (0x15U)
#define RCC_PLLREN_POS (0x18U)
#define RCC_PLLR_POS (0x19U)

#define RCC_PLLSRC_MASK (0x3U)
#define RCC_PLLSRC_NO (0x0U)
#define RCC_PLLSRC_MSI (0x1U)
#define RCC_PLLSRC_HSI16 (0x2U)
#define RCC_PLLSRC_HSE (0x3U)
#define RCC_PLLM_MASK (0x7U)
#define RCC_PLLN_MASK (0x7FU)
#define RCC_PLLQ_MASK (0x3U)
#define RCC_PLLR_MASK (0x3U)

#define RCC_PLLSRC (RCC_PLLSRC_MASK << RCC_PLLSRC_POS)
#define RCC_PLLM (RCC_PLLM_MASK << RCC_PLLM_POS)
#define RCC_PLLN (RCC_PLLN_MASK << RCC_PLLN_POS)
#define RCC_PLLQ (RCC_PLLQ_MASK << RCC_PLLQ_POS)
#define RCC_PLLR (RCC_PLLR_MASK << RCC_PLLR_POS)


/*ccipr register*/
#define RCC_CLK48SEL_POS (0x1A)


#define RCC_CLK48SEL_MASK (0x3U)
#define RCC_CLK48SEL_HSI48 (0x0U)
#define RCC_CLK48SEL_PLLQ (0x2U)
#define RCC_CLK48SEL_MSI (0x3U)


/*bdcr register*/
#define RCC_LSEBYP_POS (0x2U)
#define RCC_LSEDRV_POS (0x3U)
#define RCC_LSECSSON_POS (0x5U)
#define RCC_LSESYSDIS_POS (0x7U)
#define RCC_RTCSEL_POS (0x8U)
#define RCC_LSCOEN_POS (0x18U)
#define RCC_LSCOSEL_POS (0x19U)

/*csr register*/
#define RCC_CSR_MSIRANGE_POS (0x8U)
#define RCC_LSIPREDIV_POS (0x4U)
#define RCC_RESET_FLAGS_POS (0x18U)

#define RCC_CSR_MSIRANGE_MASK (0xFU)

/*crrcr register*/
#define RCC_HSI48ON_POS (0x0U)
#define RCC_HSI48RDY_POS (0x1U)

/*ahb1 register*/

/*ahb2 register*/
#define RCC_GPIOA_POS (0x0U)
#define RCC_GPIOB_POS (0x1U)
#define RCC_GPIOC_POS (0x2U)
#define RCC_GPIOH_POS (0x7U)

/*ahb3 register*/


/*apb1r1 register*/
#define RCC_USB_POS (0x1AU)
#define RCC_PWR_POS (0x1CU)


/*apb1r2 register*/

/*apb2 register*/


/*Misc*/
#define RCC_PLL_INPUT_MIN_FREQ (4000000U)
#define RCC_PLL_INPUT_MAX_FREQ (16000000U)
#define RCC_VCO_MIN_FREQ (64000000U)
#define RCC_VCO_MAX_FREQ_RANGE1 (344000000U)
#define RCC_VCO_MAX_FREQ_RANGE2 (128000000U)
#define RCC_SYSCLK_MAX_FREQ_RANGE1 (80000000U)
#define RCC_SYSCLK_MAX_FREQ_RANGE2 (26000000U)
#define RCC_MAX_TIMEOUT (5000U)


#define RCC_PWR_CLK_ENABLE() do \
{ \
	_MACRO_SET_BIT(RCC->apb1enr1, RCC_PWR_POS); \
	cpu_busy_wait(2); \
}while(0)

#define RCC_USB_CLK_ENABLE() do \
{ \
	_MACRO_SET_BIT(RCC->apb1enr1, RCC_USB_POS); \
	cpu_busy_wait(2); \
}while(0)

#define RCC_GPIOA_CLK_ENABLE() do \
{ \
	_MACRO_SET_BIT(RCC->ahb2enr, RCC_GPIOA_POS); \
	cpu_busy_wait(2); \
}while(0)

#define RCC_GPIOB_CLK_ENABLE() do \
{ \
	_MACRO_SET_BIT(RCC->ahb2enr, RCC_GPIOB_POS); \
	cpu_busy_wait(2); \
}while(0)

#define RCC_USB_DP_CLK_ENABLE() RCC_GPIOA_CLK_ENABLE()
#define RCC_USB_DM_CLK_ENABLE() RCC_GPIOA_CLK_ENABLE()
#define RCC_SWDIO_CLK_ENABLE() RCC_GPIOB_CLK_ENABLE()
#define RCC_SWCLK_CLK_ENABLE() RCC_GPIOB_CLK_ENABLE()
#define RCC_nRESET_CLK_ENABLE() RCC_GPIOB_CLK_ENABLE()

/*******************************************************************************
- FLASH for STM32L412
******************************************************************************/
typedef struct
{
	volatile uint32_t acr;
	volatile uint32_t pdkeyr;
	volatile uint32_t keyr;
	volatile uint32_t optkeyr;
	volatile uint32_t sr;
	volatile uint32_t cr;
	volatile uint32_t eccr;
	volatile uint32_t optr;
	volatile uint32_t pcrop1sr;
	volatile uint32_t pcrop1er;
	volatile uint32_t wrp1ar;
	volatile uint32_t wrp1br;
}flash_reg_type;

#define FLASH_BASE_ADDR (0x40022000UL)

#define FLASH ((flash_reg_type*) FLASH_BASE_ADDR)

#define FLASH_LATENCY_POS (0x0U)
#define FLASH_PRFTEN_POS (0x8U)
#define FLASH_ICEN_POS (0x9U)
#define FLASH_DCEN_POS (0xAU)

#define FLASH_LATENCY_1_WAIT_STATES (0x1U)
#define FLASH_LATENCY_2_WAIT_STATES (0x2U)
#define FLASH_LATENCY_3_WAIT_STATES (0x3U)
#define FLASH_LATENCY_4_WAIT_STATES (0x4U)
#define FLASH_LATENCY_MASK (0x7U)

#define FLASH_SET_LATENCY_1_WAIT_STATES() _MACRO_SET_BIT_VAL(FLASH->acr, FLASH_LATENCY_1_WAIT_STATES, FLASH_LATENCY_POS)
#define FLASH_SET_LATENCY_2_WAIT_STATES() _MACRO_SET_BIT_VAL(FLASH->acr, FLASH_LATENCY_2_WAIT_STATES, FLASH_LATENCY_POS)
#define FLASH_SET_LATENCY_3_WAIT_STATES() _MACRO_SET_BIT_VAL(FLASH->acr, FLASH_LATENCY_3_WAIT_STATES, FLASH_LATENCY_POS)
#define FLASH_SET_LATENCY_4_WAIT_STATES() _MACRO_SET_BIT_VAL(FLASH->acr, FLASH_LATENCY_4_WAIT_STATES, FLASH_LATENCY_POS)
#define FLASH_SET_PREFETCH() _MACRO_SET_BIT(FLASH->acr, FLASH_PRFTEN_POS)

/*******************************************************************************
- USB for STM32L412
******************************************************************************/
typedef struct
{
	volatile uint32_t cntr; /*!< USB control register */
	volatile uint32_t istr; /*!< USB interrupt status register */
	volatile uint32_t fnr; /*!< USB frame number register */
	volatile uint32_t daddr; /*!< USB device address */
	volatile uint32_t btable; /*!< Buffer table address */
	volatile uint32_t lpmcsr; /*!< LPM control and status register */
	volatile uint32_t bcdr; /*!< Battery charging detector */
}usbd_fullspeed_type;

#define USBD_FS_BASE_ADDR (0x40006840UL) /*!< USB Register Base Address */
#define USBD_SRAM_BASE_ADDR (0x40006C00UL) /*!< USB SRAM Register Base Address */
#define USB_EP_BASE_ADDR (0x40006800UL) /*!< Endpoint Base Address */

#define USBD ((usbd_fullspeed_type*) USBD_FS_BASE_ADDR) /*!< Pointer to USB Base Address */
#define USBD_ENDPOINT_N_REG(ep_num) (uint16_t*) (USB_EP_BASE_ADDR + ((ep_num) << 0x2U)) /*!< Pointer to endpoint n register. */
#define USBD_BTABLE_REG(ep_num, offset) (uint16_t*) (USBD_SRAM_BASE_ADDR + (USBD->btable) + ((ep_num) << 0x3U) + (offset))

#define USBD_ENDPOINT_0 (0x0U)
#define USBD_ENDPOINT_1 (0x1U) /*OUT/IN Bulk endpoint*/

#define USBD_ENDPOINT_0_REG (uint16_t*) (USB_EP_BASE_ADDR) /*!< Pointer to endpoint 0 register. */
#define USBD_ENDPOINT_1_REG (uint16_t*) (USB_EP_BASE_ADDR + 4) /*!< Pointer to endpoint 1 register. */

/*bcdr bits*/
#define USBD_BCDR_DP_PULLUP_POS (0xFU)

/*daddr bits*/
#define USBD_DADDR_POS (0x0U)
#define USBD_DADDR_EF_POS (0x7U)

#define USBD_DADDR_MASK (0x7FU)

/*cntr bits*/
#define USBD_CNTR_FRES_POS (0x0U)
#define USBD_CNTR_PDWN_POS (0x1U)
#define USBD_CNTR_LP_MODE_POS (0x2U)
#define USBD_CNTR_FSUSP_POS (0x3U)
#define USBD_CNTR_RESUME_POS (0x4U)
#define USBD_CNTR_L1RESUME_POS (0x5U)
#define USBD_CNTR_L1REQM_POS (0x7U)
#define USBD_CNTR_ESOFM_POS (0x8U)
#define USBD_CNTR_SOFM_POS (0x9U)
#define USBD_CNTR_RESETM_POS (0xAU)
#define USBD_CNTR_SUSPM_POS (0xBU)
#define USBD_CNTR_WKUPM_POS (0xCU)
#define USBD_CNTR_ERRM_POS (0xDU)
#define USBD_CNTR_PMAOVRM_POS (0xEU)
#define USBD_CNTR_CTRM_POS (0xFU)

/*Unused interrupts*/
#define USBD_CNTR_L1REQM (0x1U << USBD_CNTR_L1REQM_POS)
#define USBD_CNTR_ESOFM (0x1U << USBD_CNTR_ESOFM_POS)
#define USBD_CNTR_SOFM (0x1U << USBD_CNTR_SOFM_POS)
#define USBD_CNTR_ERRM (0x1U << USBD_CNTR_ERRM_POS)
#define USBD_CNTR_PMAOVRM (0x1U << USBD_CNTR_PMAOVRM_POS)

#define USBD_CNTR_RESETM (0x1U << USBD_CNTR_RESETM_POS)
#define USBD_CNTR_SUSPM (0x1U << USBD_CNTR_SUSPM_POS)
#define USBD_CNTR_WKUPM (0x1U << USBD_CNTR_WKUPM_POS)
#define USBD_CNTR_CTRM (0x1U << USBD_CNTR_CTRM_POS)

/*istr bits*/
#define USBD_ISTR_EP_ID_POS (0x0U)
#define USBD_ISTR_DIR_POS (0x4U)
#define USBD_ISTR_L1REQ_POS (0x7U)
#define USBD_ISTR_ESOF_POS (0x8U)
#define USBD_ISTR_SOF_POS (0x9U)
#define USBD_ISTR_RESET_POS (0xAU)
#define USBD_ISTR_SUSP_POS (0xBU)
#define USBD_ISTR_WKUP_POS (0xCU)
#define USBD_ISTR_ERR_POS (0xDU)
#define USBD_ISTR_PMAOVR_POS (0xEU)
#define USBD_ISTR_CTR_POS (0xFU)

#define USBD_ISTR_EP_ID_MASK (0xFU)

#define USBD_ISTR_L1REQ (USBD_ISTR_L1REQ_POS)
#define USBD_ISTR_ESOF (USBD_ISTR_ESOF_POS)
#define USBD_ISTR_SOF (USBD_ISTR_SOF_POS)
#define USBD_ISTR_RESET (USBD_ISTR_RESET_POS)
#define USBD_ISTR_SUSP (USBD_ISTR_SUSP_POS)
#define USBD_ISTR_WKUP (USBD_ISTR_WKUP_POS)
#define USBD_ISTR_ERR (USBD_ISTR_ERR_POS)
#define USBD_ISTR_PMAOVR (USBD_ISTR_PMAOVR_POS)
#define USBD_ISTR_CTR (USBD_ISTR_CTR_POS)

/*fnr bits*/
#define USBD_FNR_FN_POS (0x0U)
#define USBD_FNR_RXDM_POS (0xEU)
#define USBD_FNR_RXDP_POS (0xFU)
#define USBD_FNR_FN_MASK (0x7FFU)

/*Misc.*/
#define USBD_DIR_OUT (0x0U)
#define USBD_DIR_IN (0x1U)

/*USB SRAM definitions*/
#define USBD_SRAM_NUMBLOCK_POS (0xAU)

#define USBD_SRAM_BLSIZE_MASK (0x8000U)
#define USBD_SRAM_NUMBLOCK_MASK (0x7C00U)
#define USBD_SRAM_RX_COUNT_ALLOC(x) (uint16_t) (((uint16_t)(x) > 0x3EU) \
    ? (uint16_t)(USBD_SRAM_BLSIZE_MASK | ((((uint16_t)(x) >> 0x5U) - 0x1U) << USBD_SRAM_NUMBLOCK_POS)) \
	: (uint16_t)(((uint16_t)(x) >> 0x1U) << USBD_SRAM_NUMBLOCK_POS))
#define USBD_SRAM_COUNT_MASK (0x3FFU)

#define USBD_SRAM_SIZE (0x400U)

/*Hardware endpoint definitions*/
/*endpoint bits*/
#define USBD_EP_ADDRESS_POS (0x0U)
#define USBD_EP_STAT_TX_POS (0x4U)
#define USBD_EP_DTOG_TX_POS (0x6U)
#define USBD_EP_SWBUF_RX_POS USBD_EP_DTOG_TX_POS
#define USBD_EP_CTR_TX_POS (0x7U)
#define USBD_EP_KIND_POS (0x8U)
#define USBD_EP_TYPE_POS (0x9U)
#define USBD_EP_SETUP_POS (0xBU)
#define USBD_EP_STAT_RX_POS (0xCU)
#define USBD_EP_DTOG_RX_POS (0xEU)
#define USBD_EP_SWBUF_TX_POS USBD_EP_DTOG_RX_POS
#define USBD_EP_CTR_RX_POS (0xFU)

#define USBD_EP_ADDRESS_MASK (0xFU)
#define USBD_EP_STAT_MASK (0x3U)
#define USBD_EP_TYPE_MASK (0x3U)

#define USBD_EP_STAT_DISABLED (0x0U)
#define USBD_EP_STAT_STALL (0x1U)
#define USBD_EP_STAT_NAK (0x2U)
#define USBD_EP_STAT_VALID (0x3U)

#define USBD_EP_KIND_DBL_BUF (0x1U)

#define USBD_HW_EP_TYPE_BULK (0x0U)
#define USBD_HW_EP_TYPE_CONTROL (0x1U)
#define USBD_HW_EP_TYPE_ISOCHRONOUS (0x2U)
#define USBD_HW_EP_TYPE_INTERRUPT (0x3U)

/*Masks for the rw bits.*/
#define USBD_EP_DBL_BUF_MASK (USBD_EP_KIND_DBL_BUF << USBD_EP_KIND_POS)
#define USBD_EP_STATUS_OUT_MASK USBD_EP_DBL_BUF_MASK

#define USBD_EP_TYPE_BIT_MASK (USBD_EP_TYPE_MASK << USBD_EP_TYPE_POS)
#define USBD_EP_TYPE_BULK_MASK (USBD_HW_EP_TYPE_BULK << USBD_EP_TYPE_POS)
#define USBD_EP_TYPE_CONTROL_MASK (USBD_HW_EP_TYPE_CONTROL << USBD_EP_TYPE_POS)
#define USBD_EP_TYPE_ISOCHRONOUS_MASK (USBD_HW_EP_TYPE_ISOCHRONOUS << USBD_EP_TYPE_POS)
#define USBD_EP_TYPE_INTERRUPT_MASK (USBD_HW_EP_TYPE_INTERRUPT << USBD_EP_TYPE_POS)

/*Masks for the toggle bits.*/
#define USBD_EP_STAT_TX_MASK (USBD_EP_STAT_MASK << USBD_EP_STAT_TX_POS)
#define USBD_EP_DTOG_TX_MASK (0x1U << USBD_EP_DTOG_TX_POS)
#define USBD_EP_SWBUF_RX_MASK USBD_EP_DTOG_TX_MASK
#define USBD_EP_CTR_TX_MASK (0x1U << USBD_EP_CTR_TX_POS)
#define USBD_EP_STAT_RX_MASK (USBD_EP_STAT_MASK << USBD_EP_STAT_RX_POS)
#define USBD_EP_DTOG_RX_MASK (0x1U << USBD_EP_DTOG_RX_POS)
#define USBD_EP_SWBUF_TX_MASK USBD_EP_DTOG_RX_MASK
#define USBD_EP_CTR_RX_MASK (0x1U << USBD_EP_CTR_RX_POS)

/*Flags for the stat bits*/
#define USBD_EP_STAT_RX_DISABLED (USBD_EP_STAT_DISABLED << USBD_EP_STAT_RX_POS)
#define USBD_EP_STAT_TX_DISABLED (USBD_EP_STAT_DISABLED << USBD_EP_STAT_TX_POS)
#define USBD_EP_STAT_RX_STALL (USBD_EP_STAT_STALL << USBD_EP_STAT_RX_POS)
#define USBD_EP_STAT_TX_STALL (USBD_EP_STAT_STALL << USBD_EP_STAT_TX_POS)
#define USBD_EP_STAT_RX_NAK (USBD_EP_STAT_NAK << USBD_EP_STAT_RX_POS)
#define USBD_EP_STAT_TX_NAK (USBD_EP_STAT_NAK << USBD_EP_STAT_TX_POS)
#define USBD_EP_STAT_RX_VALID (USBD_EP_STAT_VALID << USBD_EP_STAT_RX_POS)
#define USBD_EP_STAT_TX_VALID (USBD_EP_STAT_VALID << USBD_EP_STAT_TX_POS)

/*Masks for the whole register per bit type.*/
#define USBD_EP_RW_MASK ((0x1U << USBD_EP_SETUP_POS) | (USBD_EP_TYPE_MASK << USBD_EP_TYPE_POS) | (0x1U << USBD_EP_KIND_POS) | (USBD_EP_ADDRESS_MASK << USBD_EP_ADDRESS_POS))
#define USBD_EP_RC_W0_MASK (USBD_EP_CTR_RX_MASK | USBD_EP_CTR_TX_MASK)
#define USBD_EP_T_MASK (USBD_EP_DTOG_RX_MASK | USBD_EP_STAT_RX_MASK | USBD_EP_DTOG_TX_MASK | USBD_EP_STAT_TX_MASK)

/*Configuration of an endpoint. To set a toggle bit set the t_flags and the 
*t_masks, to clear a toggle bit set the t_masks only, to preserve the current
*value don't mask the bits. Type must be of value USBD_HW_EP_TYPE_BULK, 
*USBD_HW_EP_TYPE_CONTROL, USBD_HW_EP_TYPE_ISOCHRONOUS or USBD_HW_EP_TYPE_INTERRUPT
*kind must be of value USBD_EP_KIND_DBL_BUF or 0 address must be of value 0-7*/
#define USBD_EP_CONFIGURATION(reg, type, kind, address, t_flags, t_masks) ((((reg) ^ (t_flags)) & (t_masks)) | USBD_EP_RC_W0_MASK | ((type) << USBD_EP_TYPE_POS) | ((kind) << USBD_EP_KIND_POS) | ((address) << USBD_EP_ADDRESS_POS))

/*Set or clear the rw bits while preserving all other bits.*/
#define USBD_EP_SET_RW(reg, rw_masks) ((((reg) & ~USBD_EP_T_MASK) | USBD_EP_RC_W0_MASK) | (rw_masks))
#define USBD_EP_CLEAR_RW(reg, rw_masks) ((((reg) & ~USBD_EP_T_MASK) | USBD_EP_RC_W0_MASK) & ~(rw_masks))

/*Clear rc_w0 bits while preserving all other bits.*/
#define USBD_EP_CLEAR_RC_W0(reg, rc_w0_masks) ((((reg) & ~USBD_EP_T_MASK) | USBD_EP_RC_W0_MASK) & ~(rc_w0_masks))

/*Modify the toggle bits while preserving all other bits. To set a toggle bit set the t_flags and the t_masks, to clear a toggle bit set the t_masks only, to preserve the current value don't mask the bits.*/
#define USBD_EP_SET_TOGGLE(reg, t_flags, t_masks) ((((reg) ^ (t_flags)) & (USBD_EP_RW_MASK | (t_masks))) | USBD_EP_RC_W0_MASK)



/*Hardcoding everything that has to do with endpoints.*/

/*The first 24 bytes in the packet memory area are used by the buffer table.*/
#define USBD_ENDPOINT_0_IN_ADDR_OFFSET (0x18U) /*!< The next 64 bytes by endpoint 0 in direction.*/
#define USBD_ENDPOINT_0_OUT_ADDR_OFFSET (0x58U) /*!< The next 64 bytes by endpoint 0 out direction.*/
#define USBD_ENDPOINT_1_IN_ADDR_OFFSET (0x98U) /*!< The next 64 bytes are used by endpoint 1 in direction.*/
#define USBD_ENDPOINT_1_OUT_ADDR_OFFSET (0xD8U) /*!< The next 64 bytes are used by endpoint 1 out direction.*/

#define USBD_FS_MAXPACKETSIZE (0x40U)

#define USBD_ENDPOINT_0_TX_PMA_BUF (uint16_t*)(USBD_SRAM_BASE_ADDR + USBD_ENDPOINT_0_IN_ADDR_OFFSET) /*!< Pointer to endpoint 0 in PMA buffer.*/
#define USBD_ENDPOINT_0_RX_PMA_BUF (uint16_t*)(USBD_SRAM_BASE_ADDR + USBD_ENDPOINT_0_OUT_ADDR_OFFSET) /*!< Pointer to endpoint 0 out PMA buffer.*/

#define USBD_ENDPOINT_1_TX_PMA_BUF  (uint16_t*)(USBD_SRAM_BASE_ADDR + USBD_ENDPOINT_1_IN_ADDR_OFFSET)/*!< Pointer to endpoint 1 in PMA buffer.*/
#define USBD_ENDPOINT_1_RX_PMA_BUF (uint16_t*)(USBD_SRAM_BASE_ADDR + USBD_ENDPOINT_1_OUT_ADDR_OFFSET) /*!< Pointer to endpoint 1 out PMA buffer.*/


/*Hardcoded pma for endpoint 0*/
#define USBD_ENDPOINT_0_CLEAR_TX_ADDR() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable)) = 0x0U; \
}while(0)

#define USBD_ENDPOINT_0_CLEAR_TX_COUNT() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 2) = 0x0U; \
}while(0)

#define USBD_ENDPOINT_0_CLEAR_RX_ADDR() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 4) = 0x0U; \
}while(0)

#define USBD_ENDPOINT_0_CLEAR_RX_COUNT() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 6) = 0x0U; \
}while(0)

#define USBD_ENDPOINT_0_SET_TX_ADDR() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable)) = (uint16_t)USBD_ENDPOINT_0_IN_ADDR_OFFSET; \
}while(0)

#define USBD_ENDPOINT_0_SET_TX_COUNT(count) do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 2) = (uint16_t)(count); \
}while(0)

#define USBD_ENDPOINT_0_SET_RX_ADDR() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 4) = (uint16_t)USBD_ENDPOINT_0_OUT_ADDR_OFFSET; \
}while(0)

#define USBD_ENDPOINT_0_SET_RX_COUNT() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 6) = USBD_SRAM_RX_COUNT_ALLOC(USBD_FS_MAXPACKETSIZE); \
}while(0)

#define USBD_ENDPOINT_0_GET_RX_COUNT() (uint16_t)((*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 6)) & USBD_SRAM_COUNT_MASK)

/*Hardcoded pma for endpoint 1*/

#define USBD_ENDPOINT_1_CLEAR_TX_ADDR() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 8) = 0x0U; \
}while(0)


#define USBD_ENDPOINT_1_CLEAR_TX_COUNT() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 10) = 0x0U; \
}while(0)

#define USBD_ENDPOINT_1_CLEAR_RX_ADDR() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 12) = 0x0U; \
}while(0)

#define USBD_ENDPOINT_1_CLEAR_RX_COUNT() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 14) = 0x0U; \
}while(0)

#define USBD_ENDPOINT_1_SET_TX_ADDR() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 8) = (uint16_t)(USBD_ENDPOINT_1_IN_ADDR_OFFSET); \
}while(0)

#define USBD_ENDPOINT_1_SET_TX_COUNT(count) do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 10) = (uint16_t)(count); \
}while(0)

#define USBD_ENDPOINT_1_SET_RX_ADDR() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 12) = (uint16_t)(USBD_ENDPOINT_1_OUT_ADDR_OFFSET); \
}while(0)

#define USBD_ENDPOINT_1_SET_RX_COUNT() do \
{ \
	*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 14) = USBD_SRAM_RX_COUNT_ALLOC(USBD_FS_MAXPACKETSIZE); \
}while(0)

#define USBD_ENDPOINT_1_GET_RX_COUNT() (uint16_t)((*(uint16_t*)(USBD_SRAM_BASE_ADDR + (USBD->btable) + 14)) & USBD_SRAM_COUNT_MASK)

/*Hardcoded configurations of endpoints.*/
#define USBD_CLEAR_ENDPOINT_0_CONFIGURATION() do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_0_REG; \
	USBD_ENDPOINT_0_CLEAR_TX_ADDR(); \
	USBD_ENDPOINT_0_CLEAR_TX_COUNT(); \
	USBD_ENDPOINT_0_CLEAR_RX_ADDR(); \
	USBD_ENDPOINT_0_CLEAR_RX_COUNT(); \
	ep_val = USBD_EP_CONFIGURATION(ep_val, 0x0U, 0x0U, USBD_ENDPOINT_0, 0x0U, USBD_EP_T_MASK); \
	(!_MACRO_GET_BIT(ep_val, USBD_EP_CTR_RX_POS)) ? (_MACRO_SET_BIT(ep_val, USBD_EP_CTR_RX_POS)) : (_MACRO_CLEAR_BIT(ep_val, USBD_EP_CTR_RX_POS)); \
	(!_MACRO_GET_BIT(ep_val, USBD_EP_CTR_TX_POS)) ? (_MACRO_SET_BIT(ep_val, USBD_EP_CTR_TX_POS)) : (_MACRO_CLEAR_BIT(ep_val, USBD_EP_CTR_TX_POS)); \
	 *USBD_ENDPOINT_0_REG = ep_val; \
}while(0)

#define USBD_CLEAR_ENDPOINT_1_CONFIGURATION() do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_1_REG; \
	USBD_ENDPOINT_1_CLEAR_TX_ADDR(); \
	USBD_ENDPOINT_1_CLEAR_TX_COUNT(); \
	USBD_ENDPOINT_1_CLEAR_RX_ADDR(); \
	USBD_ENDPOINT_1_CLEAR_RX_COUNT(); \
	ep_val = USBD_EP_CONFIGURATION(ep_val, 0x0U, 0x0U, USBD_ENDPOINT_1, 0x0U, USBD_EP_T_MASK); \
	(!_MACRO_GET_BIT(ep_val, USBD_EP_CTR_RX_POS)) ? (_MACRO_SET_BIT(ep_val, USBD_EP_CTR_RX_POS)) : (_MACRO_CLEAR_BIT(ep_val, USBD_EP_CTR_RX_POS)); \
	(!_MACRO_GET_BIT(ep_val, USBD_EP_CTR_TX_POS)) ? (_MACRO_SET_BIT(ep_val, USBD_EP_CTR_TX_POS)) : (_MACRO_CLEAR_BIT(ep_val, USBD_EP_CTR_TX_POS)); \
	 *USBD_ENDPOINT_1_REG = ep_val; \
}while(0)

#define USBD_SET_ENDPOINT_0_CONFIGURATION() do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_0_REG; \
	USBD_ENDPOINT_0_SET_TX_ADDR(); \
	USBD_ENDPOINT_0_SET_RX_ADDR(); \
	USBD_ENDPOINT_0_SET_RX_COUNT(); \
	*USBD_ENDPOINT_0_REG = USBD_EP_CONFIGURATION(ep_val, USBD_HW_EP_TYPE_CONTROL, 0x0U, USBD_ENDPOINT_0, (USBD_EP_STAT_RX_VALID | USBD_EP_STAT_TX_NAK), USBD_EP_T_MASK); \
}while(0)

#define USBD_SET_ENDPOINT_1_CONFIGURATION() do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_1_REG; \
	USBD_ENDPOINT_1_SET_TX_ADDR(); \
	USBD_ENDPOINT_1_SET_RX_ADDR(); \
	USBD_ENDPOINT_1_SET_RX_COUNT(); \
	*USBD_ENDPOINT_1_REG = USBD_EP_CONFIGURATION(ep_val, USBD_HW_EP_TYPE_BULK, 0x0U, USBD_ENDPOINT_1, (USBD_EP_STAT_RX_VALID | USBD_EP_STAT_TX_NAK), USBD_EP_T_MASK); \
}while(0)

/*Generic commands.*/

#define USBD_ENDPOINT_SET_TX_STALL(ep_num) do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_N_REG(ep_num); \
	if (_MACRO_GET_BIT_VAL(ep_val, USBD_EP_STAT_MASK, USBD_EP_STAT_TX_POS) != USBD_EP_STAT_DISABLED) \
	*USBD_ENDPOINT_N_REG(ep_num) = USBD_EP_SET_TOGGLE(ep_val, USBD_EP_STAT_TX_STALL, USBD_EP_STAT_TX_MASK); \
}while(0)

#define USBD_ENDPOINT_SET_RX_STALL(ep_num) do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_N_REG(ep_num); \
	if (_MACRO_GET_BIT_VAL(ep_val, USBD_EP_STAT_MASK, USBD_EP_STAT_RX_POS) != USBD_EP_STAT_DISABLED) \
	*USBD_ENDPOINT_N_REG(ep_num) = USBD_EP_SET_TOGGLE(ep_val, USBD_EP_STAT_RX_STALL, USBD_EP_STAT_RX_MASK); \
}while(0)

#define USBD_ENDPOINT_CLEAR_TX_STALL(ep_num) do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_N_REG(ep_num); \
	if (_MACRO_GET_BIT_VAL(ep_val, USBD_EP_STAT_MASK, USBD_EP_STAT_TX_POS) == USBD_EP_STAT_STALL) \
	*USBD_ENDPOINT_N_REG(ep_num) = USBD_EP_SET_TOGGLE(ep_val, USBD_EP_STAT_TX_NAK, (USBD_EP_STAT_TX_MASK | USBD_EP_DTOG_TX_MASK)); \
}while(0)

#define USBD_ENDPOINT_CLEAR_RX_STALL(ep_num) do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_N_REG(ep_num); \
	if (_MACRO_GET_BIT_VAL(ep_val, USBD_EP_STAT_MASK, USBD_EP_STAT_RX_POS) == USBD_EP_STAT_STALL) \
	*USBD_ENDPOINT_N_REG(ep_num) = USBD_EP_SET_TOGGLE(ep_val, USBD_EP_STAT_RX_VALID, (USBD_EP_STAT_RX_MASK | USBD_EP_DTOG_RX_MASK)); \
}while(0)

#define USBD_ENDPOINT_GET_STALL(ep_num, dir) !(dir) \
	? (_MACRO_GET_BIT_VAL(*USBD_ENDPOINT_N_REG(ep_num), USBD_EP_STAT_MASK, USBD_EP_STAT_RX_POS) != USBD_EP_STAT_STALL) ? 0x0U : 0x1U \
	: (_MACRO_GET_BIT_VAL(*USBD_ENDPOINT_N_REG(ep_num), USBD_EP_STAT_MASK, USBD_EP_STAT_TX_POS) != USBD_EP_STAT_STALL) ? 0x0U : 0x1U


#define USBD_ENDPOINT_SET_TX_VALID(ep_num) do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_N_REG(ep_num); \
	*USBD_ENDPOINT_N_REG(ep_num) = USBD_EP_SET_TOGGLE(ep_val, USBD_EP_STAT_TX_VALID, USBD_EP_STAT_TX_MASK); \
}while(0)

#define USBD_ENDPOINT_SET_RX_VALID(ep_num) do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_N_REG(ep_num); \
	*USBD_ENDPOINT_N_REG(ep_num) = USBD_EP_SET_TOGGLE(ep_val, USBD_EP_STAT_RX_VALID, USBD_EP_STAT_RX_MASK); \
}while(0)

#define USBD_ENDPOINT_GET_KIND(ep_num) GET_BIT(*USBD_ENDPOINT_N_REG(ep_num), USBD_EP_KIND_MASK)

/*Hardcoded endpoint 0 commands.*/

#define USBD_ENDPOINT_0_SET_STALL() do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_0_REG; \
	*USBD_ENDPOINT_0_REG = USBD_EP_SET_TOGGLE(ep_val, (USBD_EP_STAT_RX_STALL | USBD_EP_STAT_TX_STALL), (USBD_EP_STAT_RX_MASK | USBD_EP_STAT_TX_MASK)); \
}while(0)

#define USBD_ENDPOINT_0_TRANSMIT_ZLP() do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_0_REG; \
	USBD_ENDPOINT_0_SET_TX_COUNT(0); \
	*USBD_ENDPOINT_0_REG = USBD_EP_SET_TOGGLE(ep_val, USBD_EP_STAT_TX_VALID, USBD_EP_STAT_TX_MASK); \
}while(0)

#define USBD_ENDPOINT_0_SET_KIND() do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_0_REG; \
	*USBD_ENDPOINT_0_REG = USBD_EP_SET_RW(ep_val, USBD_EP_STATUS_OUT_MASK); \
}while(0)

#define USBD_ENDPOINT_0_CLEAR_KIND() do \
{ \
	uint16_t ep_val = *USBD_ENDPOINT_0_REG; \
	*USBD_ENDPOINT_0_REG = USBD_EP_CLEAR_RW(ep_val, USBD_EP_STATUS_OUT_MASK); \
}while(0)


#ifdef __cplusplus
}
#endif
#endif /*endif STM32L412_DEF_H*/