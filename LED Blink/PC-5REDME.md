# PA5 LED Blink Step-by-Step Guide

This document explains how the PA5 LED blink program works in [LED Blink/PA5_LED.c](LED%20Blink/PA5_LED.c) without showing code.

## 1. Purpose of the program

The program blinks an LED connected to pin PA5 on an STM32 board.

1. It enables the GPIOA peripheral clock.
2. It configures PA5 as an output pin.
3. It repeatedly turns the LED ON and OFF.
4. It uses a delay loop so the blinking is visible.

## 2. Hardware connection

1. Connect an LED to pin PA5 through a current-limiting resistor.
2. Connect the other side of the LED to GND if your board uses active-high wiring.
3. If your board uses an onboard LED, confirm whether it is active-high or active-low before testing.

## 3. Peripheral clock setup

1. The program first enables the GPIOA clock through the RCC peripheral.
2. Without this clock, the GPIOA registers cannot be used properly.
3. This is the first required step before configuring or driving PA5.

## 4. PA5 pin configuration

1. PA5 is part of the GPIOA low configuration register group.
2. The program clears the existing PA5 configuration bits first.
3. It then sets PA5 to output mode.
4. The selected output speed is 2 MHz.
5. The output type is push-pull, which is suitable for driving an LED.

## 5. Blink operation

1. After configuration, the program enters an infinite loop.
2. In the first half of the loop, PA5 is driven to the ON state.
3. The delay function keeps the LED on long enough to see.
4. In the second half of the loop, PA5 is driven to the OFF state.
5. The delay function runs again.
6. This ON/OFF cycle repeats forever.

## 6. What each GPIO action means

1. Setting PA5 through the GPIO bit set register makes the output go high.
2. Resetting PA5 through the GPIO bit reset register makes the output go low.
3. On many boards, high means LED ON for an external active-high LED.
4. If your LED is wired active-low, the visual ON/OFF result may be reversed.

## 7. Delay behavior

1. The delay is a simple software loop.
2. It is not a precise timer-based delay.
3. The visible blink speed depends on the CPU clock and compiler optimization.

## 8. Step-by-step summary

1. Enable the GPIOA clock.
2. Configure PA5 as output push-pull.
3. Turn the LED ON.
4. Wait.
5. Turn the LED OFF.
6. Wait.
7. Repeat the sequence forever.

## 9. Expected result

When the program runs correctly, the LED connected to PA5 should blink continuously with a visible pause between ON and OFF states.
