#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
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

static void
Monitor(cpu_t *Cpu, ram_t *Ram)
{
    const char *StatusFlags = "\nNOIBDIZC\n%s\n";
    const char *Menu = "[s]ingle-step  [r]estart  [q]uit >";
    bool Running = true;
    while (Running) {
        char Input[128] = {0};
        printf(StatusFlags, GetStatusRegisters(Cpu->SR));
        
        opcode_e OpCode = (opcode_e)Ram->Data[Cpu->PC];
        instruction_t Instruction = DecodeOpCode(OpCode);
        char *OpCodeName = "(not impl)";
        if (Instruction.Func) {
            OpCodeName = Instruction.OpCodeName;
        }
        printf("%2X: %9s (%2x) ", Cpu->PC, OpCodeName, OpCode);
        
        printf(Menu);
        scanf("%127s", Input);
        
        if (Input) {
            for (char *CurrentInput = Input; *CurrentInput; ++CurrentInput) {
                switch (*CurrentInput) {
                    case 'r':
                        memset(Cpu, 0, sizeof(cpu_t));
                        break;

                    case 'q':
                        Running = false;
                        break;

                    case 's':
                        SingleStepProgram(Cpu, Ram);
                        break;
                }
            }
        }
    }
}

int
main(int argc, char *argv[])
{
    cpu_t Cpu = {0};
    ram_t Ram = {0};

    /*
    u8 Program[] = {
        BRK, BRK, BRK
    };
    u8 ProgramCount = sizeof(Program) / sizeof(Program[0]);
    LoadProgram(&Ram, Program, ProgramCount);
    */
    LoadProgram(&Ram, "rom/atari2600/Vid_olym.bin");
    // SingleStepProgram(&Cpu, &Ram);
    Monitor(&Cpu, &Ram);

    printf("Program ran for %i cycles.\n", Cpu.CycleCount);

    return 0;
}
