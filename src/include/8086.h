#ifndef X8086_H
#define X8086_H

// Definitions ----------------------------------------------------------------

// For general purpose registers
typedef union {
    struct {
        uint8_t L, H;
    };
    uint16_t X;
} Register;

typedef union {
    // https://www.geeksforgeeks.org/types-of-registers-in-8086-microprocessor/
    struct {
        uint16_t
            CF  : 1, // Carry Flag
            _u0 : 1,
            PF  : 1, // Parity Flag
            _u1 : 1,
            AF  : 1, // Auxiliary Carry Flag
            _u2 : 1,
            ZF  : 1, // Zero Flag
            SF  : 1, // Sign Flag
            TF  : 1, // Trap Flag
            IF  : 1, // Interrupt Flag
            DF  : 1, // Direction Flag
            OF  : 1; // Overflow Flag
    };
    uint16_t value;
} Flags;

// Register operation sources (low/high)
// Reference http://www.mlsite.net/8086/#addr_E
enum {
    REGISTER_OP_SRC_AC   = 0xC, // AX = low; CX = high
    REGISTER_OP_SRC_DB   = 0xD, // DX = low; BX = high
    REGISTER_OP_SRC_SPBP = 0xE, // SP = low; BP = high
    REGISTER_OP_SRC_SIDI = 0xF, // SI = low; DI = high
};

// Register operation destinations
// Reference http://www.mlsite.net/8086/#addr_E
enum {
    REGISTER_OP_DEST_A,
    REGISTER_OP_DEST_C,
    REGISTER_OP_DEST_D,
    REGISTER_OP_DEST_B,
    REGISTER_OP_DEST_SP,
    REGISTER_OP_DEST_BP,
    REGISTER_OP_DEST_SI,
    REGISTER_OP_DEST_DI,
};

// Pointers to two registers
// Reference http://www.mlsite.net/8086/#addr_E
typedef struct {
    uint16_t *dest, *src;
} RegisterOperation;

typedef struct {
    // https://www.geeksforgeeks.org/types-of-registers-in-8086-microprocessor/
    Register A, B, C, D;         // General purpose registers
    uint16_t SP, BP, SI, DI, IP; // Special purpose registers
    uint16_t CS, DS, SS, ES;     // Segment registers
    Flags flags;                 // Flags
} CPU;


// Helper functions -----------------------------------------------------------

// Sets all CPU registers and flags to zero
void CPUReset( CPU *cpu ) {
    memset(cpu, 0, sizeof(CPU));
}

// Fetches the byte located at CS:IP and increments IP (program counter)
uint8_t CPUFetchByte( CPU *cpu, uint8_t *memory ) {
    return MemoryReadByte(memory, cpu->CS, cpu->IP++);
}

// Fetches the word located at CS:IP and increments IP by 2
uint16_t CPUFetchWord( CPU *cpu, uint8_t *memory ) {
    uint16_t value = MemoryReadWord(memory, cpu->CS, cpu->IP);
    cpu->IP += 2;
    return value;
}

