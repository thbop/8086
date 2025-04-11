#ifndef X8086_H
#define X8086_H

typedef union {
    struct {
        uint8_t l, h;
    };
    uint16_t x;
} Register;

typedef struct {
    Register a;
} CPU;


#endif