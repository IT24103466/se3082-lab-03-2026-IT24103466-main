#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000; // N - large integer
double step;

int main() {
    int i;
    double x, pi, sum = 0.0;
    double tstart, tstop, tcalc;

    step = 1.0 / (double)num_steps;

    tstart = omp_get_wtime();

    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Pi = %.15f\n", pi);
    printf("Time (serial) = %f seconds, N = %ld\n", tcalc, num_steps);

    return 0;
}
