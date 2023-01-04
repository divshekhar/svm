#pragma once

#ifndef __MEMORY_H__
#define __MEMORY_H__
#endif

#include <stdint.h>

#include "./win.h"

#define MAX_MEMORY (1 << 16) // 64KB

// 65536 locations
uint16_t memory[MAX_MEMORY];

// Memory Mapped Registers
enum
{
    // Keyboard Status
    MR_KBSR = 0xFE00,
    // Keyboard Data
    MR_KBDR = 0xFE02,
};

void mem_write(uint16_t address, uint16_t val);
uint16_t mem_read(uint16_t address);
