#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// source: 7-1.c & chatgpt

struct ColorPoint {
    long a;
    long r;
    long g;
    long b;
};

void f(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[i][j].a;
            sum += points[i][j].r;
            sum += points[i][j].g;
            sum += points[i][j].b;
        }
    }
    *dest = sum;
}

// block = 2^6 = 64, so offset = 6 bits, the rest is the tag

// points[0][0].a: Address 0: 0x00 = 0000 0000, Tag: 000000, Offset: 000000 - miss
// points[0][0].r: Address 8: 0x08 = 0000 0000 1000, Tag: 000000, Offset: 001000 - hit
// points[0][0].g: Address 16: 0x10 = 0000 0001 0000, Tag: 000000, Offset: 010000 - hit
// points[0][0].b: Address 24: 0x18 = 0000 0001 1000, Tag: 000000, Offset: 011000 - hit
// points[0][1].a: Address 32: 0x20 = 0000 0010 0000, Tag: 000000, Offset: 100000 - hit
// points[0][1].r: Address 40: 0x28 = 0000 0010 1000, Tag: 000000, Offset: 101000 - hit
// points[0][1].g: Address 48: 0x30 = 0000 0011 0000, Tag: 000000, Offset: 110000 - hit
// points[0][1].b: Address 56: 0x38 = 0000 0011 1000, Tag: 000000, Offset: 111000 - hit

// since the block size is 64, it can hold two structs (32*2) at a time
// so at points[0][0] is cold miss: the cache is empty
// then holds points[0][0] & points[0][1] (8-56) - 64 bytes
// when it reaches to points[0][2], it will be miss
// the pattern throughout execution of the procedure will be after two structs it will be a miss




void g(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[j][i].a;
            sum += points[j][i].r;
            sum += points[j][i].g;
            sum += points[j][i].b;
        }
    }
    *dest = sum;
}

// points[0][0].a: Address 0: 0x00 = 0000 0000, Tag: 000000, Offset: 000000 - miss
// points[0][0].r: Address 8: 0x08 = 0000 0000 1000, Tag: 000000, Offset: 001000 - hit
// points[0][0].g: Address 16: 0x10 = 0000 0001 0000, Tag: 000000, Offset: 010000 - hit
// points[0][0].b: Address 24: 0x18 = 0000 0001 1000, Tag: 000000, Offset: 011000 - hit
// points[1][0].a: Address 4*32 = 128: 0x80 = 0000 1000 0000, Tag: 000010, Offset: 000000 - miss
// points[1][0].r: Address 4*32+8 = 136: 0x88 = 0000 1000 1000, Tag: 000010, Offset: 001000 - hit
// points[1][0].g: Address 4*32+16 = 144: 0x90 = 0000 1001 0000, Tag: 000010, Offset: 010000 - hit
// points[1][0].b: Address 4*32+24 = 152: 0x98 = 0000 1001 1000, Tag: 000010, Offset: 011000 - hit

// since the block size is 64, it can hold two structs (32*2) at a time
// so at points[0][0] is cold miss: the cache is empty
// but when it goes to points[1][0], it will be miss since access a new block
// the pattern throughout execution of the procedure will be after one struct it will be a miss (column order)


struct ColorPoint** create2DArray(int n) {
    // Array to hold a pointer to the beginning of each row
    struct ColorPoint **points = (struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
    for (int i = 0; i < n; ++i) {
        // Array to hold each row
        points[i] = (struct ColorPoint *)malloc(n * sizeof(struct ColorPoint));
        for (int j = 0; j < n; ++j) {
            // Init the ColorPoint struct
            points[i][j].a = rand();
            points[i][j].r = rand();
            points[i][j].g = rand();
            points[i][j].b = rand();
        }
    }
    return points;
}

void free2DArray(struct ColorPoint** points, int n) {
    for (int i = 0; i < n; ++i) {
        free(points[i]);
    }
    free(points);
}


int main(){
    int n = 2048; // set size of the array
    int times = 100; // number of times
    struct ColorPoint **points = create2DArray(n); // create the array
    long dest = 0; long dest1 = 0; // destination variable

    clock_t startf = clock(); // start time for f
    for (int i = 0; i < times; i++) { // run f 100 times
        f(points, n, &dest);
    }
    clock_t endf = clock(); // end time for f
    double timef = (double)(endf - startf) / CLOCKS_PER_SEC; // time for f
    printf("f: %f seconds\n", timef); // print time for f

    clock_t startg = clock(); // start time for g
    for (int i = 0; i < times; i++) { // run g 100 times
        g(points, n, &dest1);
    }
    clock_t endg = clock(); // end time for g
    double timeg = (double)(endg - startg) / CLOCKS_PER_SEC; // time for g
    printf("g: %f seconds\n", timeg); // print time for g

    free2DArray(points, n); // free the array

    return 0;
}


// result
// f: 1.439901 seconds
// g: 7.040020 seconds

// f is faster than g since f is row major order - more friendly to cache
// g is column major order - less friendly to cache
