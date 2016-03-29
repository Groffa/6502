#ifndef INSTRUCTIONS_H

#include <assert.h>
#include "opcodes.h"

#define INSTR__(OpCode, AdditionalBytes, Cycles, Func) {OpCode,AdditionalBytes,Cycles,Func}
#define INSTR_(OpCode, AdditionalBytes, Cycles, Func) INSTR__(OpCode,AdditionalBytes,Cycles,Func)
#define INSTR(OpCode, AdditionalBytes, Cycles)  INSTR_(OpCode,AdditionalBytes,Cycles,OpCode##_func)
#define IMPLIED(OpCode, Cycles)     INSTR(OpCode, 0, Cycles)
#define INDIRECT    INSTR
#define INSTRUCT(Name)  void Name##_func(cpu_t *Cpu, ram_t *Ram, u8 *Data)

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
IMPLIED(BRK, 7),
INDIRECT(ORA_X_ind, 1, 6),
IMPLIED(PHA, 3),
};
static instruction_t InvalidInstruction = {(opcode_e)0,0,0,0};

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
    return InvalidInstruction;
}

#define READ_BYTE(Cpu, Ram)     Ram->Data[Cpu->PC++]
#define READ_OP(Cpu, Ram)       (opcode_e)READ_BYTE(Cpu, Ram)

void
LoadProgram(ram_t *Ram, u8 *Program, u16 ProgramSize, u16 Base = 0x0)
{
    assert(ProgramSize <= RAM_SIZE);
    assert(Base >= 0 && Base <= RAM_SIZE);

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

    (Instruction.Func)(Cpu, Ram, Data);
}

#define INSTRUCTIONS_H
#endif
