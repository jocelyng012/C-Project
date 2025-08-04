#include <stdio.h>
#include <stdlib.h>

unsigned int combine(unsigned int x, unsigned int y){
	unsigned int byte3to1 = x & 0xFFFFFF00; //extract byte3 to byte1 from x by masking
	unsigned int byte0 = y & 0x000000FF; //extract byte0 from y by masking

	return byte3to1 | byte0; //use or op to combine 
}

int main(int argc, char *argv[]) {
  if (argc == 3) {
    unsigned int x = strtoul(argv[1], NULL, 16);
    unsigned int y = strtoul(argv[2], NULL, 16);
    printf("combine(0x%X, 0x%X): 0x%X\n", x, y, combine(x, y));
  } else {
    unsigned int x1 = 0x12345678; //added test case that in canvas question
    unsigned int y1 = 0xABCDEF00;
    printf("combine(0x%X, 0x%X): 0x%X\n", x1, y1, combine(x1,y1));

    unsigned int x2 = 0xABCDEF00; // second test case that also in canvas
    unsigned int y2 = 0x12345678;
    printf("combine(0x%X, 0X%X):0x%X\n", x2, y2, combine(x2,y2));
  }
  return 0;
}


// unsigned int combine(unsigned int x){
//   return x >> 16;
// }

// int main() {
//     unsigned int x = 0x12345678;
//     printf("combine(0x%X): 0x%X\n", x, combine(x));
// }