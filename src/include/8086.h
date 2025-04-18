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


typedef struct {
    // https://www.geeksforgeeks.org/types-of-registers-in-8086-microprocessor/
    Register A, C, D, B;         // General purpose registers
    uint16_t SP, BP, SI, DI, IP; // Special purpose registers
    uint16_t CS, DS, SS, ES;     // Segment registers
    Flags flags;                 // Flags
} CPU;

// Pointers to two registers
// Reference http://www.mlsite.net/8086/#addr_E
typedef struct {
    uint16_t *dest, *src;
} RegisterOperation;



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
RegisterOperation CPUFetchRegisterOperation( CPU *cpu, uint8_t *memory, uint8_t registerOperationType ) {
    uint8_t operation = CPUFetchByte(cpu, memory);
    RegisterOperation out;

    switch ( registerOperationType ) {
        case REG_OP_EV_GV:
            // Check out docs/cpu.md#register-operations
            out.dest = ( (uint16_t*) cpu ) + ( operation & 7 );
            out.src  = ( (uint16_t*) cpu ) + ( ( operation >> 3 ) & 7 );
            break;
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
                RegisterOperation regOp = CPUFetchRegisterOperation(cpu, memory, REG_OP_EV_GV);
                *(regOp.dest) = *(regOp.src);
            }
            break;
    }
}


#endif