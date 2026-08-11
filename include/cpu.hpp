/*
 * EMU6502 - 6502 & Custom Architecture VM
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

#pragma once
#ifndef cpu_hpp
#define cpu_hpp

#include "memory.hpp"
#include "vmp.hpp"
#include "alu.hpp"

enum OPCODE8B : uint8_t {
	// ADC - Add with Carry
	ADC_imm = 0x69,
	ADC_zp = 0x65,
	ADC_zpx = 0x75,
	ADC_abs = 0x6D,
	ADC_absx = 0x7D,
	ADC_absy = 0x79,
	ADC_indx = 0x61,
	ADC_indy = 0x71,

	// AND - Logical AND
	AND_imm = 0x29,
	AND_zp = 0x25,
	AND_zpx = 0x35,
	AND_abs = 0x2D,
	AND_absx = 0x3D,
	AND_absy = 0x39,
	AND_indx = 0x21,
	AND_indy = 0x31,

	// ASL - Arithmetic Shift Left
	ASL_acc = 0x0A,
	ASL_zp = 0x06,
	ASL_zpx = 0x16,
	ASL_abs = 0x0E,
	ASL_absx = 0x1E,

	// BCC - Branch on Carry Clear
	BCC_rel = 0x90,

	// BCS - Branch on Carry Set
	BCS_rel = 0xB0,

	// BEQ - Branch on Equal
	BEQ_rel = 0xF0,

	// BIT - Bit Test
	BIT_zp = 0x24,
	BIT_abs = 0x2C,

	// BMI - Branch on Minus
	BMI_rel = 0x30,

	// BNE - Branch on Not Equal
	BNE_rel = 0xD0,

	// BPL - Branch on Plus
	BPL_rel = 0x10,

	// BRK - Force Interrupt
	BRK_imp = 0x00,

	// BVC - Branch on Overflow Clear
	BVC_rel = 0x50,

	// BVS - Branch on Overflow Set
	BVS_rel = 0x70,

	// CLC - Clear Carry Flag
	CLC_imp = 0x18,

	// CLD - Clear Decimal Mode
	CLD_imp = 0xD8,

	// CLI - Clear Interrupt Disable
	CLI_imp = 0x58,

	// CLV - Clear Overflow Flag
	CLV_imp = 0xB8,

	// CMP - Compare
	CMP_imm = 0xC9,
	CMP_zp = 0xC5,
	CMP_zpx = 0xD5,
	CMP_abs = 0xCD,
	CMP_absx = 0xDD,
	CMP_absy = 0xD9,
	CMP_indx = 0xC1,
	CMP_indy = 0xD1,

	// CPX - Compare X Register
	CPX_imm = 0xE0,
	CPX_zp = 0xE4,
	CPX_abs = 0xEC,

	// CPY - Compare Y Register
	CPY_imm = 0xC0,
	CPY_zp = 0xC4,
	CPY_abs = 0xCC,

	// DEC - Decrement Memory
	DEC_zp = 0xC6,
	DEC_zpx = 0xD6,
	DEC_abs = 0xCE,
	DEC_absx = 0xDE,

	// DEX - Decrement X Register
	DEX_imp = 0xCA,

	// DEY - Decrement Y Register
	DEY_imp = 0x88,

	// EOR - Exclusive OR
	EOR_imm = 0x49,
	EOR_zp = 0x45,
	EOR_zpx = 0x55,
	EOR_abs = 0x4D,
	EOR_absx = 0x5D,
	EOR_absy = 0x59,
	EOR_indx = 0x41,
	EOR_indy = 0x51,

	// INC - Increment Memory
	INC_zp = 0xE6,
	INC_zpx = 0xF6,
	INC_abs = 0xEE,
	INC_absx = 0xFE,

	// INX - Increment X Register
	INX_imp = 0xE8,
	
	// INY - Increment Y Register
	INY_imp = 0xC8,

	// JMP - Jump
	JMP_abs = 0x4C,
	JMP_ind = 0x6C,

	// JSR - Jump to Subroutine
	JSR_abs = 0x20,

	// LDA - Load Accumulator
	LDA_imm = 0xA9,
	LDA_zp = 0xA5,
	LDA_zpx = 0xB5,
	LDA_abs = 0xAD,
	LDA_absx = 0xBD,
	LDA_absy = 0xB9,
	LDA_indx = 0xA1,
	LDA_indy = 0xB1,

	// LDX - Load X Register
	LDX_imm = 0xA2,
	LDX_zp = 0xA6,
	LDX_zpy = 0xB6,
	LDX_abs = 0xAE,
	LDX_absy = 0xBE,

	// LDY - Load Y Register
	LDY_imm = 0xA0,
	LDY_zp = 0xA4,
	LDY_zpx = 0xB4,
	LDY_abs = 0xAC,
	LDY_absx = 0xBC,

	//LSR - Logical Shift Right
	LSR_acc = 0x4A,
	LSR_zp = 0x46,
	LSR_zpx = 0x56,
	LSR_abs = 0x4E,
	LSR_absx = 0x5E,
	
	// NOP - No Operation
	NOP_imp = 0xEA,
	
	// ORA - Logical Inclusive OR
	ORA_imm = 0x09,
	ORA_zp = 0x05,
	ORA_zpx = 0x15,
	ORA_abs = 0x0D,
	ORA_absx = 0x1D,
	ORA_absy = 0x19,
	ORA_indx = 0x01,
	ORA_indy = 0x11,

	// PHA - Push Accumulator 
	PHA_imp = 0x48,

	// PHP - Push Processor Status 
	PHP_imp = 0x08,

	// PLA - Pull Accumulator 
	PLA_imp = 0x68,

	// PLP - Pull Processor Status 
	PLP_imp = 0x28,

	// ROL - Rotate Left
	ROL_acc = 0x2A,
	ROL_zp = 0x26,
	ROL_zpx = 0x36,
	ROL_abs = 0x2E,
	ROL_absx = 0x3E,

	// ROR - Rotate Right
	ROR_acc = 0x6A,
	ROR_zp = 0x66,
	ROR_zpx = 0x76,
	ROR_abs = 0x6E,
	ROR_absx = 0x7E,

	// RTI - Return from Interrupt
	RTI_imp = 0x40,

	// RTS - Return from Subroutine
	RTS_imp = 0x60,
	
	// SBC - Subtract Memory from Accumulator with Borrow
	SBC_imm = 0xE9,
	SBC_zp = 0xE5,
	SBC_zpx = 0xF5,
	SBC_abs = 0xED,
	SBC_absx = 0xFD,
	SBC_absy = 0xF9,
	SBC_indx = 0xE1,
	SBC_indy = 0xF1,

	SEC_imp = 0x38,
	SED_imp = 0xF8,
	SEI_imp = 0x78,

	// STA - Store Accumulator in Memory
	STA_zp = 0x85,
	STA_zpx = 0x95,
	STA_abs = 0x8D,
	STA_absx = 0x9D,
	STA_absy = 0x99,
	STA_indx = 0x81,
	STA_indy = 0x91,

	// STX - Store X Register
	STX_zp = 0x86,
	STX_zpy = 0x96,
	STX_abs = 0x8E,

	// STY - Store Y Register
	STY_zp = 0x84,
	STY_zpx = 0x94,
	STY_abs = 0x8C,

	// TAX - Transfer A to X
	TAX_imp = 0xAA,

	// TAY - Transfer A to Y
	TAY_imp = 0xA8,

	// TSX - Transfer S to X
	TSX_imp = 0xBA,

	// TXA - Transfer X to A 
	TXA_imp = 0x8A,

	// TXS - Transfer X to S
	TXS_imp = 0x9A,

	// TYA - Transfer Y to A
	TYA_imp = 0x98
};

extern bool IrqExec;
extern uint32_t IrqAddr;

void ExecuteOpcode(uint8_t opcode);
void Run();

void ADC_Immediate();
void ADC_ZeroPage();
void ADC_ZeroPageX();
void ADC_Absolute();
void ADC_AbsoluteX();
void ADC_AbsoluteY();
void ADC_IndirectX();
void ADC_IndirectY();

void AND_Immediate();
void AND_ZeroPage();
void AND_ZeroPageX();
void AND_Absolute();
void AND_AbsoluteX();
void AND_AbsoluteY();
void AND_IndirectX();
void AND_IndirectY();

void ASL_Accumulator();
void ASL_ZeroPage();
void ASL_ZeroPageX();
void ASL_Absolute();
void ASL_AbsoluteX();

void BCC_Relative();
void BCS_Relative();
void BEQ_Relative();
void BMI_Relative();
void BNE_Relative();
void BPL_Relative();
void BVC_Relative();
void BVS_Relative();

void BIT_Absolute();
void BIT_ZeroPage();

void BRK_Implied();

void CLC_Implied();

void CLD_Implied();

void CLI_Implied();

void CLV_Implied();

void CMP_Immediate();
void CMP_ZeroPage();
void CMP_ZeroPageX();
void CMP_Absolute();
void CMP_AbsoluteX();
void CMP_AbsoluteY();
void CMP_IndirectX();
void CMP_IndirectY();

void CPX_Immediate();
void CPX_ZeroPage();
void CPX_Absolute();

void CPY_Immediate();
void CPY_ZeroPage();
void CPY_Absolute();

void DEC_ZeroPage();
void DEC_ZeroPageX();
void DEC_Absolute();
void DEC_AbsoluteX();

void DEX_Implied();

void DEY_Implied();

void EOR_Immediate();
void EOR_ZeroPage();
void EOR_ZeroPageX();
void EOR_Absolute();
void EOR_AbsoluteX();
void EOR_AbsoluteY();
void EOR_IndirectX();
void EOR_IndirectY();

void INC_ZeroPage();
void INC_ZeroPageX();
void INC_Absolute();
void INC_AbsoluteX();

void INX_Implied();

void INY_Implied();

void JMP_Absolute();
void JMP_Indirect();

void JSR_Absolute();

void LDA_Immediate();
void LDA_ZeroPage();
void LDA_ZeroPageX();
void LDA_Absolute();
void LDA_AbsoluteX();
void LDA_AbsoluteY();
void LDA_IndirectX();
void LDA_IndirectY();

void LDX_Immediate();
void LDX_ZeroPage();
void LDX_ZeroPageY();
void LDX_Absolute();
void LDX_AbsoluteY();

void LDY_Immediate();
void LDY_ZeroPage();
void LDY_ZeroPageX();
void LDY_Absolute();
void LDY_AbsoluteX();

void LSR_Accumulator();
void LSR_ZeroPage();
void LSR_ZeroPageX();
void LSR_Absolute();
void LSR_AbsoluteX();

void NOP_Implied();

void ORA_Immediate();
void ORA_ZeroPage();
void ORA_ZeroPageX();
void ORA_Absolute();
void ORA_AbsoluteX();
void ORA_AbsoluteY();
void ORA_IndirectX();
void ORA_IndirectY();

void PHA_Implied();

void PHP_Implied();

void PLA_Implied();

void PLP_Implied();

void ROL_Accumulator();
void ROL_ZeroPage();
void ROL_ZeroPageX();
void ROL_Absolute();
void ROL_AbsoluteX();

void ROR_Accumulator();
void ROR_ZeroPage();
void ROR_ZeroPageX();
void ROR_Absolute();
void ROR_AbsoluteX();

void RTI_Implied();

void RTS_Implied();

void SBC_Immediate();
void SBC_ZeroPage();
void SBC_ZeroPageX();
void SBC_Absolute();
void SBC_AbsoluteX();
void SBC_AbsoluteY();
void SBC_IndirectX();
void SBC_IndirectY();

void SEC_Implied();
void SED_Implied();
void SEI_Implied();

void STA_ZeroPage();
void STA_ZeroPageX();
void STA_Absolute();
void STA_AbsoluteX();
void STA_AbsoluteY();
void STA_IndirectX();
void STA_IndirectY();

void STX_ZeroPage();
void STX_ZeroPageY();
void STX_Absolute();

void STY_ZeroPage();
void STY_ZeroPageX();
void STY_Absolute();

void TAX_Implied();

void TAY_Implied();

void TSX_Implied();

void TXA_Implied();

void TXS_Implied();

void TYA_Implied();

#endif // cpu_hpp
