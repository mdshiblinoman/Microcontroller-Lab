# PB1 LED Blink Register Explanation

This document explains the PB1_LED.c program without code blocks. It focuses on each register and the full working sequence.

## Register Map Used

1. RCC base address: 0x40021000
2. RCC APB2ENR register address: RCC base + 0x18
3. GPIOB base address: 0x40010C00
4. GPIOB CRL register address: GPIOB base + 0x00
5. GPIOB BSRR register address: GPIOB base + 0x10
6. GPIOB BRR register address: GPIOB base + 0x14

## What Each Register Does

### RCC APB2ENR

Purpose: Enables clocks for peripherals connected to APB2 bus.

Used bit in this program:
- Bit 3 controls GPIOB clock.
- Writing bit 3 as 1 enables clock for Port B.

Why needed:
- If GPIOB clock is not enabled, GPIOB configuration and output writes have no effect.

### GPIOB CRL

Purpose: Configures mode and type of pins PB0 to PB7.

PB0 configuration field:
- PB0 uses 4 bits in CRL.
- These 4 bits define output/input mode, speed, and type.

Used behavior in this program:
1. Clear PB0 configuration bits first.
2. Write new value for output push-pull at 2 MHz.

Why needed:
- Pin must be configured as output before driving LED high or low.

### GPIOB BSRR

Purpose: Sets GPIO output bits atomically.

Used behavior in this program:
- Writing 1 to bit 0 sets PB0 output HIGH.

Why useful:
- Atomic set operation avoids read-modify-write issues.
- Preferred register for turning output ON.

### GPIOB BRR

Purpose: Resets GPIO output bits.

Used behavior in this program:
- Writing 1 to bit 0 resets PB0 output LOW.

Why useful:
- Direct and simple way to turn output OFF.

## Step-by-Step Working Path

1. Start the program.
2. Enable GPIOB peripheral clock through RCC APB2ENR bit 3.
3. Configure PB0 as output push-pull in GPIOB CRL.
4. Enter infinite loop.
5. Set PB0 HIGH using GPIOB BSRR so LED turns ON.
6. Wait using software delay loop.
7. Set PB0 LOW using GPIOB BRR so LED turns OFF.
8. Wait again using software delay loop.
9. Repeat forever, creating LED blinking.

## Delay Logic

The delay is created by a simple empty loop. This gives approximate timing only and depends on clock speed and compiler optimization.

## Final Result

After initialization, PB0 is continuously toggled between HIGH and LOW states with delay in between, so the LED connected to PB0 blinks repeatedly.
