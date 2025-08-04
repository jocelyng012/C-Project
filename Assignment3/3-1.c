#include <stdio.h>
#include <stdlib.h>

struct IntArray {
    int length;
    int *dataPtr;
};

struct IntArray* mallocIntArray(int length){
    struct IntArray *array = malloc(sizeof(struct IntArray)); //allocate memory for the new struct IntArray
    array->length = length; //initialize for the new struct IntArray
    array->dataPtr = malloc(length*sizeof(int)); //allocate memory for the instance's pointer by how many int it has

    return array; //return a pointer to a new struct IntArray
}

void freeIntArray(struct IntArray *arrayPtr){
    free(arrayPtr->dataPtr); //free the instance's pointer by accessing the struct using ->
    free(arrayPtr); //free the instance
}

void readIntArray(struct IntArray *array){
    char buffer[50]; //stored input
    char *ptr;

    for (int i = 0; i < array->length; i++){

        while (1){ // while True
            printf("Enter int: "); //prompts the user
            fgets(buffer, sizeof(buffer), stdin); //read and store in buffer, source: CS212
            int value = strtol(buffer, &ptr, 10); //convert a str to an int

            if (ptr == buffer || *ptr != '\n' || value <= 0) { //check if the input is vaild
                printf("Invaild input\n");
            }
            else {
                array->dataPtr[i] = value; //store the vaild input in the array
                break;
            } 
        }
    }
}

void swap(int *xp, int *yp){
    int temp = *xp; //store the value of xp in temp
    *xp = *yp; //let xp's value equals to yp's value
    *yp = temp; //set yp's value to the temp(which is xp's value)
}

void sortIntArray(struct IntArray *array){ //source: geeksforgeeks, chatgpt, and CS313
    int n = array->length; //set the length of the array to size n
    for (int i = 0; i < n-1; i++){
        int min_idx = i; //set the first element to the minimum

        for (int j = i+1; j < n; j++){
            if (((array->dataPtr)[j]) < ((array->dataPtr)[min_idx])){
                min_idx = j; //go thru the array, find the smallest element
            }
        }
         if (min_idx != i){ 
            swap(&array->dataPtr[i], &array->dataPtr[min_idx]); //swap the minimum to the first element
        }
    }
}

void printIntArray(struct IntArray *array){
    printf("[ "); //bracket and space
    for (int i = 0; i < array->length; i++) { //loop thru the element in array
        printf("%d", array->dataPtr[i]); //print them by using [] access the value
        if (i < array->length - 1) {
            printf(", "); //add comma for each element expect for the last element
        }
    }
    printf(" ]\n"); //add space, close bracket, and newline
}

int main(){
    //copy part of readintarray for prompts the user
    char buffer[10];
    char *ptr;
    int length;

    while (1){ // while True
        printf("Enter length: "); //prompts the user
        fgets(buffer, sizeof(buffer), stdin); //read and store in buffer, source: CS212
        length = strtol(buffer, &ptr, 10); //convert a str to an int

        if (ptr == buffer || *ptr != '\n' || length <= 0) { //check if the input is vaild
            printf("Invaild input\n");
        }
        else {
            break;
        } 
    }
    struct IntArray *array = mallocIntArray(length); //create an array with the required length
    readIntArray(array);
    sortIntArray(array);
    printIntArray(array);
    freeIntArray(array);

    return 0;
}