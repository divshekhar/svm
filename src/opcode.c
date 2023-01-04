#include "../include/opcode.h"

// ADD
// 0001 DR SR1 SR2
void add(uint16_t instr)
{
    // Destination register (DR)
    // 3 bits (11-9)
    uint16_t dest = (instr >> 9) & 0x7;

    // First operand
    // 3 bits (8-6)
    uint16_t s1 = (instr >> 6) & 0x7;

    // Check if the instruction is immediate
    // 1 bit (5)
    uint16_t imm_flag = (instr >> 5) & 0x1;

    if (imm_flag)
    {
        // Immediate value
        // 5 bits (4-0)
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[dest] = reg[s1] + imm5;
    }
    else
    {
        // Second operand
        // 3 bits (2-0)
        uint16_t s2 = instr & 0x7;
        reg[dest] = reg[s1] + reg[s2];
    }

    update_flags(dest);
}

// Bitwise And
void bitwiseAnd(uint16_t instr)
{
    // Destination register (DR)
    // 3 bits (11-9)
    uint16_t dest = (instr >> 9) & 0x7;

    // First operand
    // 3 bits (8-6)
    uint16_t s1 = (instr >> 6) & 0x7;

    // Check if the instruction is immediate
    // 1 bit (5)
    uint16_t imm_flag = (instr >> 5) & 0x1;

    if (imm_flag)
    {
        // Immediate value
        // 5 bits (4-0)
        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
        reg[dest] = reg[s1] & imm5;
    }
    else
    {
        // Second operand
        // 3 bits (2-0)
        uint16_t s2 = instr & 0x7;
        reg[dest] = reg[s1] & reg[s2];
    }

    update_flags(dest);
}

// Bitwise Not
void bitwiseNot(uint16_t instr)
{
    // Destination register (DR)
    // 3 bits (11-9)
    uint16_t dest = (instr >> 9) & 0x7;

    // First operand
    // 3 bits (8-6)
    uint16_t s1 = (instr >> 6) & 0x7;

    reg[dest] = ~reg[s1];

    update_flags(dest);
}

// Branch
void branch(uint16_t instr)
{
    // PC offset
    // 9 bits (8-0)
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

    // Check if the condition is met
    // 3 bits (11-9)
    uint16_t cond_flag = (instr >> 9) & 0x7;

    if (cond_flag & reg[R_COND])
    {
        reg[R_PC] += pc_offset;
    }
}

// Jump
void jump(uint16_t instr)
{
    // Base register
    // 3 bits (8-6)
    uint16_t base_r = (instr >> 6) & 0x7;

    reg[R_PC] = reg[base_r];
}

// Jump Register
void jumpRegister(uint16_t instr)
{
    // Check if the instruction is JSR or JSRR
    // 1 bit (11)
    uint16_t jsr_flag = (instr >> 11) & 0x1;
    // Save the return address
    reg[R_R7] = reg[R_PC];

    if (jsr_flag)
    {
        // JSR
        // 11 bits (10-0)
        uint16_t pc_offset = sign_extend(instr & 0x7FF, 11);

        // Jump to the address
        reg[R_PC] += pc_offset;
    }
    else
    {
        // JSRR
        // 3 bits (8-6)
        uint16_t dest = (instr >> 6) & 0x7;

        // Jump to the address
        reg[R_PC] = reg[dest];
    }
}

// Load
void load(uint16_t instr)
{
    // Destination register
    // 3 bits (11-9)
    uint16_t dest = (instr >> 9) && 0x7;

    // PC offset
    // 9 bits (8-0)
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

    // Add the offset to the current PC
    reg[dest] = mem_read(reg[R_PC] + pc_offset);

    update_flags(dest);
}

// Load Indirect
void loadIndirect(uint16_t instr)
{
    // Destination register
    // 3 bits (11-9)
    uint16_t dest = (instr >> 9) && 0x7;

    // PC offset
    // 9 bits (8-0)
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

    // Add the offset to the current PC
    reg[dest] = mem_read(reg[R_PC] + pc_offset);

    update_flags(dest);
}

// Load Register
void loadRegister(uint16_t instr)
{
    // Destination register
    // 3 bits (11-9)
    uint16_t dest = (instr >> 9) && 0x7;

    // Base register
    // 3 bits (8-6)
    uint16_t base = (instr >> 6) && 0x7;

    // Offset
    // 6 bits (5-0)
    uint16_t offset = sign_extend(instr & 0x3F, 6);

    reg[dest] = mem_read(reg[base] + offset);

    update_flags(dest);
}

// Load Effective Address
void loadEffectiveAddress(uint16_t instr)
{
    // Destination register
    // 3 bits (11-9)
    uint16_t dest = (instr >> 9) && 0x7;

    // PC offset
    // 9 bits (8-0)
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

    // Add the offset to the current PC
    reg[dest] = reg[R_PC] + pc_offset;

    update_flags(dest);
}

// Store
void store(uint16_t instr)
{
    // Source register
    // 3 bits (11-9)
    uint16_t src = (instr >> 9) && 0x7;

    // PC offset
    // 9 bits (8-0)
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

    // Add the offset to the current PC
    mem_write(reg[R_PC] + pc_offset, reg[src]);
}

// Store Indirect
void storeIndirect(uint16_t instr)
{
    // Source register
    // 3 bits (11-9)
    uint16_t src = (instr >> 9) && 0x7;

    // PC offset
    // 9 bits (8-0)
    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

    // Add the offset to the current PC
    mem_write(mem_read(reg[R_PC] + pc_offset), reg[src]);
}

// Store Register
void storeRegister(uint16_t instr)
{
    // Source register
    // 3 bits (11-9)
    uint16_t src = (instr >> 9) && 0x7;

    // Base register
    // 3 bits (8-6)
    uint16_t base = (instr >> 6) && 0x7;

    // Offset
    // 6 bits (5-0)
    uint16_t offset = sign_extend(instr & 0x3F, 6);

    mem_write(reg[base] + offset, reg[src]);
}

void trap(uint16_t instr, int *running)
{
    reg[R_R7] = reg[R_PC];

    switch (instr & 0xFF)
    {
    case TRAP_GETC:
    {
        reg[R_R0] = (uint16_t)getchar();
        update_flags(R_R0);
    }
    break;
    case TRAP_OUT:
    {
        putc((char)reg[R_R0], stdout);
        fflush(stdout);
    }
    break;
    case TRAP_PUTS:
    {
        // One character per word
        uint16_t *c = memory + reg[R_R0];
        while (*c)
        {
            putc((char)*c, stdout);
            ++c;
        }
        fflush(stdout);
        break;
    }
    case TRAP_IN:
    {
        printf("Enter a character: ");
        char c = getchar();
        putc(c, stdout);
        reg[R_R0] = (uint16_t)c;
        update_flags(R_R0);
    }
    break;
    case TRAP_PUTSP:
    {
        uint16_t *c = memory + reg[R_R0];
        while (*c)
        {
            char char1 = (*c) & 0xFF;
            putc(char1, stdout);
            char char2 = (*c) >> 8;
            if (char2)
            {
                putc(char2, stdout);
            }
            ++c;
        }
        fflush(stdout);
        break;
    }
    case TRAP_HALT:
        puts("HALT");
        fflush(stdout);
        *running = 0;
        break;
    }
}