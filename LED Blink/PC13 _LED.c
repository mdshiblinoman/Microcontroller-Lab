#include <stdint.h>

/* RCC register */
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))

/* GPIOC register */
#define GPIOC_BASE 0x40011000
#define GPIOC_CRH (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR (*(volatile uint32_t *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

void delay(void)
{
    for (volatile int i = 0; i < 500000; i++)
        ;
}

int main(void)
{
    /* 1. Enable GPIOC clock */
    RCC_APB2ENR |= (1 << 4);

    /* 2. Configure PC13 as output push-pull */
    GPIOC_CRH &= ~(0xF << 20); // clear PC13 bits(00F00000)
    GPIOC_CRH |= (0x2 << 20);  // output mode (2 MHz)

    while (1)
    {
        /* LED ON (ACTIVE LOW → RESET pin) */
        GPIOC_BRR = (1 << 13);
        delay();

        /* LED OFF */
        GPIOC_BSRR = (1 << 13);
        delay();
    }
}