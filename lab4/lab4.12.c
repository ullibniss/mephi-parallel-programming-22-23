//
// Created by ullibniss on 25.09.22.
//
#include <omp.h>

int main(int argc, char **argv) {

#ifdef _OPENMP
    printf("+--Point 1--+\nOpenMP Version %d\n+-----+\n", _OPENMP)
#endif

    printf("+--Point 2--+\n");
    printf("Available procs: %d\n", omp_get_num_procs());
    printf("Available threads: %d\n", omp_get_num_threads());
    printf("+-----+");


    return 0;
}