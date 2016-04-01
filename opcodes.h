#ifndef OPCODES_H

// Resource:
// http://e-tradition.net/bytes/6502/6502_instruction_set.html
enum opcode_e
{
    BRK = 0x0,
    ORA_X_ind,          // ORA (zeropage, X)
    ORA_zp = 0x5,       // ORA zeropage
    ASL_zp,             // ASL zeropage
    PHP = 0x8,          // PHP zeropage
    ORA_im,             // ORA immediate
    ASL,                // ASL accumulator
    ORA_abs = 0xD,      // ORA absolute
    ASL_abs,            // ASL absolute
    
    BPL_rel = 0x10,     // BPL relative
    ORA_ind_Y,          // ORA (zeropage), Y
    ORA_zpg_X = 0x15,   // ORA zeropage, X
    ASL_zpg_X,          // ASL zeropage, X
    CLC = 0x18,         // CLC
    ORA_abs_Y,          // ORA absolute, Y
    ORA_abs_X = 0x1D,   // ORA absolute, X
    ASL_abs_X,          // ASL absolute, X
    
    JSR = 0x20,         // JSR absolute
    AND_X_ind,          // AND (zeropage, X)
    BIT_zpg = 0x24,     // BIT zeropage
    AND_zpg,            // AND zeropage
    ROL_zpg,            // ROL zeropage
    PLP = 0x28,         // PLP
    AND_im,             // AND immediate
    ROL,                // ROL accumulator,
    BIT_abs = 0x2C,     // BIT absolute
    AND_abs,            // AND absolute
    ROL_abs,            // ROL absolute

    BMI_rel = 0x30,     // BMI relative
    AND_ind_Y,          // AND (zeropage), Y
    AND_zpg_X = 0x35,   // AND zeropage, X
    ROL_zpg_X,          // ROL zeropage, X
    SEC = 0x38,         // SEC
    AND_abs_Y,          // AND absolute, Y
    AND_abs_X = 0x3D,   // AND absolute, X
    ROL_abs_X,          // ROL absolute, X

    RTI = 0x40,         // RTI
    EOR_X_ind,          // EOR (zeropage, X)
    EOR_zpg = 0x45,     // EOR zeropage
    LSR_zpg,            // LSR zeropage
    PHA = 0x48,         // PHA
    EOR_im,             // EOR immediate
    LSR,                // LSR accumulator
    JMP_abs = 0x4C,     // JMP absolute
    EOR_abs,            // EOR absolute
    LSR_abs,            // LSR absolute

    BVC_rel = 0x50,     // BVC relative
    EOR_ind_Y,          // EOR (zeropage), Y
    EOR_zpg_X = 0x55,   // EOR zeropage, X
    LSR_zpg_X,          // LSR zeropage, X
    CLI = 0x58,         // CLI
    EOR_abs_Y,          // EOR absolute, Y
    EOR_abs_X = 0x5D,   // EOR absolute, X
    LSR_abs_X,          // LSR absolute, X

    RTS = 0x60,         // RTS
    ADC_X_ind,          // ADC (zeropage, X)
    ADC_zpg = 0x65,     // ADC zeropage
    ROR_zpg,            // ROR zeropage
    PLA = 0x68,         // PLA
    ADC_im,             // ADC immediate
    ROR,                // ROR accumulator
    JMP_ind = 0x6C,     // JMP (address)
    ADC_abs,            // ADC absolute
    ROR_abs,            // ROR absolute

    BVS_rel = 0x70,     // BVS relative
    ADC_ind_Y,          // ADC (zeropage), Y
    ADC_zpg_X = 0x75,   // ADC zeropage, X
    ROR_zpg_X,          // ROR zeropage, X
    SEI = 0x78,         // SEI
    ADC_abs_Y,          // ADC absolute, Y
    ADC_abx_X = 0x7D,   // ADC absolute, X
    ROR_abs_X,          // ROR absolute, X

