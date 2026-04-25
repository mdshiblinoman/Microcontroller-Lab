#include <stdio.h>

int main(void)
{
    /* Fixed decimal inputs: change these values as needed. */
    int a = 20;
    int b = 10;
    int is_greater;

    __asm volatile(
        "CMP %1, %2\n"
        "MOVGT %0, #1\n"
        "MOVLE %0, #0\n"
        : "=r"(is_greater)
        : "r"(a), "r"(b)
        : "cc");

    if (is_greater)
        printf("%d is greater than %d\n", a, b);
    else
        printf("%d is not greater than %d\n", a, b);

    return 0;
}
