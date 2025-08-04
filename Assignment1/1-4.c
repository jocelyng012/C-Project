#include <stdio.h>
#include <stdlib.h>

void printBytes(unsigned char *start, int len) {
    for (int i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}
// inputs: a char pointer(memory address?) and an int of how many bytes to print
// expected output: list of memory address in hex format (since pointer)
// in the for loop, the stop condition is when i = or > len, which is how long of bytes need to print, for each value (accessing point using index) it prints in a hex format

void printInt(int x) {
    printBytes((unsigned char *) &x, sizeof(int));
}
// this function prints the byte representation of an integer
// the output for 2 is 02 00 00 00
// this function take the address of int x into a pointer (to function printbytes), and take the size of int - 4 (to function printbytes)
// accroding to textbook ch2 p42, the ouput print in little endian
// so the output (using printbytes & printint) print the hex format of 4 bytes/32 bits in little endian for bytes ordering

void printFloat(float x) {
    printBytes((unsigned char *) &x, sizeof(float));
}
// this function prints the byte representation of a float, same as printInt but in a float version
// float in C usually stored in IEEE  754 format; source: chatgpt
// take the address of float x into a pointer (to function printbytes), and take the size of float - 4 (to function printbytes)

int main (int argc, char *argv[])
{
	// test case for printInt
	int x1 = 2;
	printInt(x1);

	int x2 = 506789;
	printInt(x2);

    // test case for printFloat
    float x3 = 0.375;
	printFloat(x3);

	float x4 = 674.9;
	printFloat(x4);

	return 0;
}
