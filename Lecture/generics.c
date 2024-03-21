#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void swap(pointer to data1, pointer to data2, size_t nbytes) {
//     store a copy of data1 in temporary storage
//     copy data2 to location of data1
//     copy data in temporary storage to location of data2
// }

// already in system
// void *memcpy(void *dest, const void *src, size_t n);
// void *memmove(void *str1, const void *str2, size_t n); --> useful for array rotatation (in place)
// void swap(void *data1ptr, void *data2ptr, size_t bytes);

// int main(int argc, char *argv[]){
//     int x = 5;
//     int y = 4;
//     swap(&x, &y, sizeof(x));
//     printf("%d, %d", x, y);
// }

// all pointers are same size
// arithmetic with pointers, like int *ptr... ptr++ is gone
void swap(void *data1ptr, void *data2ptr, size_t nbytes) {
    char temp[nbytes];
    memcpy(temp, data1ptr, nbytes);
    memcpy(data1ptr, data2ptr, nbytes);
    memcpy(data2ptr, temp, nbytes);
}

void swap_ends(void *arr, size_t nelems, size_t elem_bytes);

int main(int argc, char **argv) {
    int nums[] = {5, 2, 3, 4, 1};
    size_t nelems = sizeof(nums) / sizeof(nums[0]);
    swap_ends(nums, nelems, sizeof(nums[0]));
    printf("%d", nums[2]);
}
// generic swap function for arrays
void swap_ends(void *arr, size_t nelems, size_t elem_bytes) {
    // fake it till you make it... amen
    swap(arr, (char *)arr + (nelems - 1) * elem_bytes, elem_bytes);
}
