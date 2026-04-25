#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Fixed decimal inputs: change these values as needed. */
    int32_t a = 10;
    int32_t b = 20;
    uint32_t is_less;

    __asm volatile(
        "CMP %1, %2\n"
        "MOVLT %0, #1\n"
        "MOVGE %0, #0\n"
        : "=r"(is_less)
        : "r"(a), "r"(b)
        : "cc");

    if (is_less)
    {
        printf("Result: %ld is less than %ld\n", (long)a, (long)b);
    }
    else
    {
        printf("Result: %ld is not less than %ld\n", (long)a, (long)b);
    }

    return 0;
}
