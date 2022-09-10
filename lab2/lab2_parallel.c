#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char** argv)
{
    const int count = 10000000;     ///< Number of array elements
    const int random_seed = time(NULL); ///< RNG seed
    const int target = 13451;          ///< Number to look for

    int* array = 0;                 ///< The array we need to f16ind the max in
    int  index = -1;                ///< The index of the element we need

    /* Initialize the RNG */
    srand(random_seed);

    /* Generate the random array */
    array = (int*)malloc(count*sizeof(int));
    for(int i=0; i<count; i++) { array[i] = rand(); }

    /* Find the index of the element */
#pragma omp parallel default(none) shared(array, count, target) reduction(min:index)
    {
#pragma for
        for (int i = 0; i < count; i++) {
            if (array[i] == target) {
                index = i;
                break;
            }
        }
        printf("Local index is %d\n", index);
    }
    printf("Found occurence of %d at index %d;\n", target, index);
    return(0);
}