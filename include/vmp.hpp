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
#ifndef vmp_hpp
#define vmp_hpp

#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <memory>
#include <raylib.h>

static size_t MEMORY_SIZE = 65536;
static bool VM_RUNNING = false;
static bool VM_DEBUG = true;

#endif
