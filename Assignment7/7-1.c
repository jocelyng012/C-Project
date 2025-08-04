#include <stdio.h>
#include <stdlib.h>

unsigned int getOffset(unsigned int address){
    return address & 0x0000000F; // extract the last 4 bits of the address
}

unsigned int getTag(unsigned int address){
    return address >> 4; // remove the last digit
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        unsigned int a = strtoul(argv[1], NULL, 16);
        unsigned int o = getOffset(a);
        unsigned int t = getTag(a);
        printf("%x: offset: %x - tag: %x\n", a, o, t);
    } else {
        // canvas test cases
        printf("0x12345678: offset: %x - tag: %x\n", getOffset(0x12345678), getTag(0x12345678));
        printf("0x87654321: offset: %x - tag: %x\n", getOffset(0x87654321), getTag(0x87654321));
    }
}

