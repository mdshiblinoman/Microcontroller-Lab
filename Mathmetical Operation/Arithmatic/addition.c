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

/* LED ON/OFF */
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
    delay(); // gap between flags
}

int main(void)
{
    /* Enable GPIOC clock */
    RCC_APB2ENR |= (1 << 4);

    /* Configure PC13 as output */
    GPIOC_CRH &= ~(0x00F00000); // Clear PC13 bits (00F00000)
    GPIOC_CRH |= (1 << 21);     // Output mode, max speed 2 MHz (0x2 << 20 = 0x00200000)

    uint32_t apsr;
    int32_t result;

    /* 🔷 User input variables */
    int a = 5;
    int b = -6;

    while (1)
    {
        __asm volatile(
            "MOV R0, %1      \n"       // Load a into R0
            "MOV R1, %2      \n"       // Load b into R1
            "ADDS R2, R0, R1 \n"       // R2 = R0 + R1, updates flags
            "MOV %0, R2      \n"       // Store result back to C variable
            "MRS %1, APSR    \n"       // Store APSR flags back to C variable
            : "=r"(result), "=r"(apsr) // Output operands
            : "r"(a), "r"(b)           // Input operands
            : "r0", "r1", "r2", "cc"); // Clobbered registers and condition codes

        printf("Addition: %d + %d = %ld\n", a, b, (long)result);

        /* 🔴 N flag (bit 31) */
        if (apsr & (1 << 31))
            blink(1);

        /* 🟢 Z flag (bit 30) */
        if (apsr & (1 << 30))
            blink(2);

        /* 🔵 C flag (bit 29) */
        if (apsr & (1 << 29))
            blink(3);

        /* 🟡 V flag (bit 28) */
        if (apsr & (1 << 28))
            blink(4);

        /* ⚪ Q flag (bit 27) */
        if (apsr & (1 << 27))
            blink(5);

        delay();
    }
}