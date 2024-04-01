#ifndef RCC_H
#define RCC_H

#include "stm32l412_system.h"


#ifdef __cplusplus
extern "C" {
#endif





/*******************************************************************************
	- RCC functions
******************************************************************************/
system_error_code_type rcc_set_cpu_max_freq(void);
system_error_code_type rcc_set_usb_src_hsi48(void);








#ifdef __cplusplus
}
#endif
#endif /*endif RCC_H*/


