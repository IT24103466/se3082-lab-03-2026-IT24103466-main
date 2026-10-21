#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000L

int main(int argc, char *argv[]) {
    int nthreads = (argc > 1) ? atoi(argv[1]) : 1;
    omp_set_num_threads(nthreads);

    long inside = 0;
    double tstart = omp_get_wtime();

    #pragma omp parallel reduction(+:inside)
    {
        unsigned int seed = 12345u + omp_get_thread_num();   // per-thread seed
        #pragma omp for
        for (long i = 0; i < N; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) inside++;
        }
    }
    double pi = 4.0 * (double)inside / (double)N;

    double tcalc = omp_get_wtime() - tstart;
    printf("Threads = %d, Pi ~ %.6f, Time = %f s\n", nthreads, pi, tcalc);
    return 0;
}
