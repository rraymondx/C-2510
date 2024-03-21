#include <stdio.h>

int binarySearch(int arr[], int l, int r, int x)
{

    if (r >= 1)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x){
            printf("hehe\n");
            return mid;
        }

        if (arr[mid] > x) {
            printf("hehe2\n");
            return binarySearch(arr, l, mid - 1, x);
        }
        printf("hehe3\n");
        return binarySearch(arr, mid + 1, r, x);
    }

    return -1;
}

int main()
{
    int arr[] = {1, 3, 5, 7, 8, 11, 13, 15};

    int res = binarySearch(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, 11);

    if (res == -1)
    {
        printf("failed to search the target\n");
    }
    else
    {
        printf("the result is found %d\n", res);
    }

    return 0;
}