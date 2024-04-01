#include "stm32l412_def.h"
#include "rcc.h"

extern uint32_t hclk;

/*******************************************************************************
- Private functions.
******************************************************************************/

/**
 * @brief Set the cpu to max frequency (80Mhz) using the external oscillator (8Mhz) and pll.
 * @param  
 * @return SYS_ERR_CODE_TIMEOUT or SYS_ERR_CODE_OK
 */
system_error_code_type rcc_set_cpu_max_freq(void)
{
	uint32_t start_timer;

	/*If the HSE is off turn it on*/
	if (!_MACRO_GET_BIT(RCC->cr, RCC_HSEON_POS))
	{
		/*Turn on external oscillator.*/
		_MACRO_SET_BIT(RCC->cr, RCC_HSEON_POS);

		/*Wait until external oscillator is ready.*/
		start_timer = get_tick();
		while (!_MACRO_GET_BIT(RCC->cr, RCC_HSERDY_POS))
		{
			if (get_tick() - start_timer > RCC_MAX_TIMEOUT)
			{
				return SYS_ERR_CODE_TIMEOUT;
			}
		}
	}

	/*If the PLL is not used as source clock then configure it.*/
	if (_MACRO_GET_BIT_VAL(RCC->cfgr, RCC_SWS_MASK, RCC_SWS_POS) != RCC_SW_PLL)
	{
		/*If the pll is on turn it off*/
		if (_MACRO_GET_BIT(RCC->cr, RCC_PLLON_POS))
		{
			/*Turn off pll*/
			_MACRO_CLEAR_BIT(RCC->cr, RCC_PLLON_POS);

			/*Wait until the pll is unlocked.*/
			start_timer = get_tick();
			while (_MACRO_GET_BIT(RCC->cr, RCC_PLLRDY_POS))
			{
				if (get_tick() - start_timer > RCC_MAX_TIMEOUT)
				{
					return SYS_ERR_CODE_TIMEOUT;
				}
			}
		}
		
		/*Clear pll*/
		RCC->pllcfgr = 0x0U;
		/*Set pll source, pllm, plln, pllr values.*/
		_MACRO_SET_BITS(RCC->pllcfgr, ((RCC_PLLSRC_HSE << RCC_PLLSRC_POS) | (0x14U << RCC_PLLN_POS)));
		/*Enable pllr output*/
		_MACRO_SET_BIT(RCC->pllcfgr, RCC_PLLREN_POS);
		/*Turn on pll*/
		_MACRO_SET_BIT(RCC->cr, RCC_PLLON_POS);
		/*Wait until the pll is unlocked.*/
		start_timer = get_tick();
		while (!_MACRO_GET_BIT(RCC->cr, RCC_PLLRDY_POS))
		{
			if (get_tick() - start_timer > RCC_MAX_TIMEOUT)
			{
				return SYS_ERR_CODE_TIMEOUT;
			}
		}
	}

	/*Set the flash latency to 2 wait states */
	FLASH_SET_LATENCY_4_WAIT_STATES();

	/*Wait until the flash latency is 4 wait states*/
	start_timer = get_tick();
	while (_MACRO_GET_BIT_VAL(FLASH->acr, FLASH_LATENCY_MASK, FLASH_LATENCY_POS) != FLASH_LATENCY_4_WAIT_STATES)
	{
		if (get_tick() - start_timer > RCC_MAX_TIMEOUT)
		{
			return SYS_ERR_CODE_TIMEOUT;
		}
	}

	/*Set the source clock, and select hsi16 as the backup clock.*/
	_MACRO_SET_BITS(RCC->cfgr, ((RCC_SW_PLL << RCC_SW_POS) | (0x1U << RCC_STOPWUCK_POS)));

	/*Wait until hclk source is set properly*/
	start_timer = get_tick();
	while (_MACRO_GET_BIT_VAL(RCC->cfgr, RCC_SWS_MASK, RCC_SWS_POS) != RCC_SW_PLL)
	{
		if (get_tick() - start_timer > RCC_MAX_TIMEOUT)
		{
			return SYS_ERR_CODE_TIMEOUT;
		}
	}
	hclk = 80000000UL; 
	set_tick(); /*Reset the systick.*/
	return SYS_ERR_CODE_OK;
}

/**
* @brief Initialize the usb clock using the HSI48 oscillator as source.
* @param  
*/
system_error_code_type rcc_set_usb_src_hsi48(void)
{
	/*Enable the hsi48 oscillator if it's off.*/
	if (!_MACRO_GET_BIT(RCC->crrcr, RCC_HSI48ON_POS))
	{
		/*Turn on the hsi48 oscillator*/
		_MACRO_SET_BIT(RCC->crrcr, RCC_HSI48ON_POS);
		/*Wait until the hsi48 oscillator is stable*/
		uint32_t start_timer = get_tick();
		while (!_MACRO_GET_BIT(RCC->crrcr, RCC_HSI48RDY_POS))
		{
			if (get_tick() - start_timer > RCC_MAX_TIMEOUT)
			{
				return SYS_ERR_CODE_TIMEOUT;
			}
		}
	}
	/*Select the hsi48 as the usb source*/
	_MACRO_CLEAR_BIT_VAL(RCC->ccipr, RCC_CLK48SEL_MASK, RCC_CLK48SEL_POS);
	_MACRO_SET_BIT_VAL(RCC->ccipr, RCC_CLK48SEL_HSI48, RCC_CLK48SEL_POS);
	return SYS_ERR_CODE_OK;
}