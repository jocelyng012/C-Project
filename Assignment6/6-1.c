#include <stdio.h>
#include <stdlib.h>

// long f(long a, long b, long c, long d, long n) {
//   long result = 0;
//   for (long i = 0; i < n; i += 2) {
//     for (long j = 0; j < n; j += 2) {
//       result += a * b + i * c * d + j; 
//     }
//   }
//   return result;
// }

long f(long a, long b, long c, long d, long n) {
  long result = 0;
  long ab = a * b; // precompute a * b
  long cd = c * d; // precompute c * d
  long icd = 0; // precompute i * cd
    for (long i = 0; i < n; i += 2) {
        icd += cd; 
        for (long j = 0; j < n; j += 2) {
            result += ab + icd + j; // replace ab and icd 
        }
    }
    return result;
}


int main(int argc, char *argv[]) {
  if (argc == 6) {
    long a = strtol(argv[1], NULL, 10);
    long b = strtol(argv[2], NULL, 10);
    long c = strtol(argv[3], NULL, 10);
    long d = strtol(argv[4], NULL, 10);
    long e = strtol(argv[5], NULL, 10);
    printf("f(%ld, %ld, %ld, %ld, %ld): %ld\n", a, b, c, d, e, f(a, b, c, d, e));
  } else {
    // canvas test cases
    printf("f(1, 2, 3, 4, 5): %ld\n", f(1, 2, 3, 4, 5));
    printf("f(2, 3, 4, 5, 6): %ld\n", f(2, 3, 4, 5, 6));
    printf("f(6, 5, 4, 3, 2): %ld\n", f(6, 5, 4, 3, 2));
    printf("f(5, 4, 3, 2, 1): %ld\n", f(5, 4, 3, 2, 1));
  }
  return 0;
}