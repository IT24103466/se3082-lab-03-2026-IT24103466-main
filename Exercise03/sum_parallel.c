#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 10000000L

int main(int argc, char *argv[]) {
    int nthreads = (argc > 1) ? atoi(argv[1]) : 1;
    omp_set_num_threads(nthreads);

    double S = 0.0;
    double tstart = omp_get_wtime();

    #pragma omp parallel for reduction(+:S)
    for (long i = 1; i <= N; i++) {
        double d = (double)i;                       // avoid int overflow of i*i
        S += d - d * d + sqrt(2.0 * (d + 1.0));
    }

    double tcalc = omp_get_wtime() - tstart;
    printf("Threads = %d, S = %.6e, Time = %f s\n", nthreads, S, tcalc);
    return 0;
}
