//
// Created by ullibniss on 25.09.22.
//
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv) {

#ifdef _OPENMP
    printf("+--Point 1--+\nOpenMP Version %d\n+-----+\n", _OPENMP)
#endif

    printf("+--Point 5--+\n");
    printf("Nested tumbler now is on: %d\n", omp_get_nested());
    printf("Maximun levels bow is %d", omp_get_max_active_levels());
    printf("+-----+\n");

    printf("+--Point 6--+\n");
    printf("Schecule tumbler now is on: %d\n", omp_get_schedule());
    printf("+-----+\n");
    return 0;
}