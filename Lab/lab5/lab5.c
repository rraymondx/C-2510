#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Update this with your A number
char a_num[] = "01343016";

void zoomArray(char ***arr, float n, int *rows, int *cols)
{
    int newRows = (int)((float)(*rows) * n);
    int newCols = (int)((float)(*cols) * n);

    char **newArr = (char **)malloc(newRows * sizeof(char *));
    if (newArr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < newRows; i++) {
        newArr[i] = (char *)malloc(newCols * sizeof(char));
        if (newArr[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            int ogRows = (int)((float)i / n);
            int ogCols = (int)((float)j / n);
            newArr[i][j] = (*arr)[ogRows][ogCols];
        }
    }

    for (int i = 0; i < *rows; i++) {
        free((*arr)[i]);
    }
    free(*arr);
    *arr = newArr;

    *rows = newRows;
    *cols = newCols;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    int dimensions = 0;
    char **arr = NULL;
    int rows = 0, cols = 0;
    float zoomFactor = 0;

    FILE *file = fopen(inputFileName, "r");
    if (file == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    fscanf(file, "%d", &rows);
    fscanf(file, "%d", &cols);
    fscanf(file, "%f", &zoomFactor);

    arr = (char **)malloc(rows * sizeof(char *));
    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < rows; i++)
    {
        arr[i] = (char *)malloc(cols * sizeof(char));
        if (arr[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    char inputChar;
    int i = 0, j = 0;
    while ((inputChar = fgetc(file)) != 'E')
    {
        if (inputChar >= '0' && inputChar <= '9' && i < rows && j < cols)
        {
            arr[i][j++] = inputChar;
            if (j == cols)
            {
                j = 0;
                i++;
            }
        }
    }

    fclose(file);
    printf("A%s\n", a_num);

    printf("Input Array:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    zoomArray(&arr, zoomFactor, &rows, &cols);

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        return 1;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fprintf(outputFile, "%c", arr[i][j]);
        }
        if (i < rows -  1)
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);

    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
