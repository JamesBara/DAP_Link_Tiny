#ifndef MACROS_H
#define MACROS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*Use for single bits*/
#define _MACRO_SET_BIT(reg, bit_pos) ((reg) |= (0x1U << (bit_pos)))
#define _MACRO_CLEAR_BIT(reg, bit_pos) ((reg) &= ~(0x1U << (bit_pos)))
#define _MACRO_GET_BIT(reg, bit_pos) (!((reg) & (0x1U << (bit_pos)))) ? (0x0U) : (0x1U)
#define _MACRO_TOGGLE_BIT(reg, bit_pos) ((reg) ^= (0x1U << (bit_pos)))

/*Use for values represented by multible bits (ex. 0x2U)*/
#define _MACRO_SET_BIT_VAL(reg, bit_val, bit_pos) ((reg) |= ((bit_val) << (bit_pos)))
#define _MACRO_CLEAR_BIT_VAL(reg, bit_mask, bit_pos) ((reg) &= ~((bit_mask) << (bit_pos)))
#define _MACRO_GET_BIT_VAL(reg, bit_mask, bit_pos) (((reg) & ((bit_mask) << (bit_pos))) >> (bit_pos)) /*!< Returns the masked bits.*/
#define _MACRO_TOGGLE_BIT_VAL(reg, bit_val, bit_pos) ((reg) ^= ((bit_val) << (bit_pos)))

/*Use with multiple values in different positions (or the values first)*/
#define _MACRO_SET_BITS(reg, bit_val) ((reg) |= (bit_val))
#define _MACRO_CLEAR_BITS(reg, bit_val) ((reg) &= ~(bit_val))
#define _MACRO_GET_BITS(reg, bit_val) ((reg) & (bit_val))


/*Helpful macros.*/
#define _MACRO_MIN(x, y) ((x) < (y)) ? (x) : (y)
#define _MACRO_MAX(x, y) ((x) > (y)) ? (x) : (y)
#define _MACRO_SWAP16(x) ((((x) & 0xFF00U) >> 0x8U) | (((x) & 0xFFU) << 0x8U))
#define _MACRO_SWAP32(x) ((((x) & 0xFF000000U) >> 0x18U) | (((x) & 0xFF0000U) >> 0x8U) | (((x) & 0xFF) << 0x18U) | (((x) & 0xFF00U) << 0x8U))

#define _MACRO_IS_ALIGNED_HELPER(p, bytes) (!(((uintptr_t)(const void *)(p)) & ((bytes) - 1))) ? true : false 
#define _MACRO_IS_ALIGNED16(x) _MACRO_IS_ALIGNED_HELPER(x, 2)
#define _MACRO_IS_ALIGNED32(x) _MACRO_IS_ALIGNED_HELPER(x, 4)


/**
 * @brief Custom Assert function in case of an error, useful for debugging,
				 user can implement it anyway they like. Default behavior
				 is to set a software breakpoint.
 * @param file Value of __FILE__ (shows the file that produced assert).
 * @param line Value of __LINE__ (show the line that produced the assert).
 * @param func Value of __func__ (show the function that produced the assert).
 * @param val Value of whatever triggered the assertation
*/
static inline void assert_func(const char* file, int line, const char* func, const char* val)
{
	(void)file;
	(void)line;
	(void)func;
	(void)val;
	__asm__("BKPT");
}

#ifdef NDEBUG
#define ASSERT(pr) ((void)0)
#else
#define ASSERT(pr) ((pr) ? (void)0 : assert_func(__FILE__, __LINE__, __func__, #pr))
#endif /*NDEBUG*/

#ifdef __cplusplus
}
#endif
#endif //endif MACROS_H