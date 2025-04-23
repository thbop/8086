#ifndef FLAGS_H
#define FLAGS_H

// For setting and reading CPU flags

// Definitions ----------------------------------------------------------------
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

enum {
    FLAG_SET_1,
    FLAG_SET_0,
    FLAG_SET_REGISTER,
    FLAG_SET_UNDEFINED, // Unused
};


typedef struct {
    uint8_t C, Z, S, O, P, A;
} FlagSetter;

// Functions ------------------------------------------------------------------

// Sets the carry flag when appropriate for either byte or word arguments.
void FlagSetCarry( Flags *flags, ALUResult result ) {
    switch ( result.operation ) {
        case ALU_ADD:                                       // Addition
            switch (result.size) {
                case ALU_ARG_BYTE:
                    flags->CF = ( result.result > 0xFF );
                    break;
                case ALU_ARG_WORD:
                    flags->CF = ( result.result > 0xFFFF );
                    break;
            }
            break;
        case ALU_SUB:                                       // Subtraction
            flags->CF = ( result.B > result.A );
            break;
    }
}

// Sets the zero flag when the result is zero
void FlagSetZero( Flags *flags, ALUResult result ) {
    flags->ZF = !result.result;
}

// Sets the sign flag when the result is negative
void FlagSetSign( Flags *flags, ALUResult result ) {
    switch (result.size) {
        case ALU_ARG_BYTE:
            flags->SF = ( (int8_t)result.result < 0 );
            break;
        case ALU_ARG_WORD:
            flags->SF = ( (int16_t)result.result < 0 );
            break;
    }
}

// Sets the overflow flag if the result overflows a register
void FlagSetOverflow( Flags *flags, ALUResult result ) {
    switch (result.size) {
        case ALU_ARG_BYTE:
            flags->OF = ( (int8_t)result.result != (int32_t)result.result );
            break;
        case ALU_ARG_WORD:
            flags->OF = ( (int16_t)result.result != (int32_t)result.result );
            break;
    }
}

// Sets the parity flag if the result's LSB has an even number of 1's
void FlagSetParity( Flags *flags, ALUResult result ) {
    flags->PF = !__builtin_parity(result.result & 0xFF);
}

// Sets the auxiliary carry flag if ...
void FlagSetAuxiliary( Flags *flags, ALUResult result ) {
    
}

#endif