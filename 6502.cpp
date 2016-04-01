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
    const char *StatusFlags = "\nNOIBDIZC      A  X  Y  PC SP    Memory snapshot (%04x - %04x)\n%s      %-2x %-2x %-2x %-2x %-2x    ";
    const char *Menu = "[s]ingle-step [r]estart [g]oto [+/-] PC [m]emory [q]uit >";
    bool Running = true;
    u16 MemoryDumpStart = 0;
    u8 MemoryDumpCount = 20;
    while (Running) {
        char Input[128] = {0};
        printf(StatusFlags, MemoryDumpStart, MemoryDumpStart + MemoryDumpCount, GetStatusRegisters(Cpu->SR), Cpu->A, Cpu->X, Cpu->Y, Cpu->PC, Cpu->SP);
        // Print memory footprint
        for (u16 MemoryAddress = MemoryDumpStart;
             MemoryAddress < MemoryDumpStart + MemoryDumpCount;
             ++MemoryAddress)
        {
            printf("%2x ", Ram->Data[MemoryAddress]);
        }
        printf("\n");
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

                    case 'g':
                        {
                            printf("Enter new PC: ");
                            scanf("%d", &Cpu->PC);
                            break;
                        }

                    case '+':
                        Cpu->PC++;
                        break;

                    case '-':
                        Cpu->PC--;
                        break;

                    case 'm':
                        {
                            for (u16 Address = MemoryDumpStart;
                                 Address < MemoryDumpStart + 128;
                                 )
                            {
                                printf("%4x  ", Address);
                                for (u16 Offset = 0; Offset < 0xF; ++Offset) {
                                    printf("%-2x ", Ram->Data[Address++]);
                                }
                                printf("\n");
                            }
                            break; 
                        }

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

    //*
    u8 Program[] = {
        ASL_zpg, 0, PHP
    };
    Ram.Data[0] = 0xAA;
    u8 ProgramCount = sizeof(Program) / sizeof(Program[0]);
    LoadProgram(&Ram, Program, ProgramCount, 0x10);
    //*/
    //LoadProgram(&Ram, "rom/atari2600/Vid_olym.bin");
    // SingleStepProgram(&Cpu, &Ram);
    Monitor(&Cpu, &Ram);

    printf("Program ran for %i cycles.\n", Cpu.CycleCount);

    return 0;
}
