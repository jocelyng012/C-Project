#include <stdio.h>
#include <stdlib.h>

unsigned int mask(int n){
    return (0x1 << n) - 1; //use 0x1 to mask 0 for the least-significant n bits, then use - 1 to filps all the 0 to 1, so all 0s in the least-significant n bits becomes 1s now (slide1 p19)
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    int n = strtol(argv[1], NULL, 10);
    printf("mask(%d): 0x%X\n", n, mask(n));
  } else {
    // canvas test cases
    printf("mask(1): 0x%X\n", mask(1));
    printf("mask(2): 0x%X\n", mask(2));
    printf("mask(3): 0x%X\n", mask(3));
    printf("mask(5): 0x%X\n", mask(5));
    printf("mask(8): 0x%X\n", mask(8));
    printf("mask(16): 0x%X\n", mask(16));
    printf("mask(31): 0x%X\n", mask(31));
  }
  return 0;
}