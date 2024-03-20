#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student Number: A01343016

// STRUCT STUDENT. //
typedef struct student{
    char *lastName;
    char *firstName;
    char *stdNum;
    int midtermGrade;
    int finalGrade;
    int avgGrade;
} Student;

// STRUCT LISTNODE. //
typedef struct listNode{
    struct student *std;
    struct listNode *next;
} ListNode;

FILE *input;
FILE *output;

// FUNCTION HEADERS. //
void printErrorExit();
void insertList(ListNode *head, int *option);
void insertSTD(ListNode *head, Student *newStudent);
void freeList(ListNode *head);
void expList(int *option, ListNode *head);
int checkName(char *name);
int checkSTD(char *stdNum);
int checkGrade(int grade);

// Main Function. //
int main(int argc, char* argv[]){

    // Check if correct number of arguments provided
    if(argc != 3) {
        return 1;
    }

    // Open input and output file
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    int option = 0, *options;

    // creates node, and ensures that both head and the student data start as null
    ListNode *head = malloc(sizeof(struct listNode));
    head -> std = NULL;
    head -> next = NULL;

    options = &option;

    // checks if input or output is null
    if (input == NULL || output == NULL) {
        return 1;
    }

    insertList(head, options);
    expList(options, head);
    freeList(head);
    return 0;
}

void printErrorExit() {
    if (output != NULL) {
        if (input != NULL) fclose(input);
        fprintf(output, "error\n");
        fclose(output);
    }
    exit(1);
}

// checks if the names are valid. //
int checkName(char *name) {
    // base case of null
    if(name == NULL) {
        return 1;
    }

    int position = 0;

    while(*(name + position) != '\0') {
        // checks to see if char is alphabetical / dash
        if(!((*(name + position) >= 'a' && *(name + position) <= 'z') 
        || (*(name + position) >= 'A' && *(name + position) <= 'Z')
        || *(name + position) == '-')) {
            return 0;
        }
        position++;
    }
    return 1;
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

// compares 2 students to see where they should go (all in order). //
int cmpStudent(Student *a, Student *b) {
    // compares last name
    int lastNameCmp = strcmp(a->lastName, b->lastName);
    if(lastNameCmp != 0) {
        return lastNameCmp;
    }

    // compares first name
    int firstNameCmp = strcmp(a->firstName, b->firstName);
    if(firstNameCmp != 0) {
        return firstNameCmp;
    }

    // compares stdNum
    int stdNumCmp = strcmp(a->stdNum, b->stdNum);
    if(stdNumCmp != 0) {
        return stdNumCmp;
    }

    if(a->midtermGrade != b->midtermGrade) {
        return a->midtermGrade - b->midtermGrade;
    }

    return a->finalGrade - b->finalGrade;

}

// insert student into the position of list. //
void insertSTD(ListNode *head, Student *newStudent) {
    ListNode* newNode = malloc(sizeof(struct listNode));
    
    // checks for null base case.
    if (newNode == NULL) {
        printErrorExit();
    }

    newNode->std = newStudent;
    newNode->next = NULL;

    if (head->next == NULL || cmpStudent(newStudent, head->next->std) < 0) {
        newNode->next = head->next;
        head->next = newNode;
    } else {
        ListNode* current = head;
        while (current->next != NULL && cmpStudent(newStudent, current->next->std) > 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// inserts into std struct. //
void insertList(ListNode *head, int *option) {
    char check = 0; 
    // student count
    int count = 0; 

    // Determine the number of students
    while ((check = fgetc(input)) != EOF) {
        if (check == '\n') {
            count++;
        }
    }
    count-=2;                                       

    char buff[100];      
    // set buffer back to the beginning. 
    fseek(input, 0, SEEK_SET);                          
    fgets(buff, 100, input);
    sscanf(buff, "%d", option);

    // make sure that options are in the range
    if (!(*option >= 1 && *option <= 5))             
        printErrorExit();
    
    // set buffer to the beginning of student list.
    fseek(input, 2, SEEK_SET);                          
    int track = 0;

    while (fgets(buff, 100, input) != NULL && track < count) {
        char *lastNameTmp = malloc(15 * sizeof(char));
        char *firstNameTmp = malloc(15 * sizeof(char));
        char *stdTmp = malloc(15 * sizeof(char));
        int midtermGradeTmp = 0;
        int finalGradeTmp = 0;

        if (firstNameTmp == NULL || lastNameTmp == NULL || stdTmp == NULL) {
            printErrorExit();
        }             
            
        int stat = sscanf(buff, "%s %s %s %d %d\n", 
            (char*)lastNameTmp, (char*)firstNameTmp, (char*)stdTmp, &midtermGradeTmp, &finalGradeTmp);    

        // has to have 5 elements
        if (stat != 5)
            printErrorExit();                                                   

        if (checkGrade(midtermGradeTmp) && checkGrade(finalGradeTmp) 
            && checkSTD(stdTmp) && checkName(firstNameTmp) 
            && checkName(lastNameTmp)) {

            Student *newStudent = malloc(sizeof(struct student));

            if (newStudent == NULL)
                printErrorExit();

            newStudent->lastName = lastNameTmp;
            newStudent->firstName = firstNameTmp;
            newStudent->stdNum = stdTmp;
            newStudent->midtermGrade = midtermGradeTmp;
            newStudent->finalGrade = finalGradeTmp;
            newStudent->avgGrade = (midtermGradeTmp + finalGradeTmp) / 2;
            insertSTD(head, newStudent);

        } else {
            printErrorExit();
        }

        track++;
    }
}

// frees the memory. //
void freeList(ListNode *head) {
    ListNode *itr = head->next;

    while (itr != NULL) {
        ListNode *temp = itr->next;
        free(itr->std);
        free(itr);
        itr = temp;
    }
}

// checks lower and upper bound and writes the content if it is in, and satify conditions. //
void filterInsert(int l, int u, ListNode *head) {
    if (output != NULL) {
        ListNode *itr = head->next;
        if (itr == NULL)
            return;

        while (itr != NULL) {
            Student *cS = itr->std;
            if (cS->avgGrade >= l && cS->avgGrade < u)
                fprintf(output, "%s %s %s %d %d\n", 
                    cS->lastName, cS->firstName, cS->stdNum, cS->midtermGrade, cS->finalGrade);
            itr = itr->next;
        }

    } else {
        printErrorExit();
    }
}

// exports items and ouputs based on the bound. //
void expList(int *option, ListNode *head) {
    switch(*option) {
        case 1:
            filterInsert(90, 100, head);
            break;
        case 2:
            filterInsert(80, 90, head);
            break;
        case 3:
            filterInsert(70, 80, head);
            break;
        case 4:
            filterInsert(60, 70, head);
            break;
        case 5:
            filterInsert(0, 60, head);
            break;
    }
}



