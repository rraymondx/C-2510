#include <stdio.h>
#include <stdlib.h>

// Student ID: A01343016

// Function to perform synthetic saturating multiplication
void multiply(int bitwidth, int a, int b, FILE *output_file) {
    // Calculate the result of multiplication
    int result = a * b;
    // Calculate the maximum value representable with given bitwidth
    int max_val = (1 << (bitwidth - 1)) - 1;
    // Calculate the minimum value representable with given bitwidth
    int min_val = ~max_val;

    // Detect signs of input and result to check for overflow and underflow
    int a_sign = (a >> (bitwidth - 1)) & 1;
    int b_sign = (b >> (bitwidth - 1)) & 1;
    int result_sign = (result >> (bitwidth - 1)) & 1;

    // Check for overflow condition
    int overflow = (a_sign == b_sign && result_sign != a_sign);
    // Check for underflow condition
    int underflow = (a_sign != b_sign && result_sign != a_sign);

    // Write the result to the output file, considering overflow and underflow
    if (overflow) {
        fprintf(output_file, "%d\n", max_val);
    } else if (underflow) {
        fprintf(output_file, "%d\n", min_val);
    } else {
        fprintf(output_file, "%d\n", result);
    }
}

int main(int argc, char *argv[]) {
    // Check if correct number of arguments provided
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    // Open output file
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        printf("Error: Unable to open output file.\n");
        fclose(input_file);
        return 1;
    }

    int bitwidth;
    int a, b;

    // Read bitwidth from input file
    fscanf(input_file, "%d", &bitwidth);
    
    // Check if there are no more pairs of integers to multiply
    if (fscanf(input_file, "%d %d", &a, &b) == 0) {
        // Write min and max values to output file
        fprintf(output_file, "min: %lld\t0x%016llx\n", -((1LL << (bitwidth - 1)) - 1) - 1, (long long) -((1LL << (bitwidth - 1)) - 1) - 1);
        fprintf(output_file, "max: %lld\t0x%016llx\n", (1LL << (bitwidth - 1)) - 1, (long long) (1LL << (bitwidth - 1)) - 1);
    } else {
        // Loop through pairs of integers to perform multiplication
        fseek(input_file, 1, SEEK_SET);
        while (fscanf(input_file, "%d %d", &a, &b) == 2) {
            multiply(bitwidth, a, b, output_file);
            fclose(input_file);
            fclose(output_file);
            return 0;
        }
    }

    return 0;
}
