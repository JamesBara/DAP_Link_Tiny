#include <string.h>
#include <stdint.h>


/**
 * @brief Extremely basic memcpy.
 * @param dst Void pointer to buffer to copy to.
 * @param src Void pointer to buffer to copy from.
 * @param n Size of buffer.
 * @return Pointer to destination buffer.
*/
void *memcpy(void *dst, const void *src, size_t n)
{
	volatile uint8_t *d = dst;
	const volatile uint8_t *s = src;

	while (n--)
	{
		*d++ = *s++;
	}
	return dst;
}