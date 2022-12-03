#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{

	int ret  = -1;	///< For return values
	int size = -1;	///< Total number of processors
	int rank = -1;	///< This processor's number

	const int count = 100000000; ///< Number of array elements
	const int random_seed = 920215; ///< RNG seed

	int* array = 0; ///< The array we need to find the max in
	int lmax = -1;	///< Local maximums
	int  max = -1;  ///< The maximal element
	/* Initialize the MPI */
    double start_time, end_time, summary_time=0;
    ret = MPI_Init(&argc, &argv);
    // printf("*** MPI Init returned (%d);\n", ret);
    /* Determine our rankand processor count */
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    /* Allocate the array */
    if (!rank) {
        printf("*** ------------------------------------------------\n");
        printf("*** -------------------- size: %d -----------------\n", size);
        printf("*** ------------------------------------------------\n");
    }
	/* Master generates the array */
    array = (int*)malloc(count * sizeof(int));

    for (int iter = 0; iter < 10; iter++) {
        if (!rank) {
            FILE *fp = NULL;
            char name[100];
            sprintf(name, "../arrays_dir/array%d.txt", iter);
            if ((fp = fopen(name, "r")) == NULL) {
                printf("Cant open file %s", name);
                return 0;
            }
            array = (int *) malloc(count * sizeof(int));
            for (int i = 0; i < count; i++) {
                fscanf(fp, "%d", &array[i]);
            }

        }

        /* Send the array to all other processors */
        MPI_Bcast(array, count, MPI_INTEGER, 0, MPI_COMM_WORLD);
        start_time = MPI_Wtime();
        const int wstart = (rank) * count / size;
        const int wend = (rank + 1) * count / size;

        for (int i = wstart;
             i < wend;
             i++) {
            if (array[i] > lmax) { lmax = array[i]; }
        }


        MPI_Reduce(&lmax, &max, 1, MPI_INTEGER, MPI_MAX, 0, MPI_COMM_WORLD);

        if (!rank) {
            end_time = MPI_Wtime();
            summary_time += (end_time - start_time);
//            printf("*** Global Maximum is for array %d: %d;\n", iter,  max);
//            printf("*** Estimated time is %f\n", end_time - start_time);
//            printf("*** ------------------------------------------------\n");
        }
        lmax = 0;
        max = 0;
    }
    if (!rank) {
        printf("*** Estimated time is %f\n", summary_time);
        printf("*** ------------------------------------------------\n");
    }
    ret = MPI_Finalize();
    // printf("*** MPI Finalize returned (%d);\n", ret);

	return(0);
}