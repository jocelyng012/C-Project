#include <stdio.h>
#include <stdlib.h>

// f(long, long, long): 
//         imulq   %rdx, %rdi // x = x * z
//         subq    %rsi, %rdx // z = z - y
//         movq    %rdi, %rax // %rax = x
//         andq    %rdx, %rax // return x & z
//         ret

// use godbolt for checking

long f(long x, long y, long z){
    x *= z; // x = x * z
    z -= y; // z = z - y
    return x & z; // return x(%rax) & z
}


int main(int argc, char *argv[]) {
  if (argc == 4) {
    long x = strtol(argv[1], NULL, 10);
    long y = strtol(argv[2], NULL, 10);
    long z = strtol(argv[3], NULL, 10);
    printf("f(%ld, %ld, %ld): %ld\n", x, y, z, f(x, y, z));
  } else {
    // canvas test cases
    printf("f(1, 2, 4): %ld\n", f(1, 2, 4));
    printf("f(3, 5, 7): %ld\n", f(3, 5, 7));
    printf("f(10, 20, 40): %ld\n", f(10, 20, 40));
    printf("f(30, 50, 70): %ld\n", f(30, 50, 70));
    printf("f(30, 50, -70): %ld\n", f(30, 50, -70));
  }
  return 0;
}