#pragma once

#ifndef __OPCODE_H__
#define __OPCODE_H__
#endif

#include <stdio.h>
#include <stdint.h>

#include "./register.h"
#include "./memory.h"
#include "./utils.h"

enum
{
    // Branch
    OP_BR = 0,
    // ADD
    OP_ADD,
    // Load
    OP_LD,
    // Store
    OP_ST,
    // Jump Register
    OP_JSR,
    // Bitwise AND
    OP_AND,
    // Load Register
    OP_LDR,
    // Store Register
    OP_STR,
    // (unused)
    OP_RTI,
    // Bitwise NOT
    OP_NOT,
    // Load Indirect
    OP_LDI,
    // Store Indirect
    OP_STI,
    // Jump
    OP_JMP,
    // Reserved (unused)
    OP_RES,
    // Load Effective Address
    OP_LEA,
    // Execute Trap
    OP_TRAP
};

// Trap codes
enum
{
    // Get a character from the keyboard, not echoed onto the terminal
    TRAP_GETC = 0x20,
    // Output a character
    TRAP_OUT = 0x21,
    // Output a word string
    TRAP_PUTS = 0x22,
    // Get a character from the keyboard, echoed onto the terminal
    TRAP_IN = 0x23,
    // Output a byte string
    TRAP_PUTSP = 0x24,
    // Halt the program
    TRAP_HALT = 0x25
};

void add(uint16_t instr);
void bitwiseAnd(uint16_t instr);
void bitwiseNot(uint16_t instr);
void branch(uint16_t instr);
void jump(uint16_t instr);
void jumpRegister(uint16_t instr);
void load(uint16_t instr);
void loadIndirect(uint16_t instr);
void loadRegister(uint16_t instr);
void loadEffectiveAddress(uint16_t instr);
void store(uint16_t instr);
void storeIndirect(uint16_t instr);
void storeRegister(uint16_t instr);
void trap(uint16_t instr, int *running);
