# PC13 LED Blink Register Explanation

This file explains all registers used in the program in [LED Blink/PC13 _LED.c](LED Blink/PC13 _LED.c).

## 1. What the program does

1. Turns on clock for GPIO port C.
2. Configures pin PC13 as output push-pull.
3. Drives PC13 LOW and HIGH repeatedly to blink LED.
4. Uses a software delay loop between ON and OFF.

## 2. Memory-mapped register addresses

The code accesses peripheral registers directly using fixed addresses.

1. RCC base address: 0x40021000
2. GPIOC base address: 0x40011000
3. Access type is volatile 32-bit, so compiler always reads/writes actual hardware register.

## 3. RCC register used

### RCC_APB2ENR (Address offset 0x18 from RCC base)

Purpose:
Enable clocks for peripherals connected to APB2 bus.

Used bit in this code:
Bit 4 (IOPCEN) to enable GPIOC clock.

Why needed:
If GPIOC clock is not enabled, GPIOC registers will not work correctly.

## 4. GPIO registers used

### GPIOC_CRH (Address offset 0x04 from GPIOC base)

Purpose:
Configure mode and configuration of pins PC8 to PC15.

Used field in this code:
Bits 23:20 for PC13.

Meaning of PC13 4-bit field:
1. MODE13[1:0] (bits 21:20): output speed selection.
2. CNF13[1:0] (bits 23:22): output type selection.

Value configured by code:
MODE13 = 10 (output mode, max speed 2 MHz), CNF13 = 00 (general purpose push-pull).

### GPIOC_BRR (Address offset 0x14 from GPIOC base)

Purpose:
Reset output bits (drive selected pin LOW).

Used bit in this code:
Bit 13.

Effect:
Writing 1 to bit 13 sets PC13 output to 0 (LOW).
For active-low LED wiring, this turns LED ON.

### GPIOC_BSRR (Address offset 0x10 from GPIOC base)

Purpose:
Set output bits (drive selected pin HIGH) using atomic write.

Used bit in this code:
Bit 13 in lower half (set section).

Effect:
Writing 1 to bit 13 sets PC13 output to 1 (HIGH).
For active-low LED wiring, this turns LED OFF.

## 5. Blink sequence step by step

1. Enable GPIOC clock through RCC_APB2ENR bit 4.
2. Clear PC13 configuration bits in GPIOC_CRH.
3. Write output push-pull 2 MHz config to PC13 field in GPIOC_CRH.
4. Write to GPIOC_BRR bit 13 to make PC13 LOW (LED ON for active-low).
5. Wait in delay loop.
6. Write to GPIOC_BSRR bit 13 to make PC13 HIGH (LED OFF for active-low).
7. Wait in delay loop.
8. Repeat forever.

## 6. Important note about PC13 LED logic

Many STM32 boards connect LED so that PC13 works as active-low.

1. PC13 LOW means LED ON.
2. PC13 HIGH means LED OFF.

If your external LED is wired differently, ON and OFF behavior may be reversed.
