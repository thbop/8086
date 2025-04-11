#include "Core.h"

int main() {
    CPU cpu;
    cpu.flags.AF = 1;
    printf("%02X\n", cpu.flags.value);
    return 0;
}