#include <stdio.h>
#include <stdlib.h>

// A01343016

int fill(char **arrF, int xMax, int yMax) {

    for(int i = 1; i < yMax; i++) {
        
        int flag = 0;

        for(int j = 0; j <= xMax; j++) {
            if(arrF[i][j] == '1') {
                if(flag == 0) {
                    flag = 1;
                } else if(flag == 1) {
                    flag = 0;
                }
            }
            if(flag == 1) {
                arrF[i][j] = '1';
            }
        }
    }
    return 0;
}

int createGrid(FILE *input, FILE *output) {

    char buff[10];
    int x = -1;
    int y = -1;
    int maxX = 0;
    int maxY = 0;

    while(fgets(buff, 10, input) != NULL) {
        
        sscanf(buff, "%d, %d", &x, &y);
        if(x < 0 || y < 0) {
            fputs("Error", output);
            return -1;
        }
        if(x > maxX) {
            maxX = x;
        }
        if (y > maxY) {
            maxY = y;
        }
    }

    rewind(input);

    char **arr;
    arr = (char **)malloc((maxY + 1) * sizeof(char *));

    if(arr == NULL) {
        return -1;
    }

    for(int i = 0; i < (maxY + 1); i++) {
        arr[i] = (char *)malloc((maxX + 1) * sizeof(char));
        if(arr[i] == NULL) {
            return -1;
        }
    }

    for(int i = 0; i <= maxY; i++) {
        for(int j = 0; j < maxX; j++) {
            arr[i][j] = '0';
        }
    }

    int prevX;
    int prevY;
    int deltaX;
    int deltaY;

    fgets(buff, 10, input);
    sscanf(buff, "%d, %d", &x, &y);

    while(fgets(buff, 10, input) != NULL) {
        // makes it so the previous values of x, y are stored in the variable
        prevX = x;
        prevY = y;
        sscanf(buff, "%d, %d", &x, &y);

        // calculates the difference between previous values of x,y
        if(prevX < x) {
            deltaX = 1;
        } else if(prevX > x) {
            deltaX = -1;
        }else {
            deltaX = 0;
        }

        if(prevY < y) {
            deltaY = 1;
        } else if(prevY > y) {
            deltaY = -1;
        } else {
            deltaY = 0;
        }

        // degree is gonna be 45, therfore we will stop when prevX = x
        while(prevX != x || prevY != y) {
            arr[prevY][prevX] = '1';
            prevX += deltaX;
            prevY += deltaY;
        }
    }

    fill(arr, maxX, maxY);

    for(int i = maxY; i >= 0; i--) {
        int count = 0;

        for(int j = 0; j <= maxX; j++) {

            if(arr[i][j] == '1') {
                fputc('*', output);
                count = 1;
            } else {
                if(count == 0) {
                    fputc(' ', output);
                } else {
                    break;
                }
            }
        }
        if(i != 0) {
            fputc('\n', output);
        }
    }

    fclose(input);
    fclose(output);

    for(int i = 0; i <= maxY; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL) {
        return 1;
    }

    if (createGrid(inputFile, outputFile) == -1) {
        return 1;
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}