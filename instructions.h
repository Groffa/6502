#ifndef INSTRUCTIONS_H

#include <assert.h>
#include "opcodes.h"

#define OPCODE__(OpCode, AdditionalBytes, Cycles, Func) {OpCode,AdditionalBytes,Cycles,Func,#OpCode}
#define OPCODE_(OpCode, AdditionalBytes, Cycles, Func) OPCODE__(OpCode,AdditionalBytes,Cycles,Func)
#define OPCODE(OpCode, AdditionalBytes, Cycles)  OPCODE_(OpCode,AdditionalBytes,Cycles,OpCode##_func)

inline void
PushStack(cpu_t *Cpu, ram_t *Ram, u8 Value)
{
    u16 Address = STACK_ADDR(Cpu->SP);
    Ram->Data[Address] = Value;
    Cpu->SP++;
}

inline u8
PopStack(cpu_t *Cpu, ram_t *Ram)
{
    u16 Address = STACK_ADDR(Cpu->SP);
    u8 Value = Ram->Data[Address];
    Cpu->SP--;
    return Value;
}

#include "instructions_impl.cpp"

static instruction_t InstructionTable[] = {
    // opcode, additional bytes, cycles
    OPCODE(BRK, 0, 7),
    OPCODE(ORA_X_ind, 1, 6),
    OPCODE(ORA_zpg, 1, 3),
    OPCODE(ASL_zpg, 1, 5),
    OPCODE(PHP, 0, 3),
    OPCODE(PHA, 0, 3),
};

#define INSTRUCTION_COUNT   (sizeof(InstructionTable)/sizeof(InstructionTable[0]))

inline instruction_t
DecodeOpCode(opcode_e OpCode)
{
    // TODO: when all opcodes are filled in in InstructionTable above,
    // switch to following direct lookup.
    // return InstructionTable[OpCode];
    for (u8 i=0; i < INSTRUCTION_COUNT; ++i)
    {
        if (InstructionTable[i].OpCode == OpCode) {
            return InstructionTable[i];
        }
    }
    instruction_t InvalidInstruction = { (opcode_e)0, 0, 0, 0 };
    return InvalidInstruction;
}

#define READ_BYTE(Cpu, Ram)     Ram->Data[Cpu->PC++]
#define READ_OP(Cpu, Ram)       (opcode_e)READ_BYTE(Cpu, Ram)

void
LoadProgram(ram_t *Ram, u8 *Program, u16 ProgramSize, u16 Base = 0x0)
{
    for (u16 i=0; i < ProgramSize; ++i) {
        u16 Address = Base + i;
        Ram->Data[Address] = *(Program + i);
    }
}

void
SingleStepProgram(cpu_t *Cpu, ram_t *Ram)
{
    opcode_e OpCode = READ_OP(Cpu, Ram);
    instruction_t Instruction = DecodeOpCode(OpCode);
    u8 Data[2] = {0};

    // Eat remaining bytes
    for (u8 i=0; i < Instruction.Bytes; ++i) {
        Data[i] = READ_BYTE(Cpu, Ram);
    }

    if (Instruction.Func) {
        (Instruction.Func)(Cpu, Ram, Data);
        // Update meta-information
        Cpu->CycleCount += Instruction.Cycles;
    } else {
        printf("-- NOT IMPLEMENTED PC=%2X: %2X",
            Cpu->PC - (Instruction.Bytes + 1),
            (u8)OpCode);
        for (u8 i=0; i < Instruction.Bytes; ++i) {
            printf(" %2X", Data[i]);
        }
        printf("\n");
    }
}

#define INSTRUCTIONS_H
#endif
