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
    FLAG_SET_0,
    FLAG_SET_1,
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
            switch ( result.size ) {
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
    switch ( result.size ) {
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
    switch ( result.size ) {
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

// Sets the auxiliary carry flag if carry from bit 3 to bit 4 or a borrow from
// bit 4 to bit 3
void FlagSetAuxiliary( Flags *flags, ALUResult result ) {
    // Unfortunately, ChatGPT helped out with this one
    flags->AF = ( (result.A ^ result.B ^ result.result ) & 0x10 ) != 0;
}

// Sets all flags given the flags, a flag setter, and an ALU result
void FlagSet( Flags *flags, FlagSetter setter, ALUResult result ) {
    // There is a better way to do this, but since flags are bit fields I do
    // not have many good options.

    // TODO: Refactor sort of everything so that this function does not violate
    // DRY.

    // Carry flag
    switch ( setter.C ) {
        case FLAG_SET_0:        flags->CF = 0;                   break;
        case FLAG_SET_1:        flags->CF = 1;                   break;
        case FLAG_SET_REGISTER: FlagSetCarry(flags, result);     break;
    }

    // Zero flag
    switch ( setter.Z ) {
        case FLAG_SET_0:        flags->ZF = 0;                   break;
        case FLAG_SET_1:        flags->ZF = 1;                   break;
        case FLAG_SET_REGISTER: FlagSetZero(flags, result);      break;
    }

    // Sign flag
    switch ( setter.S ) {
        case FLAG_SET_0:        flags->SF = 0;                   break;
        case FLAG_SET_1:        flags->SF = 1;                   break;
        case FLAG_SET_REGISTER: FlagSetSign(flags, result);      break;
    }

    // Overflow flag
    switch ( setter.O ) {
        case FLAG_SET_0:        flags->OF = 0;                   break;
        case FLAG_SET_1:        flags->OF = 1;                   break;
        case FLAG_SET_REGISTER: FlagSetOverflow(flags, result);  break;
    }

    // Parity flag
    switch ( setter.P ) {
        case FLAG_SET_0:        flags->PF = 0;                   break;
        case FLAG_SET_1:        flags->PF = 1;                   break;
        case FLAG_SET_REGISTER: FlagSetParity(flags, result);    break;
    }

    // Auxilary flag
    switch ( setter.A ) {
        case FLAG_SET_0:        flags->AF = 0;                   break;
        case FLAG_SET_1:        flags->AF = 1;                   break;
        case FLAG_SET_REGISTER: FlagSetAuxiliary(flags, result); break;
    }
}

#endif