#include "Core.h"

int main() {
    CPU cpu;
    cpu.a.l = 12;
    cpu.a.h = 15;
    printf("%02X\n", cpu.a.x);
    return 0;
}