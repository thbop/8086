#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// Based on: http://www.mlsite.net/8086/

// Classes (the upper 4 bits) -------------------------------------------------
enum {
    CLASS_MOV_IM = 0xB0,
};

// Targets (lower 4 bits) -----------------------------------------------------


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


#endif