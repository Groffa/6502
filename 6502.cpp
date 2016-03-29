#include <stdio.h>
#include "6502.h"

// For testing purposes
#include "opcodes.h"

int
main(int argc, char *argv[])
{
    cpu_t Cpu = {0};
    ram_t Ram = {0};

    u8 Program[] = {
        BRK
    };

    u8 ProgramCount = sizeof(Program) / sizeof(Program[0]);

    LoadProgram(&Ram, Program, ProgramCount);
    SingleStepProgram(&Cpu, &Ram);

    return 0;
}
