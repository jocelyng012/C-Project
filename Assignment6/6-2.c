#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inner(float *u, float *v, int length, float *dest) {
  float sum = 0.0f;
  for (int i = 0; i < length; ++i) {
    sum += u[i] * v[i];
  }
  *dest = sum;
}


// source: lab6
void inner2(float *u, float *v, int length, float *dest) {

  // intialize four partial sums and i
  float sum = 0.0f;
  float sum1 = 0.0f;
  float sum2 = 0.0f;
  float sum3 = 0.0f;
  int i;

  // unroll the loop by 4, 4 elements at a time
  for (i = 0; i < length - 3; i += 4) {
    sum += u[i] * v[i];
    sum1 += u[i + 1] * v[i + 1];
    sum2 += u[i + 2] * v[i + 2];
    sum3 += u[i + 3] * v[i + 3];
  }

  // process remaining elements
  for (; i < length; ++i) {
    sum += u[i] * v[i];
  }
  *dest = sum + sum1 + sum2 + sum3; // combine all the partial sums
}


// source: lab6
void inner3(float *u, float *v, int length, float *dest) {

  // intialize eight partial sums and i
  float sum = 0.0f;
  float sum1 = 0.0f;
  float sum2 = 0.0f;
  float sum3 = 0.0f;
  float sum4 = 0.0f;
  float sum5 = 0.0f;
  float sum6 = 0.0f;
  float sum7 = 0.0f;
  int i;

  // unroll the loop by 8, 8 elements at a time
  for (i = 0; i < length - 3; i += 4) {
    sum += u[i] * v[i];
    sum1 += u[i + 1] * v[i + 1];
    sum2 += u[i + 2] * v[i + 2];
    sum3 += u[i + 3] * v[i + 3];
    sum4 += u[i + 4] * v[i + 4];
    sum5 += u[i + 5] * v[i + 5];
    sum6 += u[i + 6] * v[i + 6];
    sum7 += u[i + 7] * v[i + 7];
  }

  // process remaining elements
  for (; i < length; ++i) {
    sum += u[i] * v[i];
  }
  *dest = sum + sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7; // combine all the partial sums
}

// copy from canvas
float *createArray(int length) {
  float *a = (float *)malloc(length * sizeof(float));
  for (int i = 0; i < length; ++i) {
    a[i] = rand()/(float)RAND_MAX;
  }
  return a;
}

// source: lecture code 2-24-optimizations.c (copy clock part)
int main(){
    int length = 100000;
    int calltime = 10000;

    float *u = createArray(length); // create two arrays of length 100,000
    float *v = createArray(length);

    float dest; float dest1; float dest2; // destination

    // inner
    clock_t start = clock(); // start the clock
    // run the inner function 10,000 times
    for (int i = 0; i < calltime; ++i) {
        inner(u, v, length, &dest); 
    }
    clock_t end = clock();
    printf("Execution time(inner): %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);


    // inner2
    clock_t start2 = clock(); // start the clock
    // run the inner2 function 10000 times
    for (int i = 0; i < calltime; ++i) {
        inner2(u, v, length, &dest1); 
    }
    clock_t end2 = clock();
    printf("Execution time(inner2): %f seconds\n", ((double) (end2 - start2)) / CLOCKS_PER_SEC);


    // inner3
    clock_t start3 = clock(); // start the clock
    // run the inner3 function 10000 times
    for (int i = 0; i < calltime; ++i) {
        inner3(u, v, length, &dest2); 
    }
    clock_t end3 = clock();
    printf("Execution time(inner3): %f seconds\n", ((double) (end3 - start3)) / CLOCKS_PER_SEC);


    // free the arrays
    free(u);
    free(v);

    return 0;
}


// Collect several execution times each for inner, inner2, and inner3.  Summarize your findings and argue 
// for which procedure is most efficient based on execution times and your learnings around loop unrolling.  
// Do you notice any limiting factors with inner3?  Any intuition regarding why that might be?  Answer in a
// comment for your inner procedure.

// result:
// Execution time(inner): 3.507781 seconds
// Execution time(inner2): 0.976395 seconds
// Execution time(inner3): 1.708361 seconds

// By the intuition, the execution time of inner3 should be the fastest compare to inner and inner2
// since inner3 process 8 elements at a time (8 accumulators), reduce the number of loop iterations,
// but the result is not as expected.

// But from the result, inner2 is the fastest and inner3 is the second fastest, while the inner is the
// slowest. That because CPUs have a limited number of registers, so when the number of accumulators 
// increase, the CPU takes more time to load the data from memory to the register, which is slower. 
// (diminshing return)

// So the ineer2 is the faster in this case(shorter execution time). 