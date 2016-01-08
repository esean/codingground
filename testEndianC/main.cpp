#include <stdio.h>
#include <inttypes.h>

// return 0 for big endian, 1 for little endian.
int is_little_endian()
{
    volatile uint32_t i=0x01234567;
    return (*((uint8_t*)(&i))) == 0x67;
}

int is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };

    return e.c[0];
}

int main()
{
	printf("is_little_endian() = %s\n", is_little_endian() ? "little" : "big");
	printf("is_big_endian() = %s\n", is_big_endian() ? "big" : "little");

	return 0;
}

