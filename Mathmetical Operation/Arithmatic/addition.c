#include <stdint.h>
#include <stdio.h>

volatile int32_t result;

int main(void)
{
    /* Change these values to test different user inputs. */
    register int32_t a = 12;
    register int32_t b = 8;

    __asm volatile(
        "ADDS %0, %1, %2\n"
        : "=r"(result)
        : "r"(a), "r"(b)
        : "cc");

    printf("Addition result = %ld\n", (long)result);

    return 0;
}
