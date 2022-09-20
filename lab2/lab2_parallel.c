#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <stdbool.h>
int main(int argc, char** argv)
{
    const int count = 10000000;     ///< Number of array elements
    const int random_seed = time(NULL); ///< RNG seed
         ///< Number to look for
    const int procs = 12;
    int* array = 0;                 ///< The array we need to f16ind the max in
    long long index; ///< The index of the element we need
    double start_time, end_time, summary_time = 0;
    bool lock;
    /* Initialize the RNG */
    srand(random_seed);
    const int target = rand() % 100000;
#ifdef _OPENMP
    printf("OpenMP: %d\n", _OPENMP);
#endif

//    /* Generate the random array */
//    array = (int*)malloc(count*sizeof(int));
//    for(int i=0; i<count; i++) { array[i] = rand() % 10000000; }
    for (int iter = 0; iter < 10; iter++) {
        FILE *fp = NULL;
        char name[100];
        sprintf(name, "arrays_dir/array%d.txt", iter);
        if ((fp = fopen(name, "r")) == NULL) {
            printf("Cant open file %s", name);
            return 0;
        }
        array = (int *) malloc(count * sizeof(int));
        for (int i = 0; i < count; i++) {
            fscanf(fp, "%d", &array[i]);
        }
//            printf("Iteration: %d\n", iter);
        /* Find the maximal element */
        /* Find the index of the element */
        start_time = omp_get_wtime();
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
            } else printf("Local index in thread %d is %d\n", omp_get_thread_num(), index);
        }
        end_time = omp_get_wtime();
        summary_time += end_time - start_time;
        printf("\n========\nTime spent: %f\n", end_time - start_time);
        if (index != count)
        {
            printf("\n=======\nFound occurence of %d at index %d;\n=========\n", target, index);
            index = count;
        } else {
            printf("Not found occurence of %d;\n=========\n\n", target);
        }

    }
    printf("\n+==============================+\n");
    printf("Average time for %d threads is %f", procs, summary_time / 10);
    printf("\n+==============================+\n");
    return(0);
}