#ifndef INSTRUCTIONS_IMPL_CPP

INSTRUCT(BRK)
{
    // set interrupt flag
    // push pc+2
    // push sr
    SET_FLAG(Cpu->SR, StatusFlag_INTERRUPT);
}

INSTRUCT(ORA__X)
{
    // ORA (oper,X)
    // A OR M -> A
    u8 LSB = Data[0] + Cpu->X;
    u8 MSB = LSB + 1;
    u16 Address = LSB | (MSB << 8);
    Cpu->A |= Ram->Data[Address];
}

INSTRUCT(PHA)
{
    // Push accumulator on stack
    PushStack(Cpu, Ram, Cpu->A);
}


#define INSTRUCTIONS_IMPL_CPP
#endif
