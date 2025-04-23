#ifndef REGISTER_H
#define REGISTER_H

// For general purpose registers
typedef union {
    struct {
        uint8_t L, H;
    };
    uint16_t X;
} Register;

// Pointers to two registers
// Reference http://www.mlsite.net/8086/#addr_E
typedef struct {
    void *dest, *src;
} RegisterOperation;


// Register Operation Types
enum {
    REG_OP_EB_GB,
    REG_OP_EV_GV,
};

#endif

// Stuff included after CPU struct definition
#ifdef X8086_H
#ifndef X8086_H_REGISTER_H
#define X8086_H_REGISTER_H

RegisterOperation GetRegisterOperation( CPU *cpu, uint8_t *memory, uint8_t type, uint8_t operation ) {
    RegisterOperation out;
    switch ( type ) {
        case REG_OP_EB_GB: {
            uint8_t *rib[8]; // Register Index Buffer
            rib[0] = &(cpu->A.L); rib[4] = &(cpu->A.H);
            rib[1] = &(cpu->C.L); rib[5] = &(cpu->C.H);
            rib[2] = &(cpu->D.L); rib[6] = &(cpu->D.H);
            rib[3] = &(cpu->B.L); rib[7] = &(cpu->B.H);

            out.dest = rib[ operation & 7 ];
            out.src  = rib[ ( operation >> 3 ) & 7 ];

            break;
        }
        case REG_OP_EV_GV:
            // Check out docs/cpu.md#register-operations
            out.dest = ( (uint16_t*) cpu ) + ( operation & 7 );
            out.src  = ( (uint16_t*) cpu ) + ( ( operation >> 3 ) & 7 );
            break;
    }

    return out;
}

#endif
#endif