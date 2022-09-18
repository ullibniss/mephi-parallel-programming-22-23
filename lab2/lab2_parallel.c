#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <stdbool.h>
int main(int argc, char** argv)
{
    const int count = 10000000;     ///< Number of array elements
    const int random_seed = time(NULL); ///< RNG seed
    const int target = 456789;          ///< Number to look for
    const int procs = omp_get_num_procs();
    int* array = 0;                 ///< The array we need to f16ind the max in
    long long index;                ///< The index of the element we need
    bool lock;
    /* Initialize the RNG */
    srand(random_seed);

#ifdef _OPENMP
    printf("OpenMP: %d\n", _OPENMP);
#endif

    /* Generate the random array */
    array = (int*)malloc(count*sizeof(int));
    for(int i=0; i<count; i++) { array[i] = rand() % 10000000; }

    /* Find the index of the element */
#pragma omp parallel num_threads(procs) shared(array, count, target) private(lock) reduction(min: index) default(none)
    {
        lock = 0;

#pragma omp for
        for (int i = 0; i < count; i++) {
            if (array[i] == target && lock != 1) {
                lock = 1;
                index = i;
            }
        }

        if (index > count || index < 0) {
            index = count;
            printf("Local index in thread %d not found\n", omp_get_thread_num());
        }
        else printf("Local index in thread %d is %d\n", omp_get_thread_num(), index);
    }
    printf("Found occurence of %d at index %d;\n", target, index);
    return(0);
}