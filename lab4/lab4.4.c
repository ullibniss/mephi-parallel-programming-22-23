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

    double start_time, end_time;
    start_time = omp_get_wtick();
    sleep(5);
    end_time = omp_get_wtick();
    printf("Time is: %f", end_time - start_time);

}