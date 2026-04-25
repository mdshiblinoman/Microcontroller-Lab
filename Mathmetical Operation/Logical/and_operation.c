#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Fixed decimal inputs: change these values as needed. */
    uint32_t a = 23;
    uint32_t b = 45;
    uint32_t result;

    __asm volatile(
        "AND %0, %1, %2\n"
        : "=r"(result)
        : "r"(a), "r"(b)
        : "cc");

    printf("A      = %lu\n", (unsigned long)a);
    printf("B      = %lu\n", (unsigned long)b);
    printf("A & B  = %lu\n", (unsigned long)result);

    return 0;
}
