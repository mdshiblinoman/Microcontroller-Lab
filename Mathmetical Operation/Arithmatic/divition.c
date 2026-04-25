#include <stdint.h>
#include <stdio.h>

volatile int32_t quotient;
volatile int32_t remainder;

int main(void)
{
    register int32_t a = 20;
    register int32_t b = 7;

    __asm volatile(
        "MOV %0, #0        \n" /* quotient = 0 */
        "MOV %1, %2        \n" /* remainder = a */
        "CMP %3, #0        \n"
        "BEQ 2f            \n" /* if b == 0, skip loop */
        "1:                \n"
        "CMP %1, %3        \n"
        "BLT 2f            \n" /* stop when remainder < b */
        "SUBS %1, %1, %3   \n"
        "ADDS %0, %0, #1   \n"
        "B 1b              \n"
        "2:                \n"
        : "=&r"(quotient), "=&r"(remainder)
        : "r"(a), "r"(b)
        : "cc");

    if (b == 0)
    {
        printf("Division by zero is not allowed.\n");
    }
    else
    {
        printf("Division: %ld / %ld\n", (long)a, (long)b);
        printf("Quotient = %ld\n", (long)quotient);
        printf("Remainder = %ld\n", (long)remainder);
    }

    while (1)
    {
    }

    return 0;
}
