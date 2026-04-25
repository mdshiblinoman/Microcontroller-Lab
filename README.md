# Microcontroller Lab

This repository contains STM32 register-level practice programs for:

1. LED blinking on different GPIO pins.
2. Arithmetic operations and flag checking (APSR flags).
3. Logical/comparison operations and flag checking.

---

## 1. Folder Overview

- `LED Blink/`
	- `PA5_LED.c`
	- `PB1_LED.c`
	- `PC13 _LED.c`
- `Mathmetical Operation/`
	- `arithmatic_logical.c`
	- `Arithmatic/`
		- `addition.c`
		- `subtraction.c`
		- `multiplication.c`
		- `divition.c`
	- `Logical/`
		- `and_operation.c`
		- `or_operation.c`
		- `xor_operation.c`
		- `xnor_operation.c`
		- `equal.c`
		- `gather_than.c`
		- `less_than.c`

---

## 2. Before You Run (Common Steps)

Follow these steps for every file:

1. Open your STM32 project in your IDE (Keil, STM32CubeIDE, etc.).
2. Add one `.c` file from this repo as the main source file.
3. Build/compile the project.
4. Flash/upload to your STM32 board.
5. Observe onboard/external LED behavior.

Notes:

- Most files use direct register access (`RCC_APB2ENR`, `GPIOx_CRL/CRH`, `GPIOx_BSRR`, `GPIOx_BRR`).
- For `PC13`, LED is usually active LOW:
	- `BRR` -> LED ON
	- `BSRR` -> LED OFF

---

## 3. Step-by-Step Instructions for All Files

## 3.1 LED Blink Files

### `LED Blink/PA5_LED.c`

Purpose: Blink LED connected to `PA5`.

Steps in code:

1. Enable clock for GPIOA (`RCC_APB2ENR` bit 2).
2. Configure `PA5` as output push-pull.
3. Turn LED ON using `GPIOA_BSRR`.
4. Delay.
5. Turn LED OFF using `GPIOA_BRR`.
6. Repeat forever.

### `LED Blink/PB1_LED.c`

Purpose: Blink LED on GPIOB pin (code configures `PB0`).

Steps in code:

1. Enable clock for GPIOB (`RCC_APB2ENR` bit 3).
2. Configure `PB0` as output push-pull.
3. Set `PB0` HIGH using `GPIOB_BSRR`.
4. Delay.
5. Set `PB0` LOW using `GPIOB_BRR`.
6. Repeat forever.

### `LED Blink/PC13 _LED.c`

Purpose: Blink onboard LED on `PC13` (active LOW).

Steps in code:

1. Enable clock for GPIOC (`RCC_APB2ENR` bit 4).
2. Configure `PC13` as output push-pull.
3. Write `GPIOC_BRR` bit 13 -> LED ON.
4. Delay.
5. Write `GPIOC_BSRR` bit 13 -> LED OFF.
6. Repeat forever.

---

## 3.2 Combined Arithmetic + Logical Demo

### `Mathmetical Operation/arithmatic_logical.c`

Purpose: Demonstrate APSR flags using multiple arithmetic and logical assembly instructions.

Steps in code:

1. Enable `GPIOC` clock and configure `PC13` output.
2. Run arithmetic examples:
	 - Negative flag (`N`) via `ADDS` with negative result.
	 - Zero flag (`Z`) via `ADDS` resulting in zero.
	 - Overflow flag (`V`) via large signed addition.
	 - Saturation flag (`Q`) via `SSAT`.
3. Run logical examples:
	 - `ANDS`, `ORRS`, `EORS`, and negative result test.
4. Read APSR using `MRS`.
5. Turn LED ON/OFF depending on the target flag bit.
6. Add delay and continue in loop.

---

## 3.3 Arithmetic Folder Files

All files in this folder use this idea:

1. Perform one arithmetic instruction in inline assembly.
2. Read APSR flag register.
3. Blink LED a number of times for each flag:
	 - `N` -> 1 blink
	 - `Z` -> 2 blinks
	 - `C` -> 3 blinks
	 - `V` -> 4 blinks
	 - `Q` -> 5 blinks

### `Mathmetical Operation/Arithmatic/addition.c`

Purpose: Test APSR flags after `ADDS`.

Config values in file:

- `a = 5`
- `b = -6`

### `Mathmetical Operation/Arithmatic/subtraction.c`

Purpose: Test APSR flags after `SUBS`.

Config values in file:

- `a = 20`
- `b = 7`

### `Mathmetical Operation/Arithmatic/multiplication.c`

Purpose: Test APSR flags after `MULS`.

Config values in file:

- `a = 5`
- `b = -6`

### `Mathmetical Operation/Arithmatic/divition.c`

Purpose: Perform signed division (`SDIV`) and check flags after a compare.

Steps in code:

1. Check if divisor `b == 0`.
2. If zero, blink 10 times as error indication.
3. Else run `SDIV`.
4. Use `CMP R2, #0` to update flags from result.
5. Blink according to flags (`N/Z/C/V/Q`).

Config values in file:

- `a = 20`
- `b = 5`

---

## 3.4 Logical Folder Files

All logical files follow the same structure:

1. Enable `GPIOC`, configure `PC13` output.
2. Execute one logical/comparison operation in assembly.
3. Read APSR.
4. Blink by flag pattern (`N=1, Z=2, C=3, V=4, Q=5`).

### `Mathmetical Operation/Logical/and_operation.c`

Instruction used: `ANDS`

Values:

- `a = 23`
- `b = 45`

### `Mathmetical Operation/Logical/or_operation.c`

Instruction used: `ORRS`

Values:

- `a = 23`
- `b = 45`

### `Mathmetical Operation/Logical/xor_operation.c`

Instruction used: `EORS`

Values:

- `a = 23`
- `b = 45`

### `Mathmetical Operation/Logical/xnor_operation.c`

Instruction used:

1. `EOR` (XOR result)
2. `MVNS` (bitwise NOT) -> XNOR effect

Values:

- `a = 23`
- `b = 45`

### `Mathmetical Operation/Logical/equal.c`

Instruction used: `CMP R0, R1`

Values:

- `a = 25`
- `b = 25`

Expected: `Z` flag should be set for equality.

### `Mathmetical Operation/Logical/gather_than.c`

Instruction used: `CMP R0, R1`

Values:

- `a = 20`
- `b = 10`

Expected: comparison indicates greater-than case.

### `Mathmetical Operation/Logical/less_than.c`

Instruction used: `CMP R0, R1`

Values:

- `a = 10`
- `b = 20`

Expected: comparison indicates less-than case.

---

## 4. Quick Practice Flow

For lab practice, use this order:

1. Run one file from `LED Blink/`.
2. Run `Mathmetical Operation/arithmatic_logical.c`.
3. Run all files in `Mathmetical Operation/Arithmatic/`.
4. Run all files in `Mathmetical Operation/Logical/`.
5. Change input values (`a`, `b`) and observe flag/blink changes.

---

## 5. Important Notes

- Keep only one `main()` source file active in a single build.
- If LED logic looks inverted on `PC13`, remember it is active LOW.
- Delay loops are software-based and not exact timing.
- Some flags (especially `Q`) may not trigger for all operations.
