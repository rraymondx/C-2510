#include <stdio.h>
#include <stdlib.h>

// update this with your A number
char a_num[] = "01343016";

void rotateArray(int arr[10][10], int n, int rows, int cols)
{

    // to calculate the amount of times you need to rotate
    int calcuRotate = ((n % 360) + 360) % 360 / 90;

    // does the rotating part
    for (int index = 0; index < calcuRotate; index++) {

        int direction = (n > 0) ? 1 : -1;

        for (int j = 0; j < rows / 2; j++) {

            for (int k = j; k < cols - j - 1; k++) {

                int tempVal = arr[j][k];

                if (direction == 1) {

                    arr[j][k] = arr[rows - 1 - k][j];
                    arr[rows - 1 - k][j] = arr[rows - 1 - j][cols - 1 - k];
                    arr[rows - 1 - j][cols - 1 - k] = arr[k][cols - 1 - j];
                    arr[k][cols - 1 - j] = tempVal;

                } else {

                    arr[j][k] = arr[k][cols - 1 - j];
                    arr[k][cols - 1 - j] = arr[rows - 1 - j][cols - 1 - k];
                    arr[rows - 1 - j][cols - 1 - k] = arr[rows - 1 - k][j];
                    arr[rows - 1 - k][j] = tempVal;

                }
            }
        }
    }

    // Do NOT write any code below
    // Output the rotated array
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] == 0)
                printf(" ");
            else
                printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <input_file> <input_angle_degrees>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int rotationAngle = 0;
    int dimensions = 0;
    int arr[10][10] = {0}; // Initialize the array with zeros
    int rows = 0, cols = 0;
    char inputChar;

    // Read the input array from the specified file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    // Read the first line for angle of rotation and second line for array dimensions
    fscanf(file, "%d", &rotationAngle);
    fscanf(file, "%d", &dimensions);
    // Read the input array character by character
    int counter = 0; // To skip first two lines in the file
    while (rows < 10 && (inputChar = fgetc(file)) != 'E')
    {
        if (inputChar == '\n')
        {
            counter++;
        }
        if (inputChar == '\n' && counter >= 2)
        {
            rows++;
            cols = 0;
        }
        else if (cols < 10 && inputChar >= '0' && inputChar <= '9')
        {
            arr[rows][cols++] = inputChar - '0';
        }
    }

    fclose(file);
    printf("A%s\n", a_num);
    // Actual dimensions of the input array
    rows = cols = dimensions;

    printf("Input array:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] == 0)
                printf(" ");
            else
                printf("%d", arr[i][j]);
        }
        printf("\n");
    }

    printf("\nRotated array (%d degrees):\n", rotationAngle);
    rotateArray(arr, rotationAngle, rows, cols);

    return 0;
}
