#include <stdint.h>
#include <stdio.h>

volatile int32_t is_equal;

int main(void)
{
    /* Change these values to test user input. */
    register int32_t a = 25;
    register int32_t b = 25;

    __asm volatile(
        "CMP %1, %2\n"
        "BEQ 1f\n"
        "MOV %0, #0\n"
        "B 2f\n"
        "1:\n"
        "MOV %0, #1\n"
        "2:\n"
        : "=r"(is_equal)
        : "r"(a), "r"(b)
        : "cc");

    if (is_equal)
    {
        printf("Equal logical result: %ld == %ld (TRUE)\n", (long)a, (long)b);
    }
    else
    {
        printf("Equal logical result: %ld == %ld (FALSE)\n", (long)a, (long)b);
    }

    return 0;
}
