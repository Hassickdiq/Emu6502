# EMU6502 - 6502 & Custom Architecture Virtual Machine (VM) Documentation

## Overview
**EMU650216** is a comprehensive Virtual Machine (VM) emulator project that accurately replicates the standard MOS Technology 6502 Instruction Set Architecture (ISA) while introducing custom 16-bit/20-bit architectural extensions. The system integrates memory management, CPU instruction cycles, Interrupt handling, and an Arithmetic Logic Unit (ALU) with Binary Coded Decimal (BCD) support within a modular C++ infrastructure. Through the integration of the `raylib` library, it allows for graphical hardware output.

## System Architecture

### Registers
The standard 8-bit register structure of the 6502 has been extended for the custom architecture:
- **16-bit Registers (RegSet0):** `AX`, `BX`, `CX`, `DX`, `XX`, `YY`
  - Access to the lower and upper 8-bit halves, or the full 16-bit value of these registers, is provided via custom `LOW`, `HIGH`, and `FULL` parameters (e.g., the lower 8 bits of `AX` behave like the standard `A` register).
- **20-bit Registers (RegSet1):** `BP` (Base Pointer), `SP` (Stack Pointer), `PC` (Program Counter)
  - The program counter and stack pointer support extended memory management with a 20-bit addressing space.

### Status Flags
There are 8 flags that indicate the processor status:
- **C (CF):** Carry
- **Z (ZF):** Zero
- **I (IF):** Interrupt Disable
- **D (DF):** Decimal Mode (for mathematical operations in BCD format)
- **B (BF):** Break (Software interrupt)
- **S (SF):** Stack
- **V (VF):** Overflow
- **N (NF):** Negative

## Module Details

### 1. Memory Management (`memory.hpp` & `memory.cpp`)
- **Size:** The default memory size is configured to `65536` bytes (64 KB) (`MEMORY_SIZE`), but it is extensible given the potential of the 20-bit address bus.
- **Stack Operations:** 
  - `Push8Stack` / `Pull8Stack`: 8-bit data push/pull operations.
  - `Push16Stack` / `Pull16Stack`: 16-bit (word) data push/pull operations.
- **Addressing Functions:** Supports 8-bit (`ReadByte`/`WriteByte`), 16-bit (`ReadWord`/`WriteWord`), and extended 20-bit (`Read20bit`) memory reads. The system operates using a Little-Endian (LSB-first) byte order.

### 2. Arithmetic and Logic Unit (`alu.hpp`)
All mathematical and logical operations are isolated within the ALU class.
- **Supported Operations:** `Add` (ADC), `Sub` (SBC), `And`, `Or`, `Xor`, `Asl`, `Lsr`, `Rol`, `Ror`, `Cmp`, `Bit`, `Inc`, `Dec`.
- **Decimal Mode (BCD) Support:** When the `DF` (Decimal Flag) is active, `Add` and `Sub` functions apply base-10 corrections instead of standard binary operations. Carry and half-carry logic is calculated in strict fidelity to the original hardware.

### 3. Processor Core (`cpu.hpp` & `cpu.cpp`)
This is the main loop module where 6502 opcodes are decoded and executed.
- **Instruction Cycle:** Through the `Run()` function, the PC (Program Counter) is incremented by 1 byte to fetch the opcode, which is then processed in the `ExecuteOpcode` function.
- **Addressing Modes:**
  - All standard 6502 modes are implemented, including *Immediate, ZeroPage, ZeroPage,X, ZeroPage,Y, Absolute, Absolute,X, Absolute,Y, Indirect, Indirect,X, Indirect,Y, and Relative*.
- **Branching:** Relative jumps based on flag states (`BCC`, `BCS`, `BEQ`, `BMI`, `BNE`, `BPL`, etc.).
- **Hardware Interrupts (IRQs) and Software Interrupts:** When `IrqExec` is triggered or a `BRK` instruction is fetched, the system safely pushes the PC and Flag states to the Stack and jumps to the Interrupt Vector address (`0xFFFE`). 

### 4. VM Parameters (`vmp.hpp`)
This section holds the general configuration of the system.
- `VM_DEBUG`: Toggles the debugger mode, allowing the machine to dump instantaneous PC, Opcode, and register states via the console.
- `<raylib.h>` is included, allowing the system to be expanded in the future to directly render the VRAM memory region to a graphical display.
