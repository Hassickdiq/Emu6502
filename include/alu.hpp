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
#ifndef alu_hpp
#define alu_hpp

#include "memory.hpp"
#include "vmp.hpp"

class ALU {
public:
    inline uint8_t Add(uint8_t a, uint8_t b, bool carryIn) {
        uint16_t result16 = a + b + (carryIn ? 1 : 0);
        uint8_t result = result16 & 0xFF;

        // Z Flag
        if (result == 0) 
            SetFlag(ZF); 
        else 
            ClearFlag(ZF);

        // N Flag
        if (result & 0x80) 
            SetFlag(NF); 
        else 
            ClearFlag(NF);

        // V Flag
        if (((a & 0x80) == (b & 0x80)) && ((result & 0x80) != (a & 0x80)))
            SetFlag(VF);
        else
            ClearFlag(VF);
        
        // C Flag
        if (result16 > 0xFF) 
            SetFlag(CF); 
        else 
            ClearFlag(CF);

        if (!GetFlag(DF))
            return result;

        uint8_t low_a = a & 0x0F;
        uint8_t high_a = (a >> 4) & 0x0F;
        uint8_t low_b = b & 0x0F;
        uint8_t high_b = (b >> 4) & 0x0F;

        uint8_t low_sum = low_a + low_b + (carryIn ? 1 : 0);
        uint8_t carry_low = 0;
        if (low_sum > 9) {
            low_sum -= 10;
            carry_low = 1;
        }

        uint8_t high_sum = high_a + high_b + carry_low;
        uint8_t carry_high = 0;
        if (high_sum > 9) {
            high_sum -= 10;
            carry_high = 1;
        }

        result = (high_sum << 4) | low_sum;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else 
            ClearFlag(ZF);

        // N Flag 
        if (result & 0x80) SetFlag(NF); 
        else
            ClearFlag(NF);

        // C Flag
        if (carry_high) 
            SetFlag(CF); 
        else
            ClearFlag(CF);

        if (((a & 0x80) == (b & 0x80)) && ((result & 0x80) != (a & 0x80)))
            SetFlag(VF);
        else
            ClearFlag(VF);

        return result;
    }

    inline uint8_t And(uint8_t a, uint8_t b) {
        uint8_t result = a & b;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        return result;
    }

    inline uint8_t Asl(uint8_t a) {
        uint8_t result = a << 1;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        // C Flag
        if ((a & 0x80) != 0)
            SetFlag(CF);
        else
            ClearFlag(CF);

        return result;
    }

    inline void Bit(uint8_t a, uint8_t b) {
        uint8_t result = a & b;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((a & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        // V Flag
        if ((a & 0x40) != 0)
            SetFlag(VF);
        else
            ClearFlag(VF);
    }

    inline void Cmp(uint8_t a, uint8_t b) {
        uint8_t result = a - b;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        // C Flag
        if (a >= b)
            SetFlag(CF);
        else
            ClearFlag(CF);
    }

    inline uint8_t Dec(uint8_t a) {
        uint8_t result = a - 1;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        return result;
    }

    inline uint8_t Inc(uint8_t a) {
        uint8_t result = a + 1;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        return result;
    }

    inline uint8_t Xor(uint8_t a, uint8_t b) {
        uint8_t result = a ^ b;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        return result;
    }

    inline uint8_t Lsr(uint8_t a) {
        uint8_t result = a >> 1;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        ClearFlag(NF);

        // C Flag
        if ((a & 0x01) != 0)
            SetFlag(CF);
        else
            ClearFlag(CF);

        return result;
    }

    inline uint8_t Or(uint8_t a, uint8_t b) {
        uint8_t result = a | b;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        return result;
    }

    inline uint8_t Rol(uint8_t a, bool carryIn) {
        uint8_t result = (a << 1) | (carryIn ? 1 : 0);

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        // C Flag
        if ((a & 0x80) != 0)
            SetFlag(CF);
        else
            ClearFlag(CF);

        return result;
    }

    inline uint8_t Ror(uint8_t a, bool carryIn) {
        uint8_t result = (a >> 1) | (carryIn ? 0x80 : 0);

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        // C Flag
        if ((a & 0x01) != 0)
            SetFlag(CF);
        else
            ClearFlag(CF);

        return result;
    }

    inline uint8_t Sub(uint8_t a, uint8_t b, bool borrowIn) {
        uint16_t result16 = a - b - (borrowIn ? 0 : 1);
        uint8_t  result = result16 & 0xFF;

        // Z Flag
        if (result == 0)
            SetFlag(ZF);
        else
            ClearFlag(ZF);

        // N Flag
        if ((result & 0x80) != 0)
            SetFlag(NF);
        else
            ClearFlag(NF);

        // C Flag
        if (result16 < 0x100)
            SetFlag(CF);
        else
            ClearFlag(CF);

        // V Flag
        if (((a & 0x80) == (b & 0x80)) && ((result & 0x80) != (a & 0x80)))
            SetFlag(VF);
        else
            ClearFlag(VF);

        if (!GetFlag(DF))
            return result;

        uint8_t low_a = a & 0x0F;
        uint8_t high_a = (a >> 4) & 0x0F;
        uint8_t low_b = b & 0x0F;
        uint8_t high_b = (b >> 4) & 0x0F;

        uint8_t borrow = borrowIn ? 0 : 1;  // C=1 → 0, C=0 → 1

        int16_t low_sum = low_a - low_b - borrow;
        uint8_t borrow_low = 0;
        if (low_sum < 0) {
            low_sum += 10; 
            borrow_low = 1;  
        }

        int16_t high_sum = high_a - high_b - borrow_low;
        uint8_t borrow_high = 0;
        if (high_sum < 0) {
            high_sum += 10;
            borrow_high = 1; 
        }

        result = (high_sum << 4) | low_sum;

        if (borrow_high)
            ClearFlag(CF);
        else
            SetFlag(CF);

        if (result == 0) 
            SetFlag(ZF); 
        else 
            ClearFlag(ZF);

        if (result & 0x80)
            SetFlag(NF); 
        else 
            ClearFlag(NF);

        if (((a & 0x80) == (b & 0x80)) && ((result & 0x80) != (a & 0x80)))
            SetFlag(VF);
        else
            ClearFlag(VF);

        return result;
    }
};

#endif
