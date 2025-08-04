#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void f(float *a, int length, float *dest) {
  float prod = 1.0f;
  for (int i = 0; i < length; ++i) {
    if (a[i] != 0.0f) {
      prod *= a[i];
    }
  }
  *dest = prod;
}

float *createArray(int length) {
  float *a = (float *)malloc(length * sizeof(float));
  for (int i = 0; i < length; ++i) {
    // 50% chance that a[i] is 0.0f, random value on the range
    // [0.75, 1.25] otherwise.
    float r = rand()/(float)RAND_MAX;
    a[i] = r < 0.5f ? 0.0f : r + 0.26f;
  }
  return a;
}

// g function(function f without zero check)
void g(float *b, int length, float *dest) {
  float prod = 1.0f;
  for (int i = 0; i < length; ++i) {
      prod *= b[i]; // without zero check
}
  *dest = prod;
}

// source: 6-2.c & chatgpt explain ? : (if-else)
int main(){
    // create call time, length, and i
    int length = 10000;
    int calltime = 10000;
    int i;

    // create an array a
    float *a = createArray(length);
    float dest; float dest1; float dest2; // destination
    
    clock_t start = clock(); // start the clock
    for (i = 0; i < calltime; ++i) { // run the function 10000 times
        f(a, 10000, &dest);
    }
    clock_t end = clock();
    printf("Execution time(array a): %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    


    // create an array b, replace 0.0f with 1.0f
    float *b = (float *)malloc(length * sizeof(float)); // allocate memory for array b
    for (i = 0; i < calltime; ++i) {
        b[i] = (a[i] == 0.0f) ? 1.0f : a[i]; // if a[i] is 0.0f, replace it with 1.0f; else b[i] = a[i]
    }

    clock_t start2 = clock(); // start the clock
    for (i = 0; i < 10000; ++i) { // run the function 10000 times
        g(b, 10000, &dest);
    }
    clock_t end2 = clock();
    printf("Execution time(array b): %f seconds\n", ((double) (end2 - start2)) / CLOCKS_PER_SEC);



    // create an array c, only non-zero values
    float *c = (float *)malloc(length * sizeof(float)); // allocate memory for array c
    int j = 0; // define new index so there are no gaps in array c
    for (i = 0; i < length; ++i){
        if (a[i] != 0.0f){ // if a[i] is not 0.0f, add it to array c
            c[j++] = a[i]; // increment j after
        }
    }

    clock_t start3 = clock(); // start the clock
    for (i = 0; i < calltime; ++i) { // run the function 10000 times
        g(c, j, &dest);
    }
    clock_t end3 = clock();
    printf("Execution time(array c): %f seconds\n", ((double) (end3 - start3)) / CLOCKS_PER_SEC);


    // free the arrays
    free(a);
    free(b);
    free(c);

    return 0;
}


// result:
// Execution time(array a): 0.533011 seconds
// Execution time(array b): 0.353716 seconds
// Execution time(array c): 0.174896 seconds


//  Is calling g(b) more efficient than calling f(a) based on your timing data?  
//  Why (or why not) might this be the case?  Answer in a comment for your g procedure.

// Yes, g(b) is more efficient than f(a) since it removes the zero conditional check before the multiplication inside
// the loop. This means that g(b) can skip the check for each element in the array, which saves time and makes the
// loop faster(shorter execution time).



//  Is calling g(c) more efficient than calling g(b) based on your timing data?  
//  Why (or why not) might this be the case?  Answer in a comment for your g procedure.

// Yes, g(c) is more efficient than g(b) since it only contains non-zero values, it contains less elements than g(b),
// less multiplication operations. This makes the loop faster(shorter execution time) and more efficient. 