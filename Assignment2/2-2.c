#include <stdio.h>
#include <stdlib.h>

unsigned int extract (unsigned int x, int i){
  int byte = x >> (i << 3); // let the extract value shift to the least significant, then extract: shift back to then last position 
  int signed_byte = ((byte << 24) >> 24); // perform sign extension using arithmetic right shift: first left shift to the least significant, then sign extened by shift right (source: google)
  return signed_byte; // return signed bytes
}


int main(int argc, char *argv[]) {
  if (argc == 3) {
    unsigned int x = strtoul(argv[1], NULL, 16);
    int i = strtol(argv[2], NULL, 10);
    printf("extract(0x%X, %d): 0x%08X\n", x, i, extract(x, i));
  } else {
    // canvas test cases
    printf("extract(0x12345678, 0): 0x%08X\n", extract(0x12345678, 0));
    printf("extract(0xF2345678, 0): 0x%08X\n", extract(0xF2345678, 0));
    printf("extract(0xABCDEF00, 2): 0x%08X\n", extract(0xABCDEF00, 2));
    printf("extract(0x0BCDEF00, 2): 0x%08X\n", extract(0x0BCDEF00, 2));
  }
  return 0;
}