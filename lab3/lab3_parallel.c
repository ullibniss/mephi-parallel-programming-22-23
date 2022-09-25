#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {

    const int count = 10000000;     ///< Number of array elements
    const int random_seed = 920214; ///< RNG seed

    int* array = 0;                 ///< The array we need to find the max in
    int  index = -1;                 ///< The index of the element we need
    int procs = 12;
    double start_time, end_time, summary_time = 0;
    /* Initialize the RNG */
    srand(random_seed);

    if (argv[1] != NULL) {
        procs = atoi(argv[1]);
    }
//    /* Generate the random array */array = (int*)malloc(count*sizeof(int));

//    for(int i=0; i<count; i++) {
//        array[i] = rand() % 1000000;
//        printf("%d ", array[i]);
//    }
//    printf("\n=========\n");

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
        start_time = omp_get_wtime();
#pragma omp parallel default(none) shared(array, count) num_threads(procs)
        {
            for (int s = count / 2; s > 0; s /= 2) {
#pragma omp for
                for (int i = s; i < count; ++i) {
                    for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
                        int temp = array[j];
                        array[j] = array[j + s];
                        array[j + s] = temp;
                    }
                }
            }
        }

        end_time = omp_get_wtime();
//        printf("Array: %d, Time is: %f\n", iter, end_time - start_time);
        summary_time += end_time - start_time;
//    for(int i=0; i<count; i++) {
//        printf("%d ", array[i]);
//    }
    }
    printf("\n+--------+\n");
    printf("Average time: %f", summary_time / 10);
    printf("\n+--------+\n");
    return 0;
}