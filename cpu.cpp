/*
 * EMU650216 - 6502 & Custom Architecture VM
 * Copyright (C) 2026 HassickDir??
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "cpu.hpp"

ALU alu;

// ADC - Add Memory to Accumulator with Carry
void ADC_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Add((uint16_t)accumulator, (uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ADC_ZeroPage() {
	uint8_t address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Add((uint16_t)accumulator, (uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ADC_ZeroPageX() {
	uint8_t address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Add((uint16_t)accumulator, (uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ADC_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Add((uint16_t)accumulator, (uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ADC_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Add((uint16_t)accumulator, (uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ADC_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Add((uint16_t)accumulator, (uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ADC_IndirectX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint16_t address = ReadWord(zp_address);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Add((uint16_t)accumulator, (uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ADC_IndirectY() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint16_t address = ReadWord(zp_address) + ReadRegister(YY, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Add((uint16_t)accumulator, (uint16_t)operand, GetFlag(CF)));
	WriteRegister(AX, LOW, result);
}

// AND - AND Memory with Accumulator
void AND_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.And((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void AND_ZeroPage() {
	uint8_t address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.And((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void AND_ZeroPageX() {
	uint8_t address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.And((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void AND_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.And((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void AND_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.And((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void AND_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.And((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void AND_IndirectX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint16_t address = ReadWord(zp_address);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.And((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void AND_IndirectY() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint16_t address = ReadWord(zp_address) + ReadRegister(YY, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.And((uint16_t)accumulator, (uint16_t)operand));
	WriteRegister(AX, LOW, result);
}

// ASL - Shift Left One Bit (Memory or Accumulator)
void ASL_Accumulator() {
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Asl((uint16_t)accumulator)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ASL_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t result = (alu.Asl((uint16_t)operand)) & 0xFF;
	WriteByte(zp_address, result);
}

void ASL_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t result = (alu.Asl((uint16_t)operand)) & 0xFF;
	WriteByte(zp_address, result);
}

void ASL_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t result = (alu.Asl((uint16_t)operand)) & 0xFF;
	WriteByte(address, result);
}

void ASL_AbsoluteX() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t result = (alu.Asl((uint16_t)operand)) & 0xFF;
	WriteByte(address, result);
}

// BCC - Branch on Carry Clear
void BCC_Relative() {
	uint32_t pc = ReadRegister(PC, FULL);
	int8_t offset = ReadByte(pc);
	PCIncrement(1);
	if (GetFlag(CF) == 0)
		WriteRegister(PC, FULL, (pc + 1 + offset) & 0xFFFF);
}

// BCS - Branch on Carry Set
void BCS_Relative() {
	uint32_t pc = ReadRegister(PC, FULL);
	int8_t offset = ReadByte(pc);
	PCIncrement(1);
	if (GetFlag(CF) == 1)
		WriteRegister(PC, FULL, (pc + 1 + offset) & 0xFFFF);
}

// BEQ - Branch on Result Zero
void BEQ_Relative() {
	uint32_t pc = ReadRegister(PC, FULL);
	int8_t offset = ReadByte(pc);
	PCIncrement(1);
	if (GetFlag(ZF) == 1)
		WriteRegister(PC, FULL, (pc + 1 + offset) & 0xFFFF);
}

// BMI - Branch on Result Minus
void BMI_Relative() {
	uint32_t pc = ReadRegister(PC, FULL);
	int8_t offset = ReadByte(pc);
	PCIncrement(1);
	if (GetFlag(NF) == 1)
		WriteRegister(PC, FULL, (pc + 1 + offset) & 0xFFFF);
}

// BNE - Branch on Result not Zero
void BNE_Relative() {
	uint32_t pc = ReadRegister(PC, FULL);
	int8_t offset = ReadByte(pc);
	PCIncrement(1);
	if (GetFlag(ZF) == 0)
		WriteRegister(PC, FULL, (pc + 1 + offset) & 0xFFFF);
}

// BPL - Branch on Result Plus
void BPL_Relative() {
	uint32_t pc = ReadRegister(PC, FULL);
	int8_t offset = ReadByte(pc);
	PCIncrement(1);
	if (GetFlag(NF) == 0)
		WriteRegister(PC, FULL, (pc + 1 + offset) & 0xFFFF);
}

// BVC - Branch on Overflow Clear
void BVC_Relative() {
	uint32_t pc = ReadRegister(PC, FULL);
	int8_t offset = ReadByte(pc);
	PCIncrement(1);
	if (GetFlag(VF) == 0)
		WriteRegister(PC, FULL, (pc + 1 + offset) & 0xFFFF);
}

// BVS - Branch on Overflow Set
void BVS_Relative() {
	uint32_t pc = ReadRegister(PC, FULL);
	int8_t offset = ReadByte(pc);
	PCIncrement(1);
	if (GetFlag(VF) == 1)
		WriteRegister(PC, FULL, (pc + 1 + offset) & 0xFFFF);
}

// BIT - Test Bits in Memory with Accumulator
void BIT_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t value = ReadByte(zp_address);
	PCIncrement(1);
	alu.Bit(value, ReadRegister(AX, LOW));
}

void BIT_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t value = ReadByte(address);
	PCIncrement(2);
	alu.Bit(value, ReadRegister(AX, LOW));
}

// BRK - Force Break
void BRK_Implied() {
	uint16_t pc = ReadRegister(PC, FULL);
	Push8Stack(((pc + 1) & 0xFF00) >> 8);
	Push8Stack((pc + 1) & 0xFF); 
	Push8Stack(Flags | 0x30);         
	SetFlag(IF);
	WriteRegister(PC, FULL, ReadWord(0xFFFE)); // IRQ vektörü
}

// CLC - Clear Carry Flag
void CLC_Implied() {
	ClearFlag(CF);
}

// CLD - Clear Decimal Flag
void CLD_Implied() {
	ClearFlag(DF);
}

// CLI - Clear Interrupt Flag
void CLI_Implied() {
	ClearFlag(IF);
}

// CLV - Clear Overflow Flag
void CLV_Implied() {
	ClearFlag(VF);
}

// CMP - Compare Memory with Accumulator
void CMP_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	alu.Cmp((uint16_t)accumulator, (uint16_t)operand);
}

void CMP_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	alu.Cmp((uint16_t)accumulator, (uint16_t)operand);
}

void CMP_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	alu.Cmp((uint16_t)accumulator, (uint16_t)operand);
}

void CMP_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	alu.Cmp((uint16_t)accumulator, (uint16_t)operand);
}

void CMP_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	alu.Cmp((uint16_t)accumulator, (uint16_t)operand);
}

void CMP_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	alu.Cmp((uint16_t)accumulator, (uint16_t)operand);
}

void CMP_IndirectX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint16_t address = ReadWord(zp_address);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	alu.Cmp((uint16_t)accumulator, (uint16_t)operand);
}

void CMP_IndirectY() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint16_t address = ReadWord(zp_address) + ReadRegister(YY, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	alu.Cmp((uint16_t)accumulator, (uint16_t)operand);
}

// CPX - Compare Memory with X
void CPX_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	uint8_t x = ReadRegister(XX, LOW);
	alu.Cmp((uint16_t)x, (uint16_t)operand);
}

void CPX_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t x = ReadRegister(XX, LOW);
	alu.Cmp((uint16_t)x, (uint16_t)operand);
}

void CPX_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t x = ReadRegister(XX, LOW);
	alu.Cmp((uint16_t)x, (uint16_t)operand);
}

// CPY - Compare Memory with Y
void CPY_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	uint8_t y = ReadRegister(YY, LOW);
	alu.Cmp((uint16_t)y, (uint16_t)operand);
}

void CPY_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t y = ReadRegister(YY, LOW);
	alu.Cmp((uint16_t)y, (uint16_t)operand);
}

void CPY_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t y = ReadRegister(YY, LOW);
	alu.Cmp((uint16_t)y, (uint16_t)operand);
}

// DEC - Decrement Memory by One
void DEC_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	WriteByte(zp_address, alu.Dec(operand));
}

void DEC_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	WriteByte(zp_address, alu.Dec(operand));
}

void DEC_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	WriteByte(address, alu.Dec(operand));
}

void DEC_AbsoluteX() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	WriteByte(address, alu.Dec(operand));
}

// DEX - Decrement Index X by One
void DEX_Implied() {
	WriteRegister(XX, LOW, alu.Dec(ReadRegister(XX, LOW)));
}

// DEY - Decrement Index Y by One
void DEY_Implied() {
	WriteRegister(YY, LOW, alu.Dec(ReadRegister(YY, LOW)));
}

// EOR - Exclusive-OR Memory with Accumulator
void EOR_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Xor((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void EOR_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Xor((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void EOR_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Xor((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void EOR_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Xor((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void EOR_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Xor((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void EOR_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Xor((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void EOR_IndirectX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint16_t address = ReadWord(zp_address);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Xor((uint16_t)accumulator, (uint16_t)operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void EOR_IndirectY() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint16_t address = ReadWord(zp_address) + ReadRegister(YY, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Xor((uint16_t)accumulator, (uint16_t)operand));
	WriteRegister(AX, LOW, result);
}

// INC - Increment Memory by One
void INC_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	WriteByte(zp_address, alu.Inc(operand));
}

void INC_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	WriteByte(zp_address, alu.Inc(operand));
}

void INC_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	WriteByte(address, alu.Inc(operand));
}

void INC_AbsoluteX() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	WriteByte(address, alu.Inc(operand));
}

// INX - Increment Index X by One
void INX_Implied() {
	WriteRegister(XX, LOW, alu.Inc(ReadRegister(XX, LOW)));
}

// INY - Increment Index Y by One
void INY_Implied() {
	WriteRegister(YY, LOW, alu.Inc(ReadRegister(YY, LOW)));
}

// JMP - Jump to New Location
void JMP_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	WriteRegister(PC, FULL, address);
}

void JMP_Indirect() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint16_t value = ReadWord(address);
	WriteRegister(PC, FULL, value);
}

// JSR - Jump to New Location Saving Return Address
void JSR_Absolute() {
	Push8Stack(((ReadRegister(PC, FULL) + 2) & 0xFF00) >> 8);
	Push8Stack((ReadRegister(PC, FULL) + 2) & 0xFF);
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	WriteRegister(PC, FULL, address);
}

// LDA - Load Accumulator with Memory
void LDA_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	alu.Or(operand, operand);
	WriteRegister(AX, LOW, operand);
}

void LDA_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t value = ReadByte(zp_address);
	PCIncrement(1);
	alu.Or(value, value);
	WriteRegister(AX, LOW, value);
}

void LDA_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t value = ReadByte(zp_address);
	PCIncrement(1);
	alu.Or(value, value);
	WriteRegister(AX, LOW, value);
}

void LDA_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t value = ReadByte(address);
	PCIncrement(2);
	alu.Or(value, value);
	WriteRegister(AX, LOW, value);
}

void LDA_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	uint8_t value = ReadByte(address);
	PCIncrement(2);
	alu.Or(value, value);
	WriteRegister(AX, LOW, value);
}

void LDA_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	uint8_t value = ReadByte(address);
	PCIncrement(2);
	alu.Or(value, value);
	WriteRegister(AX, LOW, value);
}

void LDA_IndirectX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint16_t address = ReadWord(zp_address);
	uint8_t value = ReadByte(address);
	PCIncrement(1);
	alu.Or(value, value);
	WriteRegister(AX, LOW, value);
}

void LDA_IndirectY() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint16_t address = ReadWord(zp_address) + ReadRegister(YY, LOW);
	uint8_t value = ReadByte(address);
	PCIncrement(1);
	alu.Or(value, value);
	WriteRegister(AX, LOW, value);
}

// LDX - Load Index X with Memory
void LDX_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	alu.Or(operand, operand);
	WriteRegister(XX, LOW, operand);
}

void LDX_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t value = ReadByte(zp_address);
	PCIncrement(1);
	alu.Or(value, value);
	WriteRegister(XX, LOW, value);
}

void LDX_ZeroPageY() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW)) & 0xFF;
	uint8_t value = ReadByte(zp_address);
	PCIncrement(1);
	alu.Or(value, value);
	WriteRegister(XX, LOW, value);
}

void LDX_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t value = ReadByte(address);
	PCIncrement(2);
	alu.Or(value, value);
	WriteRegister(XX, LOW, value);
}

void LDX_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	uint8_t value = ReadByte(address);
	PCIncrement(2);
	alu.Or(value, value);
	WriteRegister(XX, LOW, value);
}

// LDY - Load Index Y with Memory
void LDY_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	alu.Or(operand, operand);
	WriteRegister(YY, LOW, operand);
}

void LDY_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t value = ReadByte(zp_address);
	PCIncrement(1);
	alu.Or(value, value);
	WriteRegister(YY, LOW, value);
}

void LDY_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t value = ReadByte(zp_address);
	PCIncrement(1);
	alu.Or(value, value);
	WriteRegister(YY, LOW, value);
}

void LDY_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t value = ReadByte(address);
	PCIncrement(2);
	alu.Or(value, value);
	WriteRegister(YY, LOW, value);
}

void LDY_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	uint8_t value = ReadByte(address);
	PCIncrement(2);
	alu.Or(value, value);
	WriteRegister(YY, LOW, value);
}

// LSR - Shift One Bit Right (Memory or Accumulator)
void LSR_Accumulator() {
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Lsr(accumulator)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void LSR_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t result = (alu.Lsr(operand)) & 0xFF;
	WriteByte(zp_address, result);
}

void LSR_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t result = (alu.Lsr(operand)) & 0xFF;
	WriteByte(zp_address, result);
}

void LSR_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t result = (alu.Lsr(operand)) & 0xFF;
	WriteByte(address, result);
}

void LSR_AbsoluteX() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t result = (alu.Lsr(operand)) & 0xFF;
	WriteByte(address, result);
}

// NOP - No Operation
void NOP_Implied() {

}

// ORA - OR Memory with Accumulator
void ORA_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Or(accumulator, operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ORA_ZeroPage() {
	uint8_t address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Or(accumulator, operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ORA_ZeroPageX() {
	uint8_t address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Or(accumulator, operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ORA_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Or(accumulator, operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ORA_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Or(accumulator, operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ORA_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Or(accumulator, operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ORA_IndirectX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint16_t address = ReadWord(zp_address);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Or(accumulator, operand)) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ORA_IndirectY() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint16_t address = ReadWord(zp_address) + ReadRegister(YY, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Or(accumulator, operand));
	WriteRegister(AX, LOW, result);
}

// PHA - Push Accumulator on Stack
void PHA_Implied() {
	Push8Stack(ReadRegister(AX, LOW));
}

// PHP - Push Processor Status on Stack
void PHP_Implied() {
	Push8Stack(Flags);
}

// PLA - Pull Accumulator from Stack
void PLA_Implied() {
	uint8_t value = Pull8Stack();
	WriteRegister(AX, LOW, alu.Or(value, value));
}

// PLP - Pull Processor Status from Stack
void PLP_Implied() {
	Flags = Pull8Stack();
}

// ROL - Rotate One Bit Left(Memory or Accumulator)
void ROL_Accumulator() {
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint8_t result = (alu.Rol((uint16_t)accumulator, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ROL_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t result = (alu.Rol((uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteByte(zp_address, result);
}

void ROL_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t result = (alu.Rol((uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteByte(zp_address, result);
}

void ROL_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t result = (alu.Rol((uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteByte(address, result);
}

void ROL_AbsoluteX() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t result = (alu.Rol((uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteByte(address, result);
}

// ROR - Rotate One Bit Left(Memory or Accumulator)
void ROR_Accumulator() {
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint8_t result = (alu.Ror((uint16_t)accumulator, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void ROR_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t result = (alu.Ror((uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteByte(zp_address, result);
}

void ROR_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(zp_address);
	PCIncrement(1);
	uint8_t result = (alu.Ror((uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteByte(zp_address, result);
}

void ROR_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t result = (alu.Ror((uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteByte(address, result);
}

void ROR_AbsoluteX() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t result = (alu.Ror((uint16_t)operand, GetFlag(CF))) & 0xFF;
	WriteByte(address, result);
}

// RTI - Return from Interrupt
void RTI_Implied() {
	uint8_t p = Pull8Stack();
	uint8_t pcl = Pull8Stack();
	uint8_t pch = Pull8Stack();
	WriteRegister(PC, FULL, (pch << 8) | pcl);
	Flags = p;
}

// RTS - Return from Subroutine
void RTS_Implied() {
	uint8_t pcl = Pull8Stack();
	uint8_t pch = Pull8Stack();
	WriteRegister(PC, FULL, ((pch << 8) | pcl ) + 1);
}

// SBC - Subtract Memory from Accumulator with Borrow
void SBC_Immediate() {
	uint8_t operand = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Sub(accumulator, operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void SBC_ZeroPage() {
	uint8_t address = ReadByte(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Sub(accumulator, operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void SBC_ZeroPageX() {
	uint8_t address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Sub(accumulator, operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void SBC_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Sub(accumulator, operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void SBC_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Sub(accumulator, operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void SBC_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	uint8_t operand = ReadByte(address);
	PCIncrement(2);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Sub(accumulator, operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void SBC_IndirectX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint16_t address = ReadWord(zp_address);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Sub(accumulator, operand, GetFlag(CF))) & 0xFF;
	WriteRegister(AX, LOW, result);
}

void SBC_IndirectY() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint16_t address = ReadWord(zp_address) + ReadRegister(YY, LOW);
	uint8_t operand = ReadByte(address);
	PCIncrement(1);
	uint8_t accumulator = ReadRegister(AX, LOW);
	uint16_t result = (alu.Sub(accumulator, operand, GetFlag(CF)));
	WriteRegister(AX, LOW, result);
}

void SEC_Implied() {
	SetFlag(CF);
}

void SED_Implied() {
	SetFlag(DF);
}

void SEI_Implied() {
	SetFlag(IF);
}

// STA - Store Accumulator in Memory
void STA_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	WriteByte(zp_address, ReadRegister(AX, LOW));
}

void STA_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	PCIncrement(1);
	WriteByte(zp_address, ReadRegister(AX, LOW));
}

void STA_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	PCIncrement(2);
	WriteByte(address, ReadRegister(AX, LOW));
}

void STA_AbsoluteX() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW));
	PCIncrement(2);
	WriteByte(address, ReadRegister(AX, LOW));
}

void STA_AbsoluteY() {
	uint16_t address = (ReadWord(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW));
	PCIncrement(2);
	WriteByte(address, ReadRegister(AX, LOW));
}

void STA_IndirectX() {
	uint16_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	uint16_t address = ReadWord(zp_address);
	PCIncrement(1);
	WriteByte(address, ReadRegister(AX, LOW));
}

void STA_IndirectY() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	uint16_t address = ReadWord(zp_address) + ReadRegister(YY, LOW);
	PCIncrement(1);
	WriteByte(address, ReadRegister(AX, LOW));
}
 
// STX - Store Index X in Memory
void STX_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	WriteByte(zp_address, ReadRegister(XX, LOW));
}

void STX_ZeroPageY() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(YY, LOW)) & 0xFF;
	PCIncrement(1);
	WriteByte(zp_address, ReadRegister(XX, LOW));
}

void STX_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	PCIncrement(2);
	WriteByte(address, ReadRegister(XX, LOW));
}

// STY - Store Index Y in Memory
void STY_ZeroPage() {
	uint8_t zp_address = ReadByte(ReadRegister(PC, FULL));
	PCIncrement(1);
	WriteByte(zp_address, ReadRegister(YY, LOW));
}

void STY_ZeroPageX() {
	uint8_t zp_address = (ReadByte(ReadRegister(PC, FULL)) + ReadRegister(XX, LOW)) & 0xFF;
	PCIncrement(1);
	WriteByte(zp_address, ReadRegister(YY, LOW));
}

void STY_Absolute() {
	uint16_t address = ReadWord(ReadRegister(PC, FULL));
	PCIncrement(2);
	WriteByte(address, ReadRegister(YY, LOW));
}

void TAX_Implied() {
	WriteRegister(XX, LOW, ReadRegister(AX, LOW));
	alu.Or(ReadRegister(AX, LOW), ReadRegister(AX, LOW));
}

void TAY_Implied() {
	WriteRegister(YY, LOW, ReadRegister(AX, LOW));
	alu.Or(ReadRegister(AX, LOW), ReadRegister(AX, LOW));
}

void TSX_Implied() {
	WriteRegister(XX, LOW, ReadRegister(SP, FULL));
	alu.Or(ReadRegister(SP, FULL) & 0xFF, ReadRegister(SP, FULL) & 0xFF);
}

void TXA_Implied() {
	WriteRegister(AX, LOW, ReadRegister(XX, LOW));
	alu.Or(ReadRegister(XX, LOW), ReadRegister(XX, LOW));
}

void TXS_Implied() {
	WriteRegister(SP, FULL, ReadRegister(XX, LOW) | 0x100);
}

void TYA_Implied() {
	WriteRegister(AX, LOW, ReadRegister(YY, LOW));
	alu.Or(ReadRegister(YY, LOW), ReadRegister(YY, LOW));
}

void ExecuteOpcode(uint8_t opcode) {
	if (VM_DEBUG)
		std::cout << "Executing opcode: 0x" << std::hex << static_cast<int>(opcode) << std::dec << std::endl;

	switch (opcode) {
		// ADC - Add with Carry
	case ADC_imm:  ADC_Immediate(); break;
	case ADC_zp:   ADC_ZeroPage(); break;
	case ADC_zpx:  ADC_ZeroPageX(); break;
	case ADC_abs:  ADC_Absolute(); break;
	case ADC_absx: ADC_AbsoluteX(); break;
	case ADC_absy: ADC_AbsoluteY(); break;
	case ADC_indx: ADC_IndirectX(); break;
	case ADC_indy: ADC_IndirectY(); break;

		// AND - Logical AND
	case AND_imm:  AND_Immediate(); break;
	case AND_zp:   AND_ZeroPage(); break;
	case AND_zpx:  AND_ZeroPageX(); break;
	case AND_abs:  AND_Absolute(); break;
	case AND_absx: AND_AbsoluteX(); break;
	case AND_absy: AND_AbsoluteY(); break;
	case AND_indx: AND_IndirectX(); break;
	case AND_indy: AND_IndirectY(); break;

		// ASL - Arithmetic Shift Left
	case ASL_acc:  ASL_Accumulator(); break;
	case ASL_zp:   ASL_ZeroPage(); break;
	case ASL_zpx:  ASL_ZeroPageX(); break;
	case ASL_abs:  ASL_Absolute(); break;
	case ASL_absx: ASL_AbsoluteX(); break;

		// Branch instructions
	case BCC_rel:  BCC_Relative(); break;
	case BCS_rel:  BCS_Relative(); break;
	case BEQ_rel:  BEQ_Relative(); break;
	case BMI_rel:  BMI_Relative(); break;
	case BNE_rel:  BNE_Relative(); break;
	case BPL_rel:  BPL_Relative(); break;
	case BVC_rel:  BVC_Relative(); break;
	case BVS_rel:  BVS_Relative(); break;

		// BIT - Bit Test
	case BIT_zp:   BIT_ZeroPage(); break;
	case BIT_abs:  BIT_Absolute(); break;

		// BRK - Force Interrupt
	case BRK_imp:  BRK_Implied(); break;

		// Clear flags
	case CLC_imp:  CLC_Implied(); break;
	case CLD_imp:  CLD_Implied(); break;
	case CLI_imp:  CLI_Implied(); break;
	case CLV_imp:  CLV_Implied(); break;

		// CMP - Compare
	case CMP_imm:  CMP_Immediate(); break;
	case CMP_zp:   CMP_ZeroPage(); break;
	case CMP_zpx:  CMP_ZeroPageX(); break;
	case CMP_abs:  CMP_Absolute(); break;
	case CMP_absx: CMP_AbsoluteX(); break;
	case CMP_absy: CMP_AbsoluteY(); break;
	case CMP_indx: CMP_IndirectX(); break;
	case CMP_indy: CMP_IndirectY(); break;

		// CPX - Compare X Register
	case CPX_imm:  CPX_Immediate(); break;
	case CPX_zp:   CPX_ZeroPage(); break;
	case CPX_abs:  CPX_Absolute(); break;

		// CPY - Compare Y Register
	case CPY_imm:  CPY_Immediate(); break;
	case CPY_zp:   CPY_ZeroPage(); break;
	case CPY_abs:  CPY_Absolute(); break;

		// DEC - Decrement Memory
	case DEC_zp:   DEC_ZeroPage(); break;
	case DEC_zpx:  DEC_ZeroPageX(); break;
	case DEC_abs:  DEC_Absolute(); break;
	case DEC_absx: DEC_AbsoluteX(); break;

		// DEX - Decrement X Register
	case DEX_imp:  DEX_Implied(); break;

		// DEY - Decrement Y Register
	case DEY_imp:  DEY_Implied(); break;

		// EOR - Exclusive OR
	case EOR_imm:  EOR_Immediate(); break;
	case EOR_zp:   EOR_ZeroPage(); break;
	case EOR_zpx:  EOR_ZeroPageX(); break;
	case EOR_abs:  EOR_Absolute(); break;
	case EOR_absx: EOR_AbsoluteX(); break;
	case EOR_absy: EOR_AbsoluteY(); break;
	case EOR_indx: EOR_IndirectX(); break;
	case EOR_indy: EOR_IndirectY(); break;

		// INC - Increment Memory
	case INC_zp:   INC_ZeroPage(); break;
	case INC_zpx:  INC_ZeroPageX(); break;
	case INC_abs:  INC_Absolute(); break;
	case INC_absx: INC_AbsoluteX(); break;

		// INX - Increment X Register
	case INX_imp:  INX_Implied(); break;

		// INY - Increment Y Register
	case INY_imp:  INY_Implied(); break;

		// JMP - Jump
	case JMP_abs:  JMP_Absolute(); break;
	case JMP_ind:  JMP_Indirect(); break;

		// JSR - Jump to Subroutine
	case JSR_abs:  JSR_Absolute(); break;

		// LDA - Load Accumulator
	case LDA_imm:  LDA_Immediate(); break;
	case LDA_zp:   LDA_ZeroPage(); break;
	case LDA_zpx:  LDA_ZeroPageX(); break;
	case LDA_abs:  LDA_Absolute(); break;
	case LDA_absx: LDA_AbsoluteX(); break;
	case LDA_absy: LDA_AbsoluteY(); break;
	case LDA_indx: LDA_IndirectX(); break;
	case LDA_indy: LDA_IndirectY(); break;

		// LDX - Load X Register
	case LDX_imm:  LDX_Immediate(); break;
	case LDX_zp:   LDX_ZeroPage(); break;
	case LDX_zpy:  LDX_ZeroPageY(); break;
	case LDX_abs:  LDX_Absolute(); break;
	case LDX_absy: LDX_AbsoluteY(); break;

		// LDY - Load Y Register
	case LDY_imm:  LDY_Immediate(); break;
	case LDY_zp:   LDY_ZeroPage(); break;
	case LDY_zpx:  LDY_ZeroPageX(); break;
	case LDY_abs:  LDY_Absolute(); break;
	case LDY_absx: LDY_AbsoluteX(); break;

		// LSR - Logical Shift Right
	case LSR_acc:  LSR_Accumulator(); break;
	case LSR_zp:   LSR_ZeroPage(); break;
	case LSR_zpx:  LSR_ZeroPageX(); break;
	case LSR_abs:  LSR_Absolute(); break;
	case LSR_absx: LSR_AbsoluteX(); break;

		// NOP - No Operation
	case NOP_imp:  NOP_Implied(); break;

		// ORA - Logical OR
	case ORA_imm:  ORA_Immediate(); break;
	case ORA_zp:   ORA_ZeroPage(); break;
	case ORA_zpx:  ORA_ZeroPageX(); break;
	case ORA_abs:  ORA_Absolute(); break;
	case ORA_absx: ORA_AbsoluteX(); break;
	case ORA_absy: ORA_AbsoluteY(); break;
	case ORA_indx: ORA_IndirectX(); break;
	case ORA_indy: ORA_IndirectY(); break;

		// PHA - Push Accumulator
	case PHA_imp:  PHA_Implied(); break;

		// PHP - Push Processor Status
	case PHP_imp:  PHP_Implied(); break;

		// PLA - Pull Accumulator
	case PLA_imp:  PLA_Implied(); break;

		// PLP - Pull Processor Status
	case PLP_imp:  PLP_Implied(); break;

		// ROL - Rotate Left
	case ROL_acc:  ROL_Accumulator(); break;
	case ROL_zp:   ROL_ZeroPage(); break;
	case ROL_zpx:  ROL_ZeroPageX(); break;
	case ROL_abs:  ROL_Absolute(); break;
	case ROL_absx: ROL_AbsoluteX(); break;

		// ROR - Rotate Right
	case ROR_acc:  ROR_Accumulator(); break;
	case ROR_zp:   ROR_ZeroPage(); break;
	case ROR_zpx:  ROR_ZeroPageX(); break;
	case ROR_abs:  ROR_Absolute(); break;
	case ROR_absx: ROR_AbsoluteX(); break;

		// RTI - Return from Interrupt
	case RTI_imp:  RTI_Implied(); break;

		// RTS - Return from Subroutine
	case RTS_imp:  RTS_Implied(); break;
	
		// SBC - Subtract Memory from Accumulator with Borrow
	case SBC_imm:  SBC_Immediate(); break;
	case SBC_zp:   SBC_ZeroPage(); break;
	case SBC_zpx:  SBC_ZeroPageX(); break;
	case SBC_abs:  SBC_Absolute(); break;
	case SBC_absx: SBC_AbsoluteX(); break;
	case SBC_absy: SBC_AbsoluteY(); break;
	case SBC_indx: SBC_IndirectX(); break;
	case SBC_indy: SBC_IndirectY(); break;

		// SEC - Set Carry Flag
	case SEC_imp: SEC_Implied(); break;

		// SED - Set Decimal Flag
	case SED_imp: SED_Implied(); break;

		// SEI - Set Interrupt Disable Status
	case SEI_imp: SEI_Implied(); break;

		// Store Accumulator in Memory
	case STA_zp:   STA_ZeroPage(); break;
	case STA_zpx:  STA_ZeroPageX(); break;
	case STA_abs:  STA_Absolute(); break;
	case STA_absx: STA_AbsoluteX(); break;
	case STA_absy: STA_AbsoluteY(); break;
	case STA_indx: STA_IndirectX(); break;
	case STA_indy: STA_IndirectY(); break;

		default:
			std::cerr << "Unhandled opcode: 0x" << std::hex << static_cast<int>(opcode) << std::dec << std::endl;
			VM_RUNNING = false; // Stop the VM on unhandled opcode
			break;
	}
}

bool IrqExec = false;

void Run() {
	WriteRegister(PC, FULL, 0x00);
	WriteRegister(SP, FULL, 0x1FF);
	VM_RUNNING = true;
	IrqExec = false;
	IrqAddr = 0;

	while (VM_RUNNING) {
		if (IrqExec == true) { 
			IrqExec = false;

			uint16_t pc = ReadRegister(PC, FULL);
			Push8Stack(((pc + 1) & 0xF0000) >> 12);
			Push8Stack(((pc + 1) & 0xFF00) >> 8);
			Push8Stack((pc + 1) & 0xFF);
			Push8Stack(Flags);
			SetFlag(IF);

			WriteRegister(PC, FULL, IrqAddr & 0xFFFFF);
		}

		uint8_t opcode = ReadByte(ReadRegister(PC, FULL));
		PCIncrement(1);
		ExecuteOpcode(opcode);
	}
}