#ifndef INSTRUCTIONS_IMPL_CPP

#define IMPLEMENT(OpCode)  void OpCode##_func(cpu_t *Cpu, ram_t *Ram, u8 *Data)
#define NOT_IMPLEMENTED(OpCode)   IMPLEMENT(OpCode)

static void
CheckAndSetFlags(cpu_t *Cpu)
{
    if (Cpu->A == 0) {
        SET_FLAG(Cpu->SR, StatusFlag_ZERO);
    }
    if (Cpu->A & 0x80) {
        SET_FLAG(Cpu->SR, StatusFlag_NEGATIVE);
    }
    // TODO: more tests
}

IMPLEMENT(BRK)
{
    // set interrupt flag
    // push pc+2
    // push sr
    PushStack(Cpu, Ram, Cpu->PC + 2);
    PushStack(Cpu, Ram, Cpu->SR);
    SET_FLAG(Cpu->SR, StatusFlag_INTERRUPT);
}

IMPLEMENT(ORA_X_ind)
{
    // ORA (oper,X)
    // A OR M -> A
    u8 LSB = Data[0] + Cpu->X;
    u8 MSB = LSB + 1;
    u16 Address = LSB | (MSB << 8);
    Cpu->A |= Ram->Data[Address];
    // Flags: N, Z
    // TODO: if not true, clear flag?
    CheckAndSetFlags(Cpu);
}

IMPLEMENT(ORA_zpg)
{
    // ORA $00
    u8 Address = Data[0];
    Cpu->A |= Ram->Data[Address];
    CheckAndSetFlags(Cpu);
}

IMPLEMENT(ASL_zpg)
{
    // C <- 7 6 5 4 3 2 1 0 <- 0
    u16 Address = Data[0];
    if (Ram->Data[Address] & 0x80) {
        SET_FLAG(Cpu->SR, StatusFlag_CARRY);
    } else {
        CLEAR_FLAG(Cpu->SR, StatusFlag_CARRY);
    }
    Ram->Data[Address] <<= 1;
    u8 Value = Ram->Data[Address];
    if (Value & 0x80) {
        SET_FLAG(Cpu->SR, StatusFlag_NEGATIVE);
    }
    if (Value == 0) {
        SET_FLAG(Cpu->SR, StatusFlag_ZERO);
    }
}

IMPLEMENT(PHP)
{
    PushStack(Cpu, Ram, Cpu->SR);
}

IMPLEMENT(PHA)
{
    PushStack(Cpu, Ram, Cpu->A);
}

NOT_IMPLEMENTED(ORA_im){}             // ORA immediate
NOT_IMPLEMENTED(ASL){}                // ASL accumulator
NOT_IMPLEMENTED(ORA_abs ){}
NOT_IMPLEMENTED(ASL_abs){}            // ASL absolute

NOT_IMPLEMENTED(BPL_rel ){}
NOT_IMPLEMENTED(ORA_ind_Y){}          // ORA (zeropage), Y
NOT_IMPLEMENTED(ORA_zpg_X ){}
NOT_IMPLEMENTED(ASL_zpg_X){}          // ASL zeropage, X
NOT_IMPLEMENTED(CLC ){}
NOT_IMPLEMENTED(ORA_abs_Y){}          // ORA absolute, Y
NOT_IMPLEMENTED(ORA_abs_X ){}
NOT_IMPLEMENTED(ASL_abs_X){}          // ASL absolute, X

NOT_IMPLEMENTED(JSR ){}
NOT_IMPLEMENTED(AND_X_ind){}          // AND (zeropage, X)
NOT_IMPLEMENTED(BIT_zpg ){}
NOT_IMPLEMENTED(AND_zpg){}            // AND zeropage
NOT_IMPLEMENTED(ROL_zpg){}            // ROL zeropage
NOT_IMPLEMENTED(PLP ){}
NOT_IMPLEMENTED(AND_im){}             // AND immediate
NOT_IMPLEMENTED(ROL){}                // ROL accumulator,
NOT_IMPLEMENTED(BIT_abs ){}
NOT_IMPLEMENTED(AND_abs){}            // AND absolute
NOT_IMPLEMENTED(ROL_abs){}            // ROL absolute

NOT_IMPLEMENTED(BMI_rel ){}
NOT_IMPLEMENTED(AND_ind_Y){}          // AND (zeropage), Y
NOT_IMPLEMENTED(AND_zpg_X ){}
NOT_IMPLEMENTED(ROL_zpg_X){}          // ROL zeropage, X
NOT_IMPLEMENTED(SEC ){}
NOT_IMPLEMENTED(AND_abs_Y){}          // AND absolute, Y
NOT_IMPLEMENTED(AND_abs_X ){}
NOT_IMPLEMENTED(ROL_abs_X){}          // ROL absolute, X

NOT_IMPLEMENTED(RTI ){}
NOT_IMPLEMENTED(EOR_X_ind){}          // EOR (zeropage, X)
NOT_IMPLEMENTED(EOR_zpg ){}
NOT_IMPLEMENTED(LSR_zpg){}            // LSR zeropage
NOT_IMPLEMENTED(EOR_im){}             // EOR immediate
NOT_IMPLEMENTED(LSR){}                // LSR accumulator
NOT_IMPLEMENTED(JMP_abs ){}
NOT_IMPLEMENTED(EOR_abs){}            // EOR absolute
NOT_IMPLEMENTED(LSR_abs){}            // LSR absolute

NOT_IMPLEMENTED(BVC_rel){}
NOT_IMPLEMENTED(EOR_ind_Y){}          // EOR (zeropage), Y
NOT_IMPLEMENTED(EOR_zpg_X){}
NOT_IMPLEMENTED(LSR_zpg_X){}          // LSR zeropage, X
NOT_IMPLEMENTED(CLI){}
NOT_IMPLEMENTED(EOR_abs_Y){}          // EOR absolute, Y
NOT_IMPLEMENTED(EOR_abs_X){}
NOT_IMPLEMENTED(LSR_abs_X){}          // LSR absolute, X

NOT_IMPLEMENTED(RTS){}
NOT_IMPLEMENTED(ADC_X_ind){}          // ADC (zeropage, X)
NOT_IMPLEMENTED(ADC_zpg){}
NOT_IMPLEMENTED(ROR_zpg){}            // ROR zeropage
NOT_IMPLEMENTED(PLA){}
NOT_IMPLEMENTED(ADC_im){}             // ADC immediate
NOT_IMPLEMENTED(ROR){}                // ROR accumulator
NOT_IMPLEMENTED(JMP_ind){}
NOT_IMPLEMENTED(ADC_abs){}            // ADC absolute
NOT_IMPLEMENTED(ROR_abs){}            // ROR absolute

NOT_IMPLEMENTED(BVS_rel){}
NOT_IMPLEMENTED(ADC_ind_Y){}          // ADC (zeropage), Y
NOT_IMPLEMENTED(ADC_zpg_X){}
NOT_IMPLEMENTED(ROR_zpg_X){}          // ROR zeropage, X
NOT_IMPLEMENTED(SEI){}
NOT_IMPLEMENTED(ADC_abs_Y){}          // ADC absolute, Y
NOT_IMPLEMENTED(ADC_abx_X){}
NOT_IMPLEMENTED(ROR_abs_X){}          // ROR absolute, X

NOT_IMPLEMENTED(STA_X_ind){}
NOT_IMPLEMENTED(STY_zpg){}
NOT_IMPLEMENTED(STA_zpg){}            // STA zeropage
NOT_IMPLEMENTED(STX_zpg){}            // STX zeropage
NOT_IMPLEMENTED(DEY){}
NOT_IMPLEMENTED(TXA){}
NOT_IMPLEMENTED(STY_abs){}
NOT_IMPLEMENTED(STA_abs){}            // STA absolute,
NOT_IMPLEMENTED(STX_abs){}            // STX absolute

NOT_IMPLEMENTED(BCC_rel){}
NOT_IMPLEMENTED(STA_ind_Y){}          // STA (zeropage), Y
NOT_IMPLEMENTED(STY_zpg_X){}
NOT_IMPLEMENTED(STA_zpg_X){}          // STA zeropage, X
NOT_IMPLEMENTED(STX_zpg_Y){}          // STX zeropage, Y
NOT_IMPLEMENTED(TYA){}
NOT_IMPLEMENTED(STA_abs_Y){}          // STA absolute, Y
NOT_IMPLEMENTED(TXS){}                // TXS
NOT_IMPLEMENTED(STA_abs_X){}

NOT_IMPLEMENTED(LDY_im){}
NOT_IMPLEMENTED(LDA_X_ind){}          // LDA (zeropage, X)
NOT_IMPLEMENTED(LDX_im){}             // LDX immediate
NOT_IMPLEMENTED(LDY_zpg){}
NOT_IMPLEMENTED(LDA_zpg){}            // LDA zeropage
NOT_IMPLEMENTED(LDX_zpg){}            // LDX zeropage
NOT_IMPLEMENTED(TAY){}
NOT_IMPLEMENTED(LDA_im){}             // LDA immediate
NOT_IMPLEMENTED(TAX){}                // TAX
NOT_IMPLEMENTED(LDY_abs){}
NOT_IMPLEMENTED(LDA_abs){}            // LDA absolute
NOT_IMPLEMENTED(LDX_abs){}            // LDX absolute

NOT_IMPLEMENTED(BCS_rel){}
NOT_IMPLEMENTED(LDA_ind_Y){}          // LDA (zeropage), Y
NOT_IMPLEMENTED(LDY_zpg_X){}
NOT_IMPLEMENTED(LDA_zpg_X){}          // LDA zeropage, X
NOT_IMPLEMENTED(LDX_zpg_Y){}          // LDX zeropage, Y
NOT_IMPLEMENTED(CLV){}
NOT_IMPLEMENTED(LDA_abs_Y){}          // LDA absolute, Y
NOT_IMPLEMENTED(TSX){}                // TSX
NOT_IMPLEMENTED(LDY_abs_X){}
NOT_IMPLEMENTED(LDA_abs_X){}          // LDA absolute, X
NOT_IMPLEMENTED(LDX_abs_Y){}          // LDX absolute, Y

NOT_IMPLEMENTED(CPY_im){}
NOT_IMPLEMENTED(CMP_X_ind){}          // CMP (zeropage, X)
NOT_IMPLEMENTED(CPY_zpg){}
NOT_IMPLEMENTED(CMP_zpg){}            // CMP zeropage
NOT_IMPLEMENTED(DEC_zpg){}            // DEC zeropage
NOT_IMPLEMENTED(INY){}
NOT_IMPLEMENTED(CMP_im){}             // CMP immediate
NOT_IMPLEMENTED(DEX){}                // DEX
NOT_IMPLEMENTED(CPY_abs){}
NOT_IMPLEMENTED(CMP_abs){}            // CMP absolute
NOT_IMPLEMENTED(DEC_abs){}            // DEC absolute

NOT_IMPLEMENTED(BNE_rel){}
NOT_IMPLEMENTED(CMP_ind_Y){}          // CMP (zeropage), Y
NOT_IMPLEMENTED(CMP_zpg_X){}
NOT_IMPLEMENTED(DEC_zpg_X){}          // DEC zeropage, X
NOT_IMPLEMENTED(CLD){}
NOT_IMPLEMENTED(CMP_abs_Y){}          // CMP absolute, Y
NOT_IMPLEMENTED(CMP_abs_X){}
NOT_IMPLEMENTED(DEC_abs_X){}          // DEC absolute, X

NOT_IMPLEMENTED(CPX_im){}
NOT_IMPLEMENTED(SBC_X_ind){}          // SBC (zeropage, X)
NOT_IMPLEMENTED(CPX_zpg){}
NOT_IMPLEMENTED(SBC_zpg){}            // SBC zeropage
NOT_IMPLEMENTED(INC_zpg){}            // INC zeropage
NOT_IMPLEMENTED(INX){}
NOT_IMPLEMENTED(SBC_im){}             // SBC immediate
NOT_IMPLEMENTED(NOP){}                // NOP
NOT_IMPLEMENTED(CPX_abs){}
NOT_IMPLEMENTED(SBC_abs){}            // SBC absolute
NOT_IMPLEMENTED(INC_abs){}            // INC absolute

NOT_IMPLEMENTED(BEQ_rel){}
NOT_IMPLEMENTED(SBC_ind_Y){}          // SBC (zeropage), Y
NOT_IMPLEMENTED(SBC_zpg_X){}
NOT_IMPLEMENTED(INC_zpg_X){}          // INC zeropage, X
NOT_IMPLEMENTED(SED){}
NOT_IMPLEMENTED(SBC_abs_Y){}          // SBC absolute, Y
NOT_IMPLEMENTED(SBC_abs_X){}
NOT_IMPLEMENTED(INC_abs_X){}

#define INSTRUCTIONS_IMPL_CPP
#endif
