#include "Core.h"

void LoadProgram( CPU *cpu, uint8_t *memory ) {
    // This will only work if you run emu.exe from outside the build directory
    uint8_t *fileBuffer = StorageLoadSectors("build/main.bin", 0, 1);
    StorageLoad(fileBuffer, 1, memory, cpu->CS);
    free(fileBuffer);
}

int main() {
    // Initialize
    CPU cpu;
    CPUReset(&cpu);
    cpu.CS = 0x0500;

    uint8_t *memory = MemoryNew();
    LoadProgram(&cpu, memory);


    while (cpu.running)
        CPUExecute(&cpu, memory);

    // printf("AX=%02X BX=%02X\n", cpu.A.X, cpu.B.X);

    ALUOperation_t operation = {
        .A = 127, .B = 1,
        .operation = ALU_ADD,
        .size = ALU_ARG_BYTE,
    };
    ALUResult result = ALUOperation(operation);
    FlagSetter setter = {
        .C = FLAG_SET_0,
        .Z = FLAG_SET_REGISTER,
        .S = FLAG_SET_REGISTER,
        .O = FLAG_SET_0,
        .P = FLAG_SET_REGISTER,
    };
    FlagSet(&cpu.flags, setter, result);
    printf("%02X\n", cpu.flags.OF);


    // Cleanup
    MemoryFree(memory);
    return 0;
}