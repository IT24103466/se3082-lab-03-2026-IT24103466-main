#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000000;

int main(int argc, char *argv[]) {
    int nthreads = (argc > 1) ? atoi(argv[1]) : 1;
    omp_set_num_threads(nthreads);

    double step = 1.0 / (double)num_steps;
    double sum = 0.0, pi;

    double tstart = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;      // x is private: declared inside the loop
        sum += 4.0 / (1.0 + x * x);
    }
    pi = step * sum;

    double tcalc = omp_get_wtime() - tstart;
    printf("Threads = %d, Pi = %.15f, Time = %f s\n", nthreads, pi, tcalc);
    return 0;
}
