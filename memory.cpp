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

#include "memory.hpp"

std::unique_ptr<uint8_t[]> Memory;

// AX BX CX DX XX YX BP SP PC
uint16_t RegSet0[6] = { 0x0 }; // 16-bit registers {AX, BX, CX, DX, XX, YY}
uint32_t RegSet1[3] = { 0x0 }; // 20-bit registers {BP, SP, PC}

// Flags: C Z I D B V N
uint8_t Flags = 0x0;

void DEBUG() {
	std::cout << std::endl;
	std::cout << "AX = " << std::hex << ReadRegister(AX, HIGH) << ":" << ReadRegister(AX, LOW) << std::dec << std::endl;
	std::cout << "XX = " << std::hex << ReadRegister(XX, HIGH) << ":" << ReadRegister(XX, LOW) << std::dec << std::endl;
	std::cout << "YY = " << std::hex << ReadRegister(YY, HIGH) << ":" << ReadRegister(YY, LOW) << std::dec << std::endl;
	std::cout << "SP = " << std::hex << ReadRegister(SP, FULL) << std::dec << std::endl;
	std::cout << "PC = " << std::hex << ReadRegister(PC, FULL) << std::dec << std::endl;

	std::cout << std::endl;
	std::cout << "C = " << GetFlag(CF) << std::endl;
	std::cout << "Z = " << GetFlag(ZF) << std::endl;
	std::cout << "I = " << GetFlag(IF) << std::endl;
	std::cout << "D = " << GetFlag(DF) << std::endl;
	std::cout << "B = " << GetFlag(BF) << std::endl;
	std::cout << "S = " << GetFlag(SF) << std::endl;
	std::cout << "V = " << GetFlag(VF) << std::endl;
	std::cout << "N = " << GetFlag(NF) << std::endl;

	for (size_t i = 0; i < 5; i++)
		std::cout << (0x1FF - i) << " = 0x" << std::hex << (int)ReadByte((uint16_t)(0x1FF - i)) << std::dec << std::endl;
}

void WriteRegister(size_t reg, size_t lh, uint32_t value) {
	if (reg <= 8) {
		if (reg < 5)
			if (lh == 1)
				RegSet0[reg] = (RegSet0[reg] & 0x00FF) | (value & 0xFF00);
			else if (lh == 0)
				RegSet0[reg] = (RegSet0[reg] & 0xFF00) | (value & 0x00FF);
			else if (lh == 2)
				RegSet0[reg] = value & 0xFFFF;
			else {
				std::cerr << "Invalid lh value: " << lh << std::endl;
				VM_RUNNING = false;
				return;
			}
		else
			if (value < 0xFFFFF)
				RegSet1[reg - 6] = value & 0xFFFFF;

		return;
	}
	else {
		std::cerr << "Register index out of bounds: " << reg << std::endl;
		VM_RUNNING = false;
		return;
	}
}

uint32_t ReadRegister(size_t reg, size_t lh) {
	if (reg <= 8) {
		if (reg < 5)
			if (lh == 1)
				return (uint32_t)(RegSet0[reg] & 0xFF00) >> 8;
			else if (lh == 0)
				return (uint32_t)(RegSet0[reg] & 0x00FF);
			else if (lh == 2)
				return (uint32_t)(RegSet0[reg] & 0xFFFF);
			else {
				VM_RUNNING = false;
				std::cerr << "Invalid lh value: " << lh << std::endl;
				return 0;
			}
		else
			return RegSet1[reg - 6];
	}
	else {
		std::cerr << "Register index out of bounds: " << reg << std::endl;
		VM_RUNNING = false;
		return 0;
	}
}

void PCIncrement(uint16_t value) {
	RegSet1[2] += value;
}

void SetAllFlag(uint8_t value) {
	Flags |= value;
}

void ClearAllFlag(uint8_t value) {
	Flags &= ~value;
}

void SetFlag(size_t flag) {
	Flags |= (1 << flag);
}

void ClearFlag(size_t flag) {
	Flags &= ~(1 << flag);
}

bool GetFlag(size_t flag) {
	return Flags & (1 << flag);
}

void InitializeMemory() {
	Memory = std::make_unique<uint8_t[]>(MEMORY_SIZE);
	std::cout << "Memory initialized with size: " << MEMORY_SIZE << " BYTES" << std::endl;
}

void Push8Stack(uint8_t value) {
	WriteByte(ReadRegister(SP, FULL) & 0xFFFF, value);
	WriteRegister(SP, FULL, (ReadRegister(SP, FULL) - 1) & 0xFFFF);
}

uint8_t Pull8Stack() {
	WriteRegister(SP, FULL, (ReadRegister(SP, FULL) + 1) & 0xFFFF);
	return ReadByte(ReadRegister(SP, FULL));
}

void Push16Stack(uint16_t value) {
	WriteWord(ReadRegister(SP, FULL) & 0xFFFFF, value);
	WriteRegister(SP, FULL, (ReadRegister(SP, FULL) - 2) & 0xFFFFF);
}

uint16_t Pull16Stack() {
	WriteRegister(SP, FULL, (ReadRegister(SP, FULL) + 2) & 0xFFFFF);
	return ReadByte(ReadRegister(SP, FULL));
}

void WriteByte(uint32_t address, uint8_t value) {
	address &= 0xFFFFF;

	if (address < MEMORY_SIZE) {
		Memory[address] = value;
		return;
	}
	else {
		std::cerr << "Address out of bounds: " << address << std::endl;
		VM_RUNNING = false;
		return;
	}
}

void WriteWord(uint32_t address, uint16_t value) {
	address &= 0xFFFFF;

	if (address + 1 < MEMORY_SIZE) {
		Memory[address] = static_cast<uint8_t>(value & 0xFF);
		Memory[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		return;
	}
	else {
		std::cerr << "Address out of bounds: " << address << std::endl;
		VM_RUNNING = false;
		return;
	}
}

uint8_t ReadByte(uint32_t address) {
	address &= 0xFFFFF;

	if (address < MEMORY_SIZE) {
		return Memory[address];
	}
	else {
		std::cerr << "Address out of bounds: " << address << std::endl;
		VM_RUNNING = false;
		return 0;
	}
}

uint16_t ReadWord(uint32_t address) {
	address &= 0xFFFFF;

	if (address + 1 < MEMORY_SIZE) {
		uint8_t low = Memory[address];      // Düşük byte
		uint8_t high = Memory[address + 1]; // Yüksek byte
		return (high << 8) | low;
	}
	else {
		std::cerr << "Address out of bounds: " << address << std::endl;
		VM_RUNNING = false;
		return 0;
	}
}

uint32_t Read20bit(uint32_t address) {
	address &= 0xFFFFF;

	if (address + 1 < MEMORY_SIZE) {
		uint8_t low = Memory[address];      // Düşük byte
		uint8_t high = Memory[address + 1]; // Yüksek byte
		uint8_t highhalf = Memory[address + 2] & 0x0F; // 2. Yüksek byte'ın yarısı
		return (highhalf << 12) | (high << 8) | low;
	}
	else {
		std::cerr << "Address out of bounds: " << address << std::endl;
		VM_RUNNING = false;
		return 0;
	}
}