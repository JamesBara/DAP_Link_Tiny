#ifndef STM32L412_SYSTEM_H
#define STM32L412_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <stdint.h>
#include <stddef.h>

typedef enum
{
	SYS_ERR_CODE_OK = 0x0U,
	SYS_ERR_CODE_ERROR = 0x1U,
	SYS_ERR_CODE_BUSY = 0x2U,
	SYS_ERR_CODE_TIMEOUT = 0x3U
}system_error_code_type;


void __attribute__((noinline)) cpu_busy_wait(uint32_t max);
uint32_t get_tick(void);
void set_tick(void);
void delay(uint32_t timeout);

#ifdef __cplusplus
}
#endif
#endif //endif STM32L412_SYSTEM_H