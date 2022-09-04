#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main(int argc, char** argv)
{

#ifdef _OPENMP
    printf("OpenMP Version: %d\n", _OPENMP);
#endif

    const int count = 10000000;     ///< Number of array elements
    const int threads = 12;         ///< Number of parallel threads to use
//    const int random_seed = 920215; ///< RNG seed

    int* array = 0;                 ///< The array we need to find the max in
    int  max   = -1;                ///< The maximal element

    /* Initialize the RNG */
//    srand(random_seed);

    /* Determine the OpenMP support */
    printf("OpenMP: %d;\n======\n", _OPENMP);

    /* Generate the random array */
//    array = (int*)malloc(count*sizeof(int));
//    for(int i=0; i<count; i++) { array[i] = rand(); }

    /* Read array from file */

    double _time;
    double _summary_time = 0;
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
        printf("Iteration: %d\n", iter);
        /* Find the maximal element */
        double start_time = omp_get_wtime();
#pragma omp parallel num_threads(threads) shared(array, count) reduction(max: max) default(none)
        {
#pragma omp for
            for (int i = 0; i < count; i++) {
                if (array[i] > max) { max = array[i]; };
            }
            // printf("-- My lmax is: %d;\n", max);
        }
        double end_time = omp_get_wtime();
        _time = end_time - start_time;
        printf("======\nMax is: %d;\nTime: %f;\n======\n", max, _time);
        _summary_time += _time;
    }
    printf("Process finished\n");
    printf("Average time: %f\n", _summary_time / 10);
    printf("Threads number: %d\n", threads);
    return(0);
}