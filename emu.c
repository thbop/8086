#include "Core.h"

void LoadProgram( uint8_t *memory ) {
    // This will only work if you run emu.exe from outside the build directory
    uint8_t *fileBuffer = StorageLoadSectors("build/main.bin", 0, 1);
    StorageLoad(fileBuffer, 1, memory, 0x0500);
    free(fileBuffer);
}

int main() {
    // Initialize
    CPU cpu;
    CPUReset(&cpu);
    cpu.CS = 0x0500;

    uint8_t *memory = MemoryNew();
    LoadProgram(memory);

    printf("Instruction: %02X\n", CPUFetchByte(&cpu, memory));
    printf("Argument: %02X\n", CPUFetchWord(&cpu, memory));

    // Cleanup
    MemoryFree(memory);
    return 0;
}