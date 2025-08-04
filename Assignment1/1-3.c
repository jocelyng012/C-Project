#include <stdio.h>
#include <stdlib.h>

int oddBit(unsigned int x){
  unsigned int mask = 0xAAAAAAAA; // extract odd index since A = 1010; source: chatgpt
  return (x & mask) != 0; // isolates only odd bits of x then return 1 if x & mask is nonzero, means at least 1 odd bits in x, otherwise it would be 0
}


int main(int argc, char *argv[]) {
  if (argc == 2) {
    unsigned int x = strtoul(argv[1], NULL, 16);
    printf("oddBit(0x%X): %d\n", x, oddBit(x));
  } else {
    // test case from canvas
    printf("oddBit(0x1): %d\n", oddBit(0x1));
    printf("oddBit(0x2): %d\n", oddBit(0x2));
    printf("oddBit(0x3): %d\n", oddBit(0x3));
    printf("oddBit(0x4): %d\n", oddBit(0x4));
    printf("oddBit(0xFFFFFFFF): %d\n", oddBit(0xFFFFFFFF));
    printf("oddBit(0xAAAAAAAA): %d\n", oddBit(0xAAAAAAAA));
    printf("oddBit(0x55555555): %d\n", oddBit(0x55555555));
  }
  return 0;
}