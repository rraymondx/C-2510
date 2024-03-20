#include <stdio.h>

// Student Number: A01343016

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
} listNode;

FILE *input, *output;

int main(int argc, char* argv[]){

    // Check if correct number of arguments provided
    if(argc != 3) {
        printf("Usage: %s input output\n", argv[0]);
        return 1;
    }

    // Open input and output file
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    // checks if input or output is null
    if (input == NULL || output == NULL) {
        return 1;
    }

    // creates node, and ensures that both head and the student data start as null
    listNode *head = malloc(sizeof(listNode));
    head -> std = NULL;
    head -> next = NULL;



    fclose(input);
    fclose(output);
    
    return 0;
}



// ensures that grades are within the range provided. //
int checkGrade(int grade) {
    if(!(grade >= 0 && grade <= 100)) {
        return 0;
    } else {
        return 1;
    }
}

// checks if the A number starts with A number. //
int checkSTD(char *stdNum) {

    // base case of null
    if(stdNum == NULL) {
        return 0;
    }

    int position = 0;
    int size = 0;

    // loops as long as it does not hit a null terminator
    while(*(stdNum + position) != '\0') {
        // if it starts with A
        if(position == 0 && *(stdNum + position) != 'A') {
            return 0;
        } else if(position != 0 && !(*(stdNum + position) >= '0' && *(stdNum + position) <= '9')) {
            return 0;
        }

        size++;
        position++;
    }

    if(size == 8) {
        return 1;
    } else {
        return 0;
    }
}

