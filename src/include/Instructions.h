#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// Based on: http://www.mlsite.net/8086/

// Classes (the upper 4 bits) -------------------------------------------------
enum {
    CLASS_80     = 0x80,
    CLASS_MOV_IM = 0xB0,
    CLASS_F0     = 0xF0,
};


// Targets (lower 4 bits) -----------------------------------------------------

// Class 80
enum {
    C80_MOV_EB_GB = 0x08,
    C80_MOV_EV_GV = 0x09,
};

// Move Immediate
enum {
    MOV_IM_AL = 0x00,
    MOV_IM_CL = 0x01,
    MOV_IM_DL = 0x02,
    MOV_IM_BL = 0x03,
    MOV_IM_AH = 0x04,
    MOV_IM_CH = 0x05,
    MOV_IM_DH = 0x06,
    MOV_IM_BH = 0x07,
    MOV_IM_AX = 0x08,
    MOV_IM_CX = 0x09,
    MOV_IM_DX = 0x0A,
    MOV_IM_BX = 0x0B,
    MOV_IM_SP = 0x0C,
    MOV_IM_BP = 0x0D,
    MOV_IM_SI = 0x0E,
    MOV_IM_DI = 0x0F,
};

// Class F0
enum {
    CF0_HLT = 0x04,
};

// Misc -----------------------------------------------------------------------

// Register Operation Types
enum {
    REG_OP_EB_GB,
    REG_OP_EV_GV,
};


#endif