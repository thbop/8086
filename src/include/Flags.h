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
// Essentially, it evaluates the result of an ALU operation, 8 or 16 bit, and
// sets the carry flag if 8th or 16th bits are set respectively.
void FlagSetCarry( Flags *flags, uint32_t result, uint8_t size ) {
    // TODO: Check if this handles subtraction borrows correctly
    switch (size) {
        case FLAG_ARG_BYTE:
            if ( ( result >> 7 ) & 1 ) flags->CF = 1;
            else                       flags->CF = 0;
            break;
        case FLAG_ARG_WORD:
            if ( ( result >> 15 ) & 1 ) flags->CF = 1;
            else                        flags->CF = 0;
            break;
    }
}

// Sets the zero flag when the result is zero
void FlagSetZero( Flags *flags, uint32_t result ) {
    if ( !result ) flags->ZF = 1;
    else           flags->ZF = 0;
}

// Sets the sign flag when the result is negative
void FlagSetSign( Flags *flags, uint32_t result, uint8_t size ) {
    switch (size) {
        case FLAG_ARG_BYTE:
            if ( ( result >> 6 ) & 1 ) flags->SF = 1;
            else                       flags->SF = 0;
            break;
        case FLAG_ARG_WORD:
            if ( ( result >> 14 ) & 1 ) flags->SF = 1;
            else                        flags->SF = 0;
            break;
    }
}

// Sets the overflow flag if the result overflows a register
void FlagSetOverflow( Flags *flags, uint32_t result, uint8_t size ) {
    // Inaccurate
    // switch (size) {
    //     case FLAG_ARG_BYTE:
    //         if ( result >> 8 ) flags->OF = 1;
    //         else               flags->OF = 0;
    //         break;
    //     case FLAG_ARG_WORD:
    //         if ( result >> 16 ) flags->OF = 1;
    //         else                flags->OF = 0;
    //         break;
    // }
}

// Sets the parity flag if the result's LSB has an even number of 1's
void FlagSetParity( Flags *flags, uint32_t result ) {
    flags->PF = !__builtin_parity(result & 0xFF);
}

// Sets the auxiliary carry flag if ...
void FlagSetAuxiliary( Flags *flags, FlagOperation operation ) {
    
}

#endif