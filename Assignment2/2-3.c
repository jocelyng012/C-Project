#include <stdio.h>
#include <stdlib.h>

int le(float x, float y) {
    unsigned int ux = *((unsigned int*) &x); // convert x raw bits
    unsigned int uy = *((unsigned int*) &y); // convert y raw bits
    unsigned int sx = ux >> 31; // extract sign bit of ux
    unsigned int sy = uy >> 31; // extract sign bit of uy   
    ux &= 0x7FFFFFFF; // drop sign bit of ux
    uy &= 0x7FFFFFFF; // drop sign bit of uy
    // TODO: return using sx, sy, ux, uy (but not x or y)
    // use || to connect all the conditions
    // relationship flips comes to negative since signed

    return (sx == sy &&  // if they have the same sign
           ((sx == 0 && ux <= uy)) || // both postive but x <= y
           ((sx == 1 && ux >= uy)) || // both negative but x >= y
           ((ux == 0 && uy == 0))) || // both -0.0 or 0.0 
           (sx > sy); //x is negative, y is positive (x <= y)
} 


int main(int argc, char *argv[]) {
  if (argc == 3) {
    float x = strtof(argv[1], NULL);
    float y = strtof(argv[2], NULL);
    printf("le(%f, %f): %d\n", x, y, le(x, y));
  } else {
    // canvas test cases
    printf("le(0.0f, 0.0f): %d\n", le(0.0f, 0.0f));
    printf("le(-0.0f, 0.0f): %d\n", le(-0.0f, 0.0f));
    printf("le(0.0f, -0.0f): %d\n", le(0.0f, -0.0f));
    printf("le(-0.0f, -0.0f): %d\n", le(-0.0f, -0.0f));
    printf("le(1.0f, 1.0f): %d\n", le(1.0f, 1.0f));
    printf("le(-1.0f, 1.0f): %d\n", le(-1.0f, 1.0f));
    printf("le(1.0f, -1.0f): %d\n", le(1.0f, -1.0f));
    printf("le(-1.0f, -1.0f): %d\n", le(-1.0f, -1.0f));
    printf("le(-1.0f, 0.0f): %d\n", le(-1.0f, 0.0f));
    printf("le(0.0f, -1.0f): %d\n", le(0.0f, -1.0f));
    printf("le(1.0f, 0.0f): %d\n", le(1.0f, 0.0f));
    printf("le(0.0f, 1.0f): %d\n", le(0.0f, 1.0f));
    printf("le(1.0f, 2.0f): %d\n", le(1.0f, 2.0f));
    printf("le(2.0f, 1.0f): %d\n", le(2.0f, 1.0f));
    printf("le(-1.0f, -2.0f): %d\n", le(-1.0f, -2.0f));
    printf("le(-2.0f, -1.0f): %d\n", le(-2.0f, -1.0f));
  }
  return 0;
}