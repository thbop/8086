#ifndef STORAGE_H
#define STORAGE_H

#define STORAGE_SECTOR_SIZE 512

// Load a variable number of sectors into memory
// This does not load into emulated memory, but
// allocates its own buffer
uint8_t *StorageLoadSectors( const char *filename, uint16_t lba, uint16_t sectorCount ) {
    FILE *fp = fopen(filename, "rb");

    // Get file size and check if it is large enough to read
    // the requested sectors
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    if ( fileSize < ( lba + sectorCount ) * STORAGE_SECTOR_SIZE ) {
        fprintf(
            stderr,
            "\"%s\" does not contain %d sectors starting from LBA %02X!\n"
            "File not big enough!\n",
            filename, sectorCount, lba
        );
        fclose(fp);
        return NULL;
    }

    // Allocate a buffer for the sectors and read the data in
    uint8_t *buffer = (uint8_t*)malloc(sectorCount * STORAGE_SECTOR_SIZE);
    if ( buffer == NULL ) {
        fprintf(stderr, "Failed to allocate file buffer!\n");
        fclose(fp);
        return NULL;
    }

    // Read data and return buffer
    fseek(fp, lba * STORAGE_SECTOR_SIZE, SEEK_SET);
    fread(buffer, 1, sectorCount * STORAGE_SECTOR_SIZE, fp);

    fclose(fp);

    return buffer;
}

// Copies data from a fileBuffer into a specific segment of memory
void StorageLoad( uint8_t *fileBuffer, uint16_t sectorCount, uint8_t *memory, int16_t segment ) {
    size_t fileBufferSize = sectorCount * STORAGE_SECTOR_SIZE;
    uint32_t address = segment << 4;

    if ( fileBufferSize + address > MEMORY_MAX_SIZE ) {
        fprintf(
            stderr,
            "Cannot load %d sectors into memory segment %s! Too large!\n",
            sectorCount, segment
        );
        return;
    }


    memcpy(memory + address, fileBuffer, fileBufferSize);
}

#endif