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
        ORA__X, 0, 1
    };

    u8 ProgramCount = sizeof(Program) / sizeof(Program[0]);

    LoadProgram(&Ram, Program, ProgramCount);
    Cpu.X = 0; 
    Cpu.A = 255;
    SingleStepProgram(&Cpu, &Ram);

    return 0;
}
