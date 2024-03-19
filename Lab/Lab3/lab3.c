#include <stdio.h>
#include <stdlib.h>

// Student Number: A01343016

void encrypt_text(char *input, char *output, int shift);

int main(int argc, char *argv[]) {

    // takes args from command-line
    char *input = argv[1];
    char *output = argv[2];
    // atoi used for converting str args to an int 
    int numShift = atoi(argv[3]);

    encrypt_text(input, output, numShift);

}

void encrypt_text(char *input, char *output, int shift) {
    
    FILE *fptrIn, *fptrOut;
    char c;

    // checks for input file to read from
    fptrIn = fopen(input, "r"); 
    if (fptrIn == NULL) {
        printf("Cannot open the input file");
        return;
    }

    // checks for output file to write in
    fptrOut = fopen(output, "w");
    if (fptrOut == NULL) {
        printf("Cannot create the output file");
        return;
    }

    // loops throught the input and grabs characters and shifts
    c = fgetc(fptrIn);
    while (c != EOF) {

        // basic shifting 
        if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + shift) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + shift) % 26;
        }

        // puts the cyphered charcter into output file
        fputc(c, fptrOut);
        // get next character
        c = fgetc(fptrIn);
    }

    // closes stream/scan thingy
    fclose(fptrIn);
    fclose(fptrOut);
    
}
