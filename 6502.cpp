#include <stdio.h>
#include <stdlib.h>
#include "6502.h"

// For testing purposes
#include "opcodes.h"

static bool
LoadProgram(ram_t *Ram, const char *Filename)
{
    FILE *File = fopen(Filename, "rb");
    bool Result = false;
    if (File) {
        Result = true;
        fseek(File, 0, SEEK_END);
        u16 ProgramSize = ftell(File);
        fseek(File, 0, SEEK_SET);
        u8 *Program = (u8 *)calloc(ProgramSize, 1);
        fread(Program, 1, ProgramSize, File);
        fclose(File);
        free(Program);

        LoadProgram(Ram, Program, ProgramSize);
    }
    return Result;
}

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

    printf("Program ran for %i cycles.\n", Cpu.CycleCount);

    return 0;
}
