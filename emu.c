#include "Core.h"

int main() {
    CPU cpu;
    uint8_t *memory = MemoryNew();

    memory[0x1000] = 0xAD;
    memory[0x1001] = 0xDE;

    printf("%02X ", MemoryReadWord(memory, 0x0000, 0x1000));

    MemoryWriteWord(memory, 0x0001, 0x1000, 0xBEEF);

    printf("%02X ", MemoryReadWord(memory, 0x0001, 0x1000));

    MemoryWriteByte(memory, 0x0000, 0x1000, 0xED);

    printf("%02X\n", MemoryReadWord(memory, 0x0000, 0x1000));

    MemoryFree(memory);
    
    return 0;
}