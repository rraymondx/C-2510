#include <stdio.h>
#include <stdlib.h>

// Student Number: A01343016

unsigned int reversedArr; // Global variable to hold the modified value of arr

void reverseIntBits(unsigned int arr, int start, int end);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL) {
        return 1;
    }

    unsigned int arr;
    int start, end;
    char dummy;

    // Read input values
    if (fscanf(inputFile, "%u %d %d %c", &arr, &start, &end, &dummy) != 4) {
        return 1;
    }

    // Call function to reverse bits
    reverseIntBits(arr, start, end);

    // Write result to output file
    fprintf(outputFile, "%u\n", reversedArr);

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

void reverseIntBits(unsigned int arr, int start, int end) {
    unsigned int result = arr;
    // Traverse the range from start to end
    while (start < end) {
        // Extract the bit values at positions start and end
        unsigned int bit1 = (arr >> start) & 1;
        unsigned int bit2 = (arr >> end) & 1;
        // Toggle the bits at positions start and end in the result
        result ^= (-bit1 ^ result) & (1 << end);
        result ^= (-bit2 ^ result) & (1 << start);
        // Move to the next bit positions
        start++;
        end--;
    }
    // Update the global variable with the modified value of arr
    reversedArr = result;
}
