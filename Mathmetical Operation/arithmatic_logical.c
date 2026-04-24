#include <stdint.h>

/* RCC and GPIO Registers */
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))

#define GPIOC_BASE 0x40011000
#define GPIOC_CRH (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR (*(volatile unsigned int *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR (*(volatile unsigned int *)(GPIOC_BASE + 0x14))

/* Simple delay */
void delay(void)
{
    for (volatile int i = 0; i < 500000; i++)
        ;
}

int main(void)
{
    /* Enable GPIOC clock */
    RCC_APB2ENR |= (1 << 4);

    /* Configure PC13 as output */
    GPIOC_CRH &= ~(0x00F00000);
    GPIOC_CRH |= (1 << 21); //(2<<20)

    uint32_t apsr;

    while (1)
    {
        /* =====================================================
           🔴 ARITHMETIC: NEGATIVE FLAG (N)
        ===================================================== */
        __asm volatile(
            "MOV R0, #5      \n"
            "MOV R1, #-6     \n"
            "ADDS R2, R0, R1 \n" // -1 → N = 1
            "MRS %0, APSR    \n" // MRS aspr ,APSR
            : "=r"(apsr)
            :
            : "cc");

        if (apsr & (1 << 31))
            GPIOC_BRR = (1 << 13); // LED ON
        else
            GPIOC_BSRR = (1 << 13); // LED OFF

        delay();

        /* =====================================================
           🟢 ARITHMETIC: ZERO FLAG (Z)
        ===================================================== */
        __asm volatile(
            "MOV R0, #5      \n"
            "MOV R1, #-5     \n"
            "ADDS R2, R0, R1 \n" // 0 → Z = 1
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            :
            : "cc");

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =====================================================
           🔵 ARITHMETIC: OVERFLOW FLAG (V)
        ===================================================== */
        __asm volatile(
            "LDR R0, =2147483647 \n"
            "MOV R1, #1          \n"
            "ADDS R2, R0, R1     \n" // overflow → V = 1
            "MRS %0, APSR        \n"
            : "=r"(apsr)
            :
            : "cc");

        if (apsr & (1 << 28))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =====================================================
           🟡 SATURATION: Q FLAG
        ===================================================== */
        __asm volatile(
            "MOV R0, #300     \n"
            "SSAT R1, #8, R0  \n"
            "MRS %0, APSR     \n"
            : "=r"(apsr)
            :
            : "cc");

        if (apsr & (1 << 27))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =====================================================
           🔷 LOGICAL OPERATION: ANDS
           Result = 0 → Z = 1
        ===================================================== */
        __asm volatile(
            "MOV R0, #0x0F      \n"
            "MOV R1, #0xF0      \n"
            "ANDS R2, R0, R1    \n" // 0x00
            "MRS %0, APSR       \n"
            : "=r"(apsr)
            :
            : "cc");

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =====================================================
           🔷 LOGICAL OPERATION: ORRS
           Result ≠ 0 → Z = 0
        ===================================================== */
        __asm volatile(
            "MOV R0, #0x0F      \n"
            "MOV R1, #0xF0      \n"
            "ORRS R2, R0, R1    \n" // 0xFF
            "MRS %0, APSR       \n"
            : "=r"(apsr)
            :
            : "cc");

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =====================================================
           🔷 LOGICAL OPERATION: EORS
           Result = 0 → Z = 1
        ===================================================== */
        __asm volatile(
            "MOV R0, #0xFF      \n"
            "MOV R1, #0xFF      \n"
            "EORS R2, R0, R1    \n" // 0x00
            "MRS %0, APSR       \n"
            : "=r"(apsr)
            :
            : "cc");

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =====================================================
           🔴 LOGICAL: NEGATIVE FLAG (N)
        ===================================================== */
        __asm volatile(
            "MOV R0, #0x80      \n"
            "MOV R1, #0x00      \n"
            "ORRS R2, R0, R1    \n" // MSB = 1 → N = 1
            "MRS %0, APSR       \n"
            : "=r"(apsr)
            :
            : "cc");

        if (apsr & (1 << 31))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();
    }
}