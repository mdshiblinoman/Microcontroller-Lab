#include <stdint.h>
#include <stdio.h>

/* RCC and GPIO Registers */
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))

#define GPIOC_BASE 0x40011000
#define GPIOC_CRH (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR (*(volatile unsigned int *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR (*(volatile unsigned int *)(GPIOC_BASE + 0x14))

/* Delay */
void delay(void)
{
    for (volatile int i = 0; i < 300000; i++)
        ;
}

/* LED Control (PC13: Active LOW) */
void led_on() { GPIOC_BRR = (1 << 13); }
void led_off() { GPIOC_BSRR = (1 << 13); }

/* Blink function */
void blink(int times)
{
    for (int i = 0; i < times; i++)
    {
        led_on();
        delay();

        led_off();
        delay();
    }
    delay(); // gap
}

int main(void)
{
    /* Enable GPIOC clock */
    RCC_APB2ENR |= (1 << 4);

    /* Configure PC13 as Output (2 MHz Push-Pull) */
    GPIOC_CRH &= ~(0xF << 20); // Clear PC13 bits (00F00000)
    GPIOC_CRH |= (0x2 << 20);  // Output mode, max speed 2 MHz (0x2 << 20 = 0x00200000)

    uint32_t apsr;
    int32_t result;

    int a = 20;
    int b = 5;

    while (1)
    {
        if (b == 0)
        {
            printf("Division by zero is not allowed.\n");
            blink(10); // error indication
            continue;
        }

        __asm volatile(
            "MOV R0, %1      \n"
            "MOV R1, %2      \n"
            "SDIV R2, R0, R1 \n" // division
            "MOV %0, R2      \n"
            "CMP R2, #0      \n" // 👈 flags update (VERY IMPORTANT)
            "MRS %1, APSR    \n"
            : "=r"(result), "=r"(apsr)
            : "r"(a), "r"(b)
            : "r0", "r1", "r2", "cc");

        printf("Division: %d / %d\n", a, b);
        printf("Quotient = %ld\n", (long)result);
        printf("Remainder = %ld\n", (long)(a - (result * b)));

        /* N flag (Negative) */
        if (apsr & (1 << 31))
            blink(1);

        /* Z flag (Zero) */
        if (apsr & (1 << 30))
            blink(2);

        /* C flag (Carry) */
        if (apsr & (1 << 29))
            blink(3);

        /* V flag (Overflow) */
        if (apsr & (1 << 28))
            blink(4);

        /* Q flag (Saturation - usually unused এখানে) */
        if (apsr & (1 << 27))
            blink(5);

        delay();
    }
}