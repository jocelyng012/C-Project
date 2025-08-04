#include <stdio.h>
#include <stdlib.h>

unsigned int replace(unsigned int x, int i, unsigned char b){
	unsigned int masked_x = (~(0xFF << (i * 8))) & x; //first find the replace location by shift the index i by 8, then find the complement of the mask to keep the byte info other than the replace location, finally extract that location from x uxing the mask
	unsigned int shifted_b = (unsigned int)b << (i * 8); //shift the index i by 8 as i required location
	
	return masked_x | shifted_b; //use or to combine two steps above
}

int main(int argc, char *argv[]) {
  if (argc == 4) {
    unsigned int x = strtoul(argv[1], NULL, 16);
    int i = strtol(argv[2], NULL, 10);
    unsigned char b = (unsigned char)strtoul(argv[3], NULL, 16);
    printf("replace(0x%X, %d, 0x%X): 0x%X\n", x, i, b, replace(x, i, b));
  } else {
    unsigned int x1 = 0x12345678; // canvas test cases: total 4
    int i1 = 3;
    unsigned char b1 = 0xAB;
    printf("replace(0x%08X, %d, 0x%02X): 0x%08X\n", x1, i1, b1, replace(x1, i1, b1));

    unsigned int x2 = 0x12345678;
    int i2 = 2;
    unsigned char b2 = 0xAB;
    printf("replace(0x%08X, %d, 0x%02X): 0x%08X\n", x2, i2, b2, replace(x2, i2, b2));

    unsigned int x3 = 0x12345678;
    int i3 = 1;
    unsigned char b3 = 0xAB;
    printf("replace(0x%08X, %d, 0x%02X): 0x%08X\n", x3, i3, b3, replace(x3, i3, b3));

    unsigned int x4 = 0x12345678;
    int i4 = 0;
    unsigned char b4 = 0xAB;
    printf("replace(0x%08X, %d, 0x%02X): 0x%08X\n", x4, i4, b4, replace(x4, i4, b4));

  }
  return 0;
}
