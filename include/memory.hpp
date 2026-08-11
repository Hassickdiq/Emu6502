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
#ifndef memory_hpp
#define memory_hpp

#include "vmp.hpp"

enum RegisterPart : size_t {
	LOW = 0,
	HIGH = 1,
	FULL = 2
};

enum Fs : size_t {
	CF = 0,	// C
	ZF = 1,	// Z
	IF = 2,	// I
	DF = 3,	// D
	BF = 4,	// B
	SF = 5,	// S
	VF = 6,	// V
	NF = 7  // N 
};

enum Regs : size_t {
	AX = 0,	
	BX = 1,	
	CX = 2,
	DX = 3,
	XX = 4,	
	YY = 5,	
	BP = 6,	
	SP = 7,	
	PC = 8  
};

extern std::unique_ptr<uint8_t[]> Memory;
extern uint8_t Flags;
extern uint16_t RegSet0[6]; // 16-bit registers {AX, BX, CX, DX, XX, YY}
extern uint32_t RegSet1[3]; // 20-bit registers {BP, SP, PC}

void DEBUG();

void WriteRegister(size_t reg, size_t lh, uint32_t value);

void PCIncrement(uint16_t value);

uint32_t ReadRegister(size_t reg, size_t lh);

void SetAllFlag(uint8_t flag);

void ClearAllFlag(uint8_t flag);

void SetFlag(size_t flag);

void ClearFlag(size_t flag);

bool GetFlag(size_t flag);

void WriteByte(uint32_t address, uint8_t value);

void InitializeMemory();

void Push8Stack(uint8_t value);

uint8_t Pull8Stack();

void Push16Stack(uint16_t value);

uint16_t Pull16Stack();

void WriteWord(uint32_t address, uint16_t value);

uint8_t ReadByte(uint32_t address);

uint16_t ReadWord(uint32_t address);

uint32_t Read20bit(uint32_t address);

#endif 
