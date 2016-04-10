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

    // Below: NOT IMPLEMENTED
    OPCODE(ORA_im,1,0),             // ORA immediate
    OPCODE(ASL,0,0),                // ASL accumulator
    OPCODE(ORA_abs,2,0),
    OPCODE(ASL_abs,2,0),            // ASL absolute
    
    OPCODE(BPL_rel,1,0),
    OPCODE(ORA_ind_Y,1,0),          // ORA (zeropage), Y
    OPCODE(ORA_zpg_X,1,0),
    OPCODE(ASL_zpg_X,1,0),          // ASL zeropage, X
    OPCODE(CLC,0,0),
    OPCODE(ORA_abs_Y,0,0),          // ORA absolute, Y
    OPCODE(ORA_abs_X,2,0),
    OPCODE(ASL_abs_X,2,0),          // ASL absolute, X
    
    OPCODE(JSR,2,0),
    OPCODE(AND_X_ind,1,0),          // AND (zeropage, X)
    OPCODE(BIT_zpg,1,0),
    OPCODE(AND_zpg,1,0),            // AND zeropage
    OPCODE(ROL_zpg,1,0),            // ROL zeropage
    OPCODE(PLP ,0,0),
    OPCODE(AND_im,1,0),             // AND immediate
    OPCODE(ROL,0,0),                // ROL accumulator,
    OPCODE(BIT_abs,2,0),
    OPCODE(AND_abs,2,0),            // AND absolute
    OPCODE(ROL_abs,2,0),            // ROL absolute

    OPCODE(BMI_rel,1,0),
    OPCODE(AND_ind_Y,1,0),          // AND (zeropage), Y
    OPCODE(AND_zpg_X,1,0),
    OPCODE(ROL_zpg_X,1,0),          // ROL zeropage, X
    OPCODE(SEC ,0,0),
    OPCODE(AND_abs_Y,2,0),          // AND absolute, Y
    OPCODE(AND_abs_X,2,0),
    OPCODE(ROL_abs_X,2,0),          // ROL absolute, X

    OPCODE(RTI ,0,0),
    OPCODE(EOR_X_ind,1,0),          // EOR (zeropage, X)
    OPCODE(EOR_zpg,1,0),
    OPCODE(LSR_zpg,1,0),            // LSR zeropage
    OPCODE(EOR_im,1,0),             // EOR immediate
    OPCODE(LSR,0,0),                // LSR accumulator
    OPCODE(JMP_abs,2,0),
    OPCODE(EOR_abs,2,0),            // EOR absolute
    OPCODE(LSR_abs,2,0),            // LSR absolute

    OPCODE(BVC_rel,1,0),
    OPCODE(EOR_ind_Y,1,0),          // EOR (zeropage), Y
    OPCODE(EOR_zpg_X,1,0),
    OPCODE(LSR_zpg_X,1,0),          // LSR zeropage, X
    OPCODE(CLI ,0,0),
    OPCODE(EOR_abs_Y,2,0),          // EOR absolute, Y
    OPCODE(EOR_abs_X,2,0),
    OPCODE(LSR_abs_X,2,0),          // LSR absolute, X

    OPCODE(RTS,0,0),
    OPCODE(ADC_X_ind,1,0),          // ADC (zeropage, X)
    OPCODE(ADC_zpg,1,0),
    OPCODE(ROR_zpg,1,0),            // ROR zeropage
    OPCODE(PLA,0,0),
    OPCODE(ADC_im,1,0),             // ADC immediate
    OPCODE(ROR,0,0),                // ROR accumulator
    OPCODE(JMP_ind,2,0),
    OPCODE(ADC_abs,2,0),            // ADC absolute
    OPCODE(ROR_abs,2,0),            // ROR absolute

    OPCODE(BVS_rel,1,0),
    OPCODE(ADC_ind_Y,1,0),          // ADC (zeropage), Y
    OPCODE(ADC_zpg_X,1,0),
    OPCODE(ROR_zpg_X,1,0),          // ROR zeropage, X
    OPCODE(SEI ,0,0),
    OPCODE(ADC_abs_Y,2,0),          // ADC absolute, Y
    OPCODE(ADC_abx_X ,0,0),
    OPCODE(ROR_abs_X,2,0),          // ROR absolute, X

    OPCODE(STA_X_ind,1,0),
    OPCODE(STY_zpg,1,0),
    OPCODE(STA_zpg,1,0),            // STA zeropage
    OPCODE(STX_zpg,1,0),            // STX zeropage
    OPCODE(DEY ,0,0),
    OPCODE(TXA ,0,0),
    OPCODE(STY_abs,2,0),
    OPCODE(STA_abs,2,0),            // STA absolute,
    OPCODE(STX_abs,2,0),            // STX absolute

    OPCODE(BCC_rel,1,0),
    OPCODE(STA_ind_Y,1,0),          // STA (zeropage), Y
    OPCODE(STY_zpg_X,1,0),
    OPCODE(STA_zpg_X,1,0),          // STA zeropage, X
    OPCODE(STX_zpg_Y,0,0),          // STX zeropage, Y
    OPCODE(TYA ,0,0),
    OPCODE(STA_abs_Y,2,0),          // STA absolute, Y
    OPCODE(TXS,0,0),                // TXS
    OPCODE(STA_abs_X,2,0),

    OPCODE(LDY_im,1,0),
    OPCODE(LDA_X_ind,1,0),          // LDA (zeropage, X)
    OPCODE(LDX_im,1,0),             // LDX immediate
    OPCODE(LDY_zpg,1,0),
    OPCODE(LDA_zpg,1,0),            // LDA zeropage
    OPCODE(LDX_zpg,1,0),            // LDX zeropage
    OPCODE(TAY,0,0),
    OPCODE(LDA_im,1,0),             // LDA immediate
    OPCODE(TAX,0,0),                // TAX
    OPCODE(LDY_abs,2,0),
    OPCODE(LDA_abs,2,0),            // LDA absolute
    OPCODE(LDX_abs,2,0),            // LDX absolute

    OPCODE(BCS_rel,1,0),
    OPCODE(LDA_ind_Y,1,0),          // LDA (zeropage), Y
    OPCODE(LDY_zpg_X,1,0),
    OPCODE(LDA_zpg_X,1,0),          // LDA zeropage, X
    OPCODE(LDX_zpg_Y,0,0),          // LDX zeropage, Y
    OPCODE(CLV,0,0),
    OPCODE(LDA_abs_Y,2,0),          // LDA absolute, Y
    OPCODE(TSX,0,0),                // TSX
    OPCODE(LDY_abs_X,2,0),
    OPCODE(LDA_abs_X,2,0),          // LDA absolute, X
    OPCODE(LDX_abs_Y,2,0),          // LDX absolute, Y

    OPCODE(CPY_im,1,0),
    OPCODE(CMP_X_ind,1,0),          // CMP (zeropage, X)
    OPCODE(CPY_zpg,1,0),
    OPCODE(CMP_zpg,1,0),            // CMP zeropage
    OPCODE(DEC_zpg,1,0),            // DEC zeropage
    OPCODE(INY,0,0),
    OPCODE(CMP_im,1,0),             // CMP immediate
    OPCODE(DEX,0,0),                // DEX
    OPCODE(CPY_abs,2,0),
    OPCODE(CMP_abs,2,0),            // CMP absolute
    OPCODE(DEC_abs,2,0),            // DEC absolute

    OPCODE(BNE_rel,1,0),
    OPCODE(CMP_ind_Y,1,0),          // CMP (zeropage), Y
    OPCODE(CMP_zpg_X,1,0),
    OPCODE(DEC_zpg_X,1,0),          // DEC zeropage, X
    OPCODE(CLD ,0,0),
    OPCODE(CMP_abs_Y,2,0),          // CMP absolute, Y
    OPCODE(CMP_abs_X,2,0),
    OPCODE(DEC_abs_X,2,0),          // DEC absolute, X

    OPCODE(CPX_im,1,0),
    OPCODE(SBC_X_ind,1,0),          // SBC (zeropage, X)
    OPCODE(CPX_zpg,1,0),
    OPCODE(SBC_zpg,1,0),            // SBC zeropage
    OPCODE(INC_zpg,1,0),            // INC zeropage
    OPCODE(INX,0,0),
    OPCODE(SBC_im,1,0),             // SBC immediate
    OPCODE(NOP,0,0),                // NOP
    OPCODE(CPX_abs,2,0),
    OPCODE(SBC_abs,2,0),            // SBC absolute
    OPCODE(INC_abs,2,0),            // INC absolute

    OPCODE(BEQ_rel,1,0),
    OPCODE(SBC_ind_Y,1,0),          // SBC (zeropage), Y
    OPCODE(SBC_zpg_X,1,0),
    OPCODE(INC_zpg_X,1,0),          // INC zeropage, X
    OPCODE(SED,0,0),
    OPCODE(SBC_abs_Y,2,0),          // SBC absolute, Y
    OPCODE(SBC_abs_X,2,0),
    OPCODE(INC_abs_X,2,0)// INC absolute, X
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
