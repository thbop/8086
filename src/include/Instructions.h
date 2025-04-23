#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// Based on: http://www.mlsite.net/8086/

// Classes (the upper 4 bits) -------------------------------------------------
enum {
    CLASS_00     = 0x00,
    CLASS_80     = 0x80,
    CLASS_MOV_IM = 0xB0,
    CLASS_F0     = 0xF0,
};


// Targets (lower 4 bits) -----------------------------------------------------

// Class 00
enum {
    C00_ADD_EB_GB,
    C00_ADD_EV_GV,
    C00_ADD_GB_EB,
    C00_ADD_GV_EV,
    C00_ADD_AL_IB,
    C00_ADD_AX_IV,
    C00_PUSH_ES,
    C00_POP_ES,
    C00_OR_EB_GB,
    C00_OR_EV_GV,
    C00_OR_GB_EB,
    C00_OR_GV_EV,
    C00_OR_AL_IB,
    C00_OR_AX_IV,
    C00_PUSH_CS,
};

// Class 80
enum {
    C80_MOV_EB_GB = 0x08,
    C80_MOV_EV_GV = 0x09,
};

// Move Immediate
enum {
    MOV_AL_IB,
    MOV_CL_IB,
    MOV_DL_IB,
    MOV_BL_IB,
    MOV_AH_IB,
    MOV_CH_IB,
    MOV_DH_IB,
    MOV_BH_IB,
    MOV_AX_IV,
    MOV_CX_IV,
    MOV_DX_IV,
    MOV_BX_IV,
    MOV_SP_IV,
    MOV_BP_IV,
    MOV_SI_IV,
    MOV_DI_IV,
};

// Class F0
enum {
    CF0_HLT = 0x04,
};


#endif