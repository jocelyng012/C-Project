#include <stdio.h>
#include <stdlib.h>

// loop(long, long): //rdi a //rsi b
//         movq    $-1, %rax //initial value:result = -1
//         jmp     .L2 //jump to the L2 loop condition
// .L3:         
//         movq    %rsi, %rdx //loop body: %rdx = b; i = b: loop variable
//         xorq    %rdi, %rdx //%rdx = b ^ a
//         andq    %rdx, %rax //result = result & %rdx (b ^ a)
//         subq    $1, %rsi //after iteration: decrement: b = b - 1 each iteration
// .L2:
//         testq   %rsi, %rsi //loop condition: check if b > 0 (not zero but still positive)
//         jg      .L3 //jump ig greater if b > 0, jump to .L3
//         ret //return result


long loop(long a, long b) {
  long result = -1;
  for (long i = b; i > 0; --i) {
    result &= (i ^ a); //i ^ a since i = b
  }
  return result;
}


int main(int argc, char *argv[]) {
  if (argc == 3) {
    long a = strtol(argv[1], NULL, 10);
    long b = strtol(argv[2], NULL, 10);
    printf("loop(%ld, %ld): %ld\n", a, b, loop(a, b));
  } else {
    // canva test cases
    printf("loop(10, 1): %ld\n", loop(10, 1));
    printf("loop(30, 2): %ld\n", loop(30, 2));
    printf("loop(50, 3): %ld\n", loop(50, 3));
    printf("loop(70, 4): %ld\n", loop(70, 4));
    printf("loop(90, 5): %ld\n", loop(90, 5));
  }
  return 0;
}