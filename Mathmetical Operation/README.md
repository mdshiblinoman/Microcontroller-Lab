# Arithmetic and Logical Flags Demo (PC13 LED)

This README explains, step by step, what happens in [Mathmetical Operation/arithmatic_logical.c](Mathmetical%20Operation/arithmatic_logical.c).

## 1. Goal of this file

The program demonstrates ARM status flags using inline assembly.

1. Run arithmetic and logical instructions.
2. Read APSR (Application Program Status Register).
3. Check specific flag bits.
4. Turn PC13 LED ON/OFF based on each flag result.

## 2. Hardware behavior used by the file

1. LED pin is PC13.
2. LED control is active-low in this code path:
	- Write to `GPIOC_BRR` bit 13 -> pin LOW -> LED ON.
	- Write to `GPIOC_BSRR` bit 13 -> pin HIGH -> LED OFF.

## 3. Startup configuration steps in `main`

1. Enable GPIOC clock:
	- `RCC_APB2ENR |= (1 << 4)` enables IOPCEN.
2. Configure PC13 as output:
	- `GPIOC_CRH &= ~(0x00F00000)` clears PC13 config bits.
	- `GPIOC_CRH |= (1 << 21)` sets output mode for PC13.
3. Declare `apsr` variable:
	- `uint32_t apsr;` stores value read from APSR.
4. Enter infinite loop:
	- Inside `while (1)`, each test runs and then calls `delay()`.

## 4. APSR flag bits checked in this file

1. `N` (Negative): bit 31
2. `Z` (Zero): bit 30
3. `V` (Overflow): bit 28
4. `Q` (Saturation): bit 27

## 5. Step-by-step instruction flow inside the loop

### Step 1: Arithmetic test for Negative flag (N)

1. Assembly performs `5 + (-6) = -1` using `ADDS`.
2. `MRS` copies APSR into `apsr`.
3. Code checks `apsr & (1 << 31)`.
4. If set, LED turns ON; otherwise OFF.

Expected result: N = 1, so LED ON.

### Step 2: Arithmetic test for Zero flag (Z)

1. Assembly performs `5 + (-5) = 0` using `ADDS`.
2. APSR is read with `MRS`.
3. Code checks `apsr & (1 << 30)`.
4. If set, LED turns ON; otherwise OFF.

Expected result: Z = 1, so LED ON.

### Step 3: Arithmetic test for Overflow flag (V)

1. Load max signed 32-bit value: `2147483647`.
2. Add `1` with `ADDS`.
3. Signed overflow occurs.
4. APSR is read, then `apsr & (1 << 28)` is checked.
5. If set, LED turns ON; otherwise OFF.

Expected result: V = 1, so LED ON.

### Step 4: Saturation test for Q flag

1. Move `300` into register.
2. Execute `SSAT R1, #8, R0`.
3. Saturating to signed 8-bit range causes saturation.
4. APSR is read, then `apsr & (1 << 27)` is checked.
5. If set, LED turns ON; otherwise OFF.

Expected result: Q = 1, so LED ON.

### Step 5: Logical ANDS test (Zero result)

1. Set `R0 = 0x0F`, `R1 = 0xF0`.
2. `ANDS` gives `0x00`.
3. APSR is read.
4. Code checks Z bit: `apsr & (1 << 30)`.
5. If set, LED turns ON; otherwise OFF.

Expected result: Z = 1, so LED ON.

### Step 6: Logical ORRS test (Non-zero result)

1. Set `R0 = 0x0F`, `R1 = 0xF0`.
2. `ORRS` gives `0xFF`.
3. APSR is read.
4. Code checks Z bit.
5. If set, LED ON; else OFF.

Expected result: Z = 0, so LED OFF.

### Step 7: Logical EORS test (Zero result)

1. Set `R0 = 0xFF`, `R1 = 0xFF`.
2. `EORS` gives `0x00`.
3. APSR is read.
4. Code checks Z bit.
5. If set, LED ON; else OFF.

Expected result: Z = 1, so LED ON.

### Step 8: Logical test for Negative flag (N)

1. Set `R0 = 0x80`, `R1 = 0x00`.
2. `ORRS` result has MSB set.
3. APSR is read.
4. Code checks N bit: `apsr & (1 << 31)`.
5. If set, LED ON; else OFF.

Expected result: N = 1, so LED ON.

## 6. Delay behavior

After each test, `delay()` runs a software loop.

1. It creates visible pause between LED states.
2. It is not precise timing.
3. Delay length depends on CPU clock.

## 7. Complete visible LED pattern per loop

For one full loop pass, expected LED sequence is:

1. ON (N test)
2. ON (Z test)
3. ON (V test)
4. ON (Q test)
5. ON (ANDS Z test)
6. OFF (ORRS Z test)
7. ON (EORS Z test)
8. ON (N logical test)

Then the same sequence repeats forever.