    STA_X_ind = 0x81,   // STA (zeropage, X)
    STY_zpg = 0x84,     // STY zeropage
    STA_zpg,            // STA zeropage
    STX_zpg,            // STX zeropage
    DEY = 0x88,         // DEY
    TXA = 0x8A,         // TXA
    STY_abs = 0x8C,     // STY absolute
    STA_abs,            // STA absolute,
    STX_abs,            // STX absolute

    BCC_rel = 0x90,     // BCC relative
    STA_ind_Y,          // STA (zeropage), Y
    STY_zpg_X = 0x94,   // STY zeropage, X
    STA_zpg_X,          // STA zeropage, X
    STX_zpg_Y,          // STX zeropage, Y
    TYA = 0x98,         // TYA
    STA_abs_Y,          // STA absolute, Y
    TXS,                // TXS
    STA_abs_X = 0x9D,   // STA absolute, X

    LDY_im = 0xA0,      // LDY immediate
    LDA_X_ind,          // LDA (zeropage, X)
    LDX_im,             // LDX immediate
    LDY_zpg = 0xA4,     // LDY zeropage
    LDA_zpg,            // LDA zeropage
    LDX_zpg,            // LDX zeropage
    TAY = 0xA8,         // TAY
    LDA_im,             // LDA immediate
    TAX,                // TAX
    LDY_abs = 0xAC,     // LDY absolute
    LDA_abs,            // LDA absolute
    LDX_abs,            // LDX absolute

    BCS_rel = 0xB0,     // BCS relative
    LDA_ind_Y,          // LDA (zeropage), Y
    LDY_zpg_X = 0xB4,   // LDY zeropage, X
    LDA_zpg_X,          // LDA zeropage, X
    LDX_zpg_Y,          // LDX zeropage, Y
    CLV = 0xB8,         // CLV
    LDA_abs_Y,          // LDA absolute, Y
    TSX,                // TSX
    LDY_abs_X = 0xBC,   // LDY absolute, X
    LDA_abs_X,          // LDA absolute, X
    LDX_abs_Y,          // LDX absolute, Y

    CPY = 0xC0,         // CPY
    CMP_X_ind,          // CMP (zeropage, X)
    CPY_zpg = 0xC4,     // CPY zeropage
    CMP_zpg,            // CMP zeropage
    DEC_zpg,            // DEC zeropage
    INY = 0xC8,         // INY
    CMP_im,             // CMP immediate
    DEX,                // DEX
    CPY_abs = 0xCC,     // CPY absolute
    CMP_abs,            // CMP absolute
    DEC_abs,            // DEC absolute

    BNE_rel = 0xD0,     // BNE relative
    CMP_ind_Y,          // CMP (zeropage), Y
    CMP_zpg_X = 0xD5,   // CMP zeropage, X
    DEC_zpg_X,          // DEC zeropage, X
    CLD = 0xD8,         // CLD
    CMP_abs_Y,          // CMP absolute, Y
    CMP_abs_X = 0xDD,   // CMP absolute, X
    DEC_abs_X,          // DEC absolute, X

    CPX_im = 0xE0,      // CMP immediate
    SBC_X_ind,          // SBC (zeropage, X)
    CPX_zpg = 0xE4,     // CPX zeropage
    SBC_zpg,            // SBC zeropage
    INC_zpg,            // INC zeropage
    INX = 0xE8,         // INX
    SBC_im,             // SBC immediate
    NOP,                // NOP
    CPX_abs = 0xEC,     // CPX absolute
    SBC_abs,            // SBC absolute
    INC_abs,            // INC absolute

    BEQ_rel = 0xF0,     // BEQ relative
    SBC_ind_Y,          // SBC (zeropage), Y
    SBC_zpg_X = 0xF5,   // SBC zeropage, X
    INC_zpg_X,          // INC zeropage, X
    SED = 0xF8,         // SED
    SBC_abs_Y,          // SBC absolute, Y
    SBC_abs_X = 0xFD,   // SBC absolute, X
    INC_abs_X           // INC absolute, X
};

#define OPCODES_H
#endif
