#include <stdio.h>

void helper(int *y) {
    *y = 4;
    return;
}

int main() {
    int x = 2;

    printf("before hehe:%d\t\n", x);
    helper(&x);
    printf("after hehe:%d\t\n", x);
    return 0;
}