#pragma once

#ifndef __REGISTER_H__
#define __REGISTER_H__
#endif

enum
{
    // General purpose registers (R0-R7)
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,

    // Special registers
    R_PC,   // Program counter
    R_COND, // Condition flags

    // The number of registers (R0-R7, PC, COND)
    R_COUNT
};

// Array of Registers
uint16_t reg[R_COUNT];

// Conditional Flags
enum
{
    FL_POS = 1 << 0, // P
    FL_ZRO = 1 << 1, // Z
    FL_NEG = 1 << 2, // N
};

void update_flags(uint16_t r);