// Fetches, parses, and returns the correct register operation
// Reference http://www.mlsite.net/8086/#addr_E
RegisterOperation CPUFetchRegisterOperation( CPU *cpu, uint8_t *memory ) {
    uint8_t operation = CPUFetchByte(cpu, memory);
    RegisterOperation out;

    // Destination
    switch (operation & 7) {
        case REGISTER_OP_DEST_A:  out.dest = (uint16_t*)&cpu->A;  break;
        case REGISTER_OP_DEST_C:  out.dest = (uint16_t*)&cpu->C;  break;
        case REGISTER_OP_DEST_D:  out.dest = (uint16_t*)&cpu->D;  break;
        case REGISTER_OP_DEST_B:  out.dest = (uint16_t*)&cpu->B;  break;
        case REGISTER_OP_DEST_SP: out.dest = (uint16_t*)&cpu->SP; break;
        case REGISTER_OP_DEST_BP: out.dest = (uint16_t*)&cpu->BP; break;
        case REGISTER_OP_DEST_SI: out.dest = (uint16_t*)&cpu->SI; break;
        case REGISTER_OP_DEST_DI: out.dest = (uint16_t*)&cpu->DI; break;
    }

    // Source
    if ( ( operation & 0x0F ) < 8 ) { // Lows
        switch ( operation >> 4 ) {
            case REGISTER_OP_SRC_AC:   out.src = (uint16_t*)&cpu->A;  break;
            case REGISTER_OP_SRC_DB:   out.src = (uint16_t*)&cpu->D;  break;
            case REGISTER_OP_SRC_SPBP: out.src = (uint16_t*)&cpu->SP; break;
            case REGISTER_OP_SRC_SIDI: out.src = (uint16_t*)&cpu->SI; break;
        }
    } else {                          // Highs
        switch ( operation >> 4 ) {
            case REGISTER_OP_SRC_AC:   out.src = (uint16_t*)&cpu->C;  break;
            case REGISTER_OP_SRC_DB:   out.src = (uint16_t*)&cpu->B;  break;
            case REGISTER_OP_SRC_SPBP: out.src = (uint16_t*)&cpu->BP; break;
            case REGISTER_OP_SRC_SIDI: out.src = (uint16_t*)&cpu->DI; break;
        }
    }

    return out;
}


// Instruction execution ------------------------------------------------------

// Executes move immediate instructions by switching through the
// lower 4 bits (target) of the instruction
void CPUMoveImmediate( CPU *cpu, uint8_t *memory, uint8_t target ) {
    switch (target) {
        case MOV_IM_AL: cpu->A.L = CPUFetchByte(cpu, memory); break;
        case MOV_IM_CL: cpu->C.L = CPUFetchByte(cpu, memory); break;
        case MOV_IM_DL: cpu->D.L = CPUFetchByte(cpu, memory); break;
        case MOV_IM_BL: cpu->B.L = CPUFetchByte(cpu, memory); break;
        case MOV_IM_AH: cpu->A.H = CPUFetchByte(cpu, memory); break;
        case MOV_IM_CH: cpu->C.H = CPUFetchByte(cpu, memory); break;
        case MOV_IM_DH: cpu->D.H = CPUFetchByte(cpu, memory); break;
        case MOV_IM_BH: cpu->B.H = CPUFetchByte(cpu, memory); break;
        case MOV_IM_AX: cpu->A.X = CPUFetchWord(cpu, memory); break;
        case MOV_IM_CX: cpu->C.X = CPUFetchWord(cpu, memory); break;
        case MOV_IM_DX: cpu->D.X = CPUFetchWord(cpu, memory); break;
        case MOV_IM_BX: cpu->B.X = CPUFetchWord(cpu, memory); break;
        case MOV_IM_SP: cpu->SP  = CPUFetchWord(cpu, memory); break;
        case MOV_IM_BP: cpu->BP  = CPUFetchWord(cpu, memory); break;
        case MOV_IM_SI: cpu->SI  = CPUFetchWord(cpu, memory); break;
        case MOV_IM_DI: cpu->DI  = CPUFetchWord(cpu, memory); break;
    }
}




// Executes one instruction
void CPUExecute( CPU *cpu, uint8_t *memory ) {
    uint8_t instruction = CPUFetchByte(cpu, memory);
    switch (instruction & 0xF0) {
        case CLASS_MOV_IM:
            CPUMoveImmediate(cpu, memory, instruction & 0x0F);
            break;

        // TODO: Structure this better
        case 0x80:
            if ( (instruction & 0x0F) == 0x09 ) {
                RegisterOperation regOp = CPUFetchRegisterOperation(cpu, memory);
                *(regOp.dest) = *(regOp.src);
            }
            break;
    }
}


#endif