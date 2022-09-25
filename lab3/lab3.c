#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void shell_sort(int *array, int size) {
    for (int s = size / 2; s > 0; s /= 2) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
                int temp = array[j];
                array[j] = array[j + s];
                array[j + s] = temp;
            }
        }
    }

}

int main(int argc, char** argv) {

    const int count = 100;     ///< Number of array elements
    const int random_seed = 920214; ///< RNG seed
    const int target = 16;          ///< Number to look for

    int* array = 0;                 ///< The array we need to find the max in
    int  index = -1;                ///< The index of the element we need

    /* Initialize the RNG */
    srand(random_seed);

    /* Generate the random array */
    array = (int*)malloc(count*sizeof(int));

    for(int i=0; i<count; i++) {
        array[i] = rand() % 100;
        printf("%d ", array[i]);
    }
    shell_sort(array, count);
    printf("\n=========\n");

    for(int i=0; i<count; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}