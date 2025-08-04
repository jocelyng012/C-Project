#include <stdio.h>
#include <stdlib.h>

long iterativeFact(long x){
  long result = 1; // 0! = 1 if result = 0, and use to update the result from last iteration
  for (long i = x; i > 0; --i) { //loop: start from x and go down to 1
    result *= i; // using result * with the current reuslt and update/store the result
  }
  return result; //return the final result
}

long recursiveFact(long x){
  if (x == 0) { //base case of the recursive function: 0! = 1
    return 1; // return base case
  }
  return x * recursiveFact(x - 1); //recursive call start from the x and go to the x-1 function; x! = x * (x-1)! and return the result
}


int main(int argc, char *argv[]) {
  if (argc == 2) {
    long x = strtol(argv[1], NULL, 10);
    printf("iterativeFact(%ld): %ld\n", x, iterativeFact(x));
    printf("recursiveFact(%ld): %ld\n", x, recursiveFact(x));
  } else {
    // canvas test cases
    printf("iterativeFact(0): %ld\n", iterativeFact(0));
    printf("recursiveFact(0): %ld\n", recursiveFact(0));
    printf("iterativeFact(1): %ld\n", iterativeFact(1));
    printf("recursiveFact(1): %ld\n", recursiveFact(1));
    printf("iterativeFact(5): %ld\n", iterativeFact(5));
    printf("recursiveFact(5): %ld\n", recursiveFact(5));
  }
  return 0;
}