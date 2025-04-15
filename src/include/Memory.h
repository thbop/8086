#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_MAX_SIZE  0x100000
#define MEMORY_MAX_INDEX (MEMORY_MAX_SIZE-1)

// Allocate 1 Mb of memory
uint8_t *MemoryNew() {
    // 0x00000 - 0xFFFFF
    uint8_t *memory = calloc(MEMORY_MAX_SIZE, 1);
    if ( memory == NULL )
        fprintf(stderr, "Failed to allocate emulator memory!\n");

    return memory;
}

// Returns a pointer to the given segment and offset
uint8_t *MemoryGet( uint8_t *memory, uint16_t segment, uint16_t offset ) {
    return memory + ((( segment << 4 ) + offset) & MEMORY_MAX_INDEX);
}

// Returns a byte from a given segment and offset
uint8_t MemoryReadByte( uint8_t *memory, uint16_t segment, uint16_t offset ) {
    return *MemoryGet(memory, segment, offset);
}

// Returns a word from a given segment and offset
uint16_t MemoryReadWord( uint8_t *memory, uint16_t segment, uint16_t offset ) {
    return *(uint16_t*)MemoryGet(memory, segment, offset);
}

// Writes a byte at a given segment and offset
void MemoryWriteByte( uint8_t *memory, uint16_t segment, uint16_t offset, uint8_t value ) {
    uint8_t *memoryPtr = MemoryGet(memory, segment, offset);
    *memoryPtr = value;
}

// Writes a word at a given segment and offset
void MemoryWriteWord( uint8_t *memory, uint16_t segment, uint16_t offset, uint16_t value ) {
    uint16_t *memoryPtr = (uint16_t*)MemoryGet(memory, segment, offset);
    *memoryPtr = value;
}

// Frees all the memory from the heap
void MemoryFree( uint8_t *memory ) {
    free(memory);
}

#endif