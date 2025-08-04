#include <stdio.h>
#include <stdlib.h>

struct Set {
    unsigned int tag; // Assume tag is at most 32 bits
    unsigned char valid; // valid bit (0 or 1)
};

struct Cache {
    struct Set *sets;
    int numSets;
};

unsigned int getSet(unsigned int address) {
    return (address >> 1) & 0x7; // 2-byte blocks; 8 sets so 3 set bits
}

unsigned int getTag(unsigned int address) {
    return address >> 4; // total of 4 bits for offset and set
}

struct Cache* mallocCache(int numSets) {
    // TODO - malloc a pointer to a struct Cache, malloc a pointer to an array
    // of struct Set instances (array length is numSets).  Also initialize
    // valid to 0 for each struct Set.  Return the struct Cache pointer.

    struct Cache *cache = (struct Cache *)malloc(sizeof(struct Cache)); // allocate memory for structure of cache
    cache -> numSets = numSets; // set the number of sets in the cache
    cache -> sets = (struct Set *)malloc(numSets * sizeof(struct Set)); // allocate memory for the array of sets

    for (int i = 0; i < numSets; i++) {
        cache -> sets[i].valid = 0; // initialize valid bit to 0
    }

    return cache;

}

void freeCache(struct Cache *cache) {
    free(cache->sets);
    free(cache);
}

void printSet(struct Set *set, int setIndex) {
    printf("set: %x - tag: %x - valid: %u\n", setIndex, set->tag, set->valid);
}

void printCache(struct Cache *cache) {
    // TODO - print all valid sets in the cache by calling printSet() as
    // appropriate.
    for (int i = 0; i < cache->numSets; i++) { // loop through all sets in the cache
        if (cache->sets[i].valid) { // print only sets where the valid bit is set to 1
            printSet(&cache->sets[i], i); // print using printSet
        }
    }
}

void readValue(struct Cache *cache, unsigned int address) {
    // TODO - check the cache for a valid set containing the specified address.
    // If found, indicate a hit. If not found, update the set's tag and valid
    // state and indicate either a cold miss or conflict miss as appropriate.
    unsigned int setIndex = getSet(address); // determine the set index
    unsigned int tag = getTag(address); // extract the tag from the address
    struct Set *set = &cache->sets[setIndex]; // get the corresponding set

    printf("looking for set: %x - tag: %x\n", setIndex, tag); // print the set and tag being searched for

    if (set->valid && set->tag == tag) { // check for a hit: valid bit is set and tags match
        printf("hit!\n"); 
    }
    else {
        if (set->valid) {
            printf("Conflict miss!\n"); // conflict miss: valid set but tag mismatch
        }
        else {
            printf("Cold miss!\n"); // cold miss: set is invalid
        }
        set->valid = 1; // set valid bit to 1
        set->tag = tag; // update the tag
    }
}

unsigned int readUnsignedIntFromHex() {
    char buffer[10];
    char *p = NULL;
    unsigned int n;
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        n = strtoul(buffer, &p, 16);
        if (buffer != p) {
            break;
        }
        printf("Invalid input - try again: ");
    }
    return n;
}

int main() {  
    struct Cache *cache = mallocCache(8);

    char buffer[10];
    char c;
    do {
        printf("Enter 'r' for read, 'p' to print, 'q' to quit: ");
        fgets(buffer, sizeof(buffer), stdin);

        c = buffer[0];
        if (c == 'r') {                     
             printf("Enter 32-bit unsigned hex address: ");
             unsigned int a = readUnsignedIntFromHex();
             readValue(cache, a);
        } else if (c == 'p') {
             printCache(cache);
        }
    } while (c != 'q');

    freeCache(cache);
}

// print contents are based on the canvas output
// ask chat for debugging