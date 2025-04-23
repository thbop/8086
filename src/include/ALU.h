#ifndef ALU_H
#define ALU_H

enum {
    ALU_ARG_BYTE,
    ALU_ARG_WORD,
};

enum {
    ALU_ADD,
    ALU_SUB,
    ALU_MULT,
    ALU_DIV,
};

typedef struct {
    uint16_t A, B;   // Operation arguments
    uint16_t result; // Operation result
    uint8_t
        operation,   // ALU operation
        size;        // byte or word size of arguments
} ALUOperation_t;

typedef ALUOperation_t ALUResult;

// Performs an ALU operation (addition, subtraction, multiplication, or
// division) and returns the result.
ALUResult ALUOperation( ALUOperation_t operation ) {
    switch (operation.operation) {
        case ALU_ADD:  operation.result = operation.A + operation.B; break;
        case ALU_SUB:  operation.result = operation.A - operation.B; break;
        case ALU_MULT: operation.result = operation.A * operation.B; break;
        case ALU_DIV:  operation.result = operation.A / operation.B; break;
    }
    return (ALUResult)operation;
}

#endif