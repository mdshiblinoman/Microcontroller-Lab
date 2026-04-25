#include <stdint.h>

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
    GPIOC_CRH &= ~(0x00F00000);
    GPIOC_CRH |= (1 << 21);

    uint32_t apsr;

    /* 🔷 User input variables */
    int a = 5;
    int b = -6;

    while (1)
    {
        __asm volatile(
            "MOV R0, %1      \n"
            "MOV R1, %2      \n"
            "ADDS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            : "r"(a), "r"(b)
            : "cc");

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