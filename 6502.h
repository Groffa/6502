#ifndef x6502_H

#define KILOBYTES(x) ((x) * 1024)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int uint;

// Status register flags
enum statusflag_e
{
    StatusFlag_CARRY        = 0x1,
    StatusFlag_ZERO         = 0x2,
    StatusFlag_INTERRUPT    = 0x4,
    StatusFlag_DECIMAL      = 0x8,
    StatusFlag_BREAK        = 0x10,
    StatusFlag_IGNORED      = 0x20,
    StatusFlag_OVERFLOW     = 0x40,
    StatusFlag_NEGATIVE     = 0x80,
    
    StatusFlag_Count
};

#define SET_FLAG(SR, Flag)      (SR |= (Flag))
#define CLEAR_FLAG(SR, Flag)    (SR &= ~(Flag))
#define FLAG_ON(SR, Flag)       ((SR) & (Flag))

char *
GetStatusRegisters(u8 StatusRegister)
{
    static char Buffer[9] = {0};
    u8 i = 7;
    Buffer[i--] = (FLAG_ON(StatusRegister, StatusFlag_CARRY) ? '1' : '0');
    Buffer[i--] = (FLAG_ON(StatusRegister, StatusFlag_ZERO) ? '1' : '0');
    Buffer[i--] = (FLAG_ON(StatusRegister, StatusFlag_INTERRUPT) ? '1' : '0');
    Buffer[i--] = (FLAG_ON(StatusRegister, StatusFlag_DECIMAL) ? '1' : '0');
    Buffer[i--] = (FLAG_ON(StatusRegister, StatusFlag_BREAK) ? '1' : '0');
    Buffer[i--] = (FLAG_ON(StatusRegister, StatusFlag_IGNORED) ? '1' : '0');
    Buffer[i--] = (FLAG_ON(StatusRegister, StatusFlag_OVERFLOW) ? '1' : '0');
    Buffer[i--] = (FLAG_ON(StatusRegister, StatusFlag_NEGATIVE) ? '1' : '0');
    
    Buffer[8] = 0;

    return Buffer;
}

// Stack always starts at memory 0x0100 (range 0x0100 - 0x01FF)
#define STACK_ADDR(x)   (0x0100 + (x))

#define RAM_SIZE    (KILOBYTES(65))

struct cpu_t
{
    // Registers
    u16 PC;     // Program counter
    u8 A;      // Accumulator
    u8 X;
    u8 Y;
    u8 SR;      // Status register
    u8 SP;      // Stack pointer

    // Meta-information
    uint CycleCount;        // How many cycles have we run for?
};

// 16-bit (65K memory)
struct ram_t
{
    u8 Data[RAM_SIZE];
};

typedef void (*InstructionFunc)(cpu_t *Cpu, ram_t *Ram, u8 *Data); 

enum opcode_e;

struct instruction_t
{
    opcode_e OpCode;
    u8 Bytes;           // Additional bytes to fetch
    u8 Cycles;
    InstructionFunc Func;
};

#include "instructions.h"

#define x6502_H 
#endif
