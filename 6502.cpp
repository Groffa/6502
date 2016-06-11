#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include "6502.h"

// For testing purposes
#include "opcodes.h"

static u16
HexStringToInt(char *HexString, u8 HexStringSize = 4)
{
    u16 Result = 0;
    for (u8 HexIndex=0; HexIndex < HexStringSize; ++HexIndex) {
        char Hex = *(HexString + HexIndex);
        u8 Value = 0;
        if (Hex >= '0' && Hex <= '9') {
            Value = Hex - '0';
        } else if (Hex >= 'A' && Hex <= 'F') {
            Value = (Hex - 'A') + 10;
        } else if (Hex >= 'a' && Hex <= 'f') {
            Value = (Hex - 'a') + 10;
        }
        u16 Position = HexStringSize - HexIndex - 1;
        Result += (u16)pow(16, (float)Position) * Value;
    }
    return Result;
}

static bool
LoadProgram(ram_t *Ram, const char *Filename, u16 Base = 0)
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

        LoadProgram(Ram, Program, ProgramSize, Base);
    }
    return Result;
}

static void
MemoryDump(ram_t *Ram, u16 StartAddress, u16 Length, u16 ColumnWidth, u16 MarkAddress = 0)
{
    for (u16 Address = StartAddress; 
        Address < StartAddress + Length;
        )
    {
        printf("%4x  ", Address);
        for (u16 Offset = 0; Offset < ColumnWidth; ++Offset) {
            bool MarkThisOne = (MarkAddress > 0 && MarkAddress == Address);
            if (MarkThisOne) {
                printf("[");
            }
            printf("%-2x", Ram->Data[Address++]);
            if (MarkThisOne) {
                printf("]");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

static void
Monitor(cpu_t *Cpu, ram_t *Ram)
{
    const char *StatusFlags = "\nNOIBDIZC      A  X  Y  PC SP    Memory snapshot (%04x - %04x)\n%s      %-2x %-2x %-2x %-2x %-2x    ";
    const char *Menu = "[s]ingle-step [r]estart [g]oto [+/-] PC [m]emory s[t]ack [q]uit >";
    bool Running = true;
    u16 MemoryDumpStart = 0;
    u8 MemoryDumpCount = 20;
    bool PrintOpCode = false;   // TODO: turn into menu choice
    cpu_t OriginalCpuState = *Cpu;
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
        char OpCodeName[32] = "(not impl)";
        if (Instruction.Func) {
            strncpy(OpCodeName, Instruction.OpCodeName, sizeof(OpCodeName));
        }
        //printf("%2X: %9s (%2x) ", Cpu->PC, OpCodeName, OpCode);
        printf("%s", OpCodeName);
        if (PrintOpCode) {
            printf("(%2x)", OpCode);
        }
        for (u8 i = 0; i < Instruction.Bytes; ++i) {
            printf(" %2x", Ram->Data[Cpu->PC + i + 1]);
        }
        printf("       ");

        printf(Menu);
        scanf("%127s", Input);
        
        if (Input) {
            for (char *CurrentInput = Input; *CurrentInput; ++CurrentInput) {
                switch (*CurrentInput) {
                    case 'r':
                        //memset(Cpu, 0, sizeof(cpu_t));
                        *Cpu = OriginalCpuState;
                        break;

                    case 'q':
                        Running = false;
                        break;

                    case 's':
                        SingleStepProgram(Cpu, Ram);
                        break;

                    case 't':
                        MemoryDump(Ram, STACK_ADDR(0), 0xFF, 0xF, STACK_ADDR(Cpu->SP));
                        break;

                    case 'g':
                        {
                            char NewAddress[4] = {0};
                            printf("Enter new PC in hex (type - to cancel): 0x");
                            scanf("%4s", NewAddress);
                            Cpu->PC = HexStringToInt(NewAddress, 4); 
                            break;
                        }

                    case '+':
                        Cpu->PC++;
                        break;

                    case '-':
                        Cpu->PC--;
                        break;

                    case 'm':
                        MemoryDump(Ram, MemoryDumpStart, 128, 16, MemoryDumpStart);
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
        ASL_zpg, 0, PHP
    };
    Ram.Data[0] = 0xAA;
    u8 ProgramCount = sizeof(Program) / sizeof(Program[0]);
    LoadProgram(&Ram, Program, ProgramCount, 0x10);
    //*/
    // LoadProgram(&Ram, "rom/atari2600/Vid_olym.bin");
    
    const char *ROMName = "rom/w2/snake";
    LoadProgram(&Ram, ROMName, 0x7000);      // Wasteland 2 Snake program (easter egg)
    Cpu.PC = 0x7000;
    printf("Loaded ROM %s at 0x%x.\n", ROMName, Cpu.PC);
    Monitor(&Cpu, &Ram);

    printf("Program ran for %i cycles.\n", Cpu.CycleCount);

    return 0;
}
