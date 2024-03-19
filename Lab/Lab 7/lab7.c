#include <stdio.h>

// struct to store students info
typedef struct{
    char *lastName;
    char *firstName;
    char *stdNum;
    int midtermGrade;
    int finalGrade;
    int avgGrade;
} student;

typedef struct {
    struct student *std;
    struct ListNode *next;
} ListNode;

int main(int argc, char* argv[]){

    // Check if correct number of arguments provided
    FILE *input, *output;
    if(argc != 3) {
        printf("Usage: %s input output\n", argv[0]);
        return 1;
    }

    // Open input file
    input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Error: Unable to open input file.\n");
        fclose(input);
        return 1;
    }

    // Open output file
    output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Error: Unable to open output file.\n");
        fclose(input);
        return 1;
    }

    int charCount = 0;

    char c = getc(input);

    while((c != '\n') && (c != EOF)) {
        charCount++;
        printf("%d\n", charCount);
        c = getc(input);
    }
    // charCount -= 2;

    printf("%d", charCount);

    fclose(input);
    fclose(output);
    return 0;
}