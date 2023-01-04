#include <signal.h>
#include <stdlib.h>
#include <stdint.h>

#include "../include/memory.h"
#include "../include/opcode.h"
#include "../include/register.h"
#include "../include/utils.h"
#include "../include/win.h"

void handle_interrupt(int signal)
{
    restore_input_buffering();
    printf("\n");
    exit(-2);
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: svm <image-file1> <image-file2> ...\n");
        exit(2);
    }

    for (int i = 1; i < argc; ++i)
    {
        // read_image is a function that reads the image file
        // and loads it into the memory
        // example: read_image("examples/add.obj")
        if (!read_image(argv[i]))
        {
            printf("Failed to load image: %s\n", argv[i]);
            exit(1);
        }
    }

    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    // Initially set the conditional flag register to zero
    reg[R_COND] = FL_ZRO;

    enum
    {
        // 0x3000 is the default position of the program counter
        PC_START = 0x3000
    };
    // Set the program counter to default position
    reg[R_PC] = PC_START;

    int running = 1;
    while (running)
    {
        // Fetch the instruction from the PC register
        uint16_t instr = mem_read(reg[R_PC]);
        // Increment the program counter
        reg[R_PC]++;

        // Decode the instruction
        // Total instruction size is 16 bits
        // 4 bits for the opcode
        uint16_t op = instr >> 12;

        switch (op)
        {
        case OP_ADD:
            add(instr);
            break;
        case OP_AND:
            bitwiseAnd(instr);
            break;
        case OP_NOT:
            bitwiseNot(instr);
            break;
        case OP_BR:
            branch(instr);
            break;
        // Also handles RET
        case OP_JMP:
            jump(instr);
            break;
        case OP_JSR:
            jumpRegister(instr);
            break;
        case OP_LD:
            load(instr);
            break;
        case OP_LDI:
            loadIndirect(instr);
            break;
        case OP_LDR:
            loadRegister(instr);
            break;
        case OP_LEA:
            loadEffectiveAddress(instr);
            break;
        case OP_ST:
            store(instr);
            break;
        case OP_STI:
            storeIndirect(instr);
            break;
        case OP_STR:
            storeRegister(instr);
            break;
        case OP_TRAP:
            trap(instr, &running);
            break;
        case OP_RES:
        case OP_RTI:
        default:
            abort();
            break;
        }
    }
    // Shutdown the virtual machine
    restore_input_buffering();
}
