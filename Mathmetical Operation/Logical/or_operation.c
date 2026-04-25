#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Fixed inputs: change these two values as needed. */
    uint32_t a = 252645135;
    uint32_t b = 16711935;
    uint32_t result;

    __asm volatile(
        "ORR %0, %1, %2\n"
        : "=r"(result)
        : "r"(a), "r"(b)
        : "cc");

    printf("A      = %lu\n", (unsigned long)a);
    printf("B      = %lu\n", (unsigned long)b);
    printf("A | B  = %lu\n", (unsigned long)result);

    return 0;
}
