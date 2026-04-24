#include <stdint.h>

/* RCC register */
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))

/* GPIOA register */
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_BSRR (*(volatile uint32_t *)(GPIOA_BASE + 0x10))
#define GPIOA_BRR (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

void delay(void)
{
    for (volatile int i = 0; i < 500000; i++)
        ;
}

int main(void)
{
    /* 1. Enable GPIOA clock */
    RCC_APB2ENR |= (1 << 2); // GPIOA enable (bit 2)

    /* 2. Configure PA5 as output push-pull */
    GPIOA_CRL &= ~(0xF << 20); // clear PA5 bits
    GPIOA_CRL |= (0x2 << 20);  // output mode 2 MHz

    while (1)
    {
        /* LED ON */
        GPIOA_BSRR = (1 << 5);
        delay();

        /* LED OFF */
        GPIOA_BRR = (1 << 5);
        delay();
    }
}