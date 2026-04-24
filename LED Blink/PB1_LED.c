#include <stdint.h>

/* RCC register */
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))

/* GPIOB register */
#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_BSRR (*(volatile uint32_t *)(GPIOB_BASE + 0x10))
#define GPIOB_BRR (*(volatile uint32_t *)(GPIOB_BASE + 0x14))

void delay(void)
{
    for (volatile int i = 0; i < 500000; i++)
        ;
}

int main(void)
{
    /* 1. Enable GPIOB clock */
    RCC_APB2ENR |= (1 << 3); // GPIOB enable (bit 3)

    /* 2. Configure PB0 as output push-pull */
    GPIOB_CRL &= ~(0xF << 0); // clear PB0 bits
    GPIOB_CRL |= (0x2 << 0);  // output mode 2 MHz

    while (1)
    {
        /* LED ON */
        GPIOB_BSRR = (1 << 0);
        delay();

        /* LED OFF */
        GPIOB_BRR = (1 << 0);
        delay();
    }
}