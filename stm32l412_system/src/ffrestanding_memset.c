#include <string.h>
#include <stdint.h>

/**
* @brief Extremely basic memset.
* @param src Void pointer to buffer.
* @param c Value to set the memory to.
* @param n Buffer size.
* @return Pointer to source.
*/
void *memset(void *src, int c, size_t n)
{
	volatile uint8_t *s = src;

	while (n--)
	{
		*s++ = (uint8_t)c;
	}

	return src;
}