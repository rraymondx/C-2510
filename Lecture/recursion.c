#include <stdio.h>
#include <stdlib.h>

int expn(int x, int n) {

    if(n == 0) {
        return 1;
    } else {
        return x * expn(x, n - 1);
    }
    return 0;
}


int main(int argc, char**argv) {
    int x = atoi(argv[1]);
    int n = atoi(argv[2]);

    int res = expn(x, n);

    printf("result is: %d\n", res);

    return res;
}