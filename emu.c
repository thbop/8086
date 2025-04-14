#include "Core.h"

int main() {
    // Initialize
    CPU cpu;
    CPUReset(&cpu);

    uint8_t *memory = MemoryNew();


    // Little tests
    cpu.CS = 0x0001;
    uint8_t testIns[] = {
        0xB8, 0xD2, 0x04 // mov ax, 1234
    };
    memcpy(MemoryGet(memory, cpu.CS, 0), testIns, sizeof(testIns));

    printf("Instruction: %02X\n", CPUFetchByte(&cpu, memory));
    printf("Data: %02X\n\n", CPUFetchWord(&cpu, memory));

    // Out of bounds
    MemoryWriteByte(memory, 0xFFFF, 0xFFFF, 0xAD);
    printf("Out of bounds data: %02X\n", MemoryReadByte(memory, 0x0FF0, 0x00EF));


    // Cleanup
    MemoryFree(memory);
    return 0;
}