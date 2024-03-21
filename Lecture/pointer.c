#include<stdio.h>
#include<stdlib.h>

int main() {
    int i = 4;
    // address of the first byte of i
    int *p = &i;  
    // dereferences a pointer, in this case, p
    int res = *p;
    // operator multiply
    int mul = 1*2;

    printf("value:\t\t%d\n", i);
    printf("address:\t%lu\n", (unsigned long) p);
    printf("verify:\t%d\n", (unsigned long) res);
    
    return 0;
}