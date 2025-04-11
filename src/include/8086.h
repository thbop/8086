#ifndef X8086_H
#define X8086_H

typedef union {
    struct {
        uint8_t l, h;
    };
    uint16_t x;
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
    Register a, b, c, d;         // General purpose registers
    uint16_t sp, bp, si, di, ip; // Special purpose registers
    uint16_t cs, ds, ss, es;     // Segment registers
    Flags flags;                 // Flags
} CPU;


#endif