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

#pragma once
#ifndef icu_hpp
#define icu_hpp

#define IRQ_VECTOR  0xF000

#include "memory.hpp"
#include "cpu.hpp"
#include "vmp.hpp"

void TriggerIrq(uint8_t IrqNo);

#endif // icu_hpp