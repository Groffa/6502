#ifndef INSTRUCTIONS_IMPL_CPP

INSTRUCT(BRK)
{
    // set interrupt flag
    // push pc+2
    // push sr
    PushStack(Cpu, Ram, Cpu->PC + 2);
    PushStack(Cpu, Ram, Cpu->SR);
    SET_FLAG(Cpu->SR, StatusFlag_INTERRUPT);
}

INSTRUCT(ORA_X_ind)
{
    // ORA (oper,X)
    // A OR M -> A
    u8 LSB = Data[0] + Cpu->X;
    u8 MSB = LSB + 1;
    u16 Address = LSB | (MSB << 8);
    Cpu->A |= Ram->Data[Address];
    // Flags: N, Z
    // TODO: if not true, clear flag?
    if (Cpu->A == 0) {
        SET_FLAG(Cpu->SR, StatusFlag_ZERO);
    }
    if (Cpu->A & 0x80) {
        SET_FLAG(Cpu->SR, StatusFlag_NEGATIVE);
    }
}

INSTRUCT(PHA)
{
    // Push accumulator on stack
    PushStack(Cpu, Ram, Cpu->A);
}


#define INSTRUCTIONS_IMPL_CPP
#endif
