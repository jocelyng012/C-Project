#include <stdio.h>
#include <stdlib.h>


void transpose(long a[4][4]) {
  for (long i = 0; i < 4; ++i) {
    for (long j = 0; j < i; ++j) {
      long t1 = a[i][j];
      long t2 = a[j][i];
      a[i][j] = t2;
      a[j][i] = t1;
    }
  } 
}


// .L3:
//         movq    (%rax), %rcx //put row pointer into %rcx
//         movq    (%rdx), %rsi //put column pointer into %rsi
//         movq    %rsi, (%rax) //store column pointer into row pointer
//         movq    %rcx, (%rdx) //store row pointer into acolumn pointer
//         addq    $8, %rax //increment %rax by 8
//         addq    $32, %rdx //increment %rdx by 32


void transposeOpt(long a[4][4]) {
  for (long i = 0; i < 4; ++i) {
    long *rp = &a[i][0];
    long *cp = &a[0][i];
    for (long j = 0; j < i; ++j) {
        long t1 = *rp; //t1 = pointer %rax
        long t2 = *cp; //t2 = pointer %rdx
        *rp = t2; //pointer %rax = t2
        *cp = t1; //pointer %rdx = t1
        rp++; //move to the next element in the same row; Chatgpt help explain why this is $8 (8 bytes per long)
        cp += 4; //move to the next element in the same column; Chatgpt help explain why this is $32 (32 bytes per row, 4 elements per row)
    }
  }
}

void print(long a[4][4]) {
  for (int i = 0; i < 4; ++i) {
    for (int j =  0; j < 4; ++j) {
      printf("%ld ", a[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc == 17) {
    long a[4][4];
    long b[4][4];
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        a[i][j] = strtol(argv[i * 4 + j + 1], NULL, 10);
        b[i][j] = a[i][j];
      }
    }
    transpose(a);
    printf("transpose(a)\n");
    print(a);
    transposeOpt(b);
    printf("trasnposeOpt(b)\n");
    print(b);
  } else {
    // canva test cases
    long a_1[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    long b_1[4][4];
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        b_1[i][j] = a_1[i][j];
      }
    }
    transpose(a_1);
    printf("transpose(a_1)\n");
    print(a_1);
    transposeOpt(b_1);
    printf("trasnposeOpt(b_1)\n");
    print(b_1); //both functions have the same output after testing
  }
  return 0;
}