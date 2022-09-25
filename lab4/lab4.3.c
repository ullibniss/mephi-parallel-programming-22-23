//
// Created by ullibniss on 25.09.22.
//
#include <omp.h>

int main(int argc, char **argv) {

#ifdef _OPENMP
    printf("+--Point 1--+\nOpenMP Version %d\n+-----+\n", _OPENMP)
#endif

    printf("Значение OMP_DYNAMIC: %d\n", omp_get_dynamic());
    omp_set_dynamic(1);
    printf("Значение OMP_DYNAMIC: %d\n", omp_get_dynamic());
#pragma omp parallel num_threads(128)
    {
#pragma omp master
    {
        printf("Параллельная область, %d нитей\n", omp_get_num_threads());
    }
    return 0;
}