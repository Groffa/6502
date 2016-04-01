#ifndef INSTRUCTIONS_IMPL_CPP

#define IMPLEMENT(OpCode)  void OpCode##_func(cpu_t *Cpu, ram_t *Ram, u8 *Data)

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

IMPLEMENT(PHA)
{
    // Push accumulator on stack
    PushStack(Cpu, Ram, Cpu->A);
}


#define INSTRUCTIONS_IMPL_CPP
#endif
