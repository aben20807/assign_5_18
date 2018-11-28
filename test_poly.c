#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynamic_gen/dynamic_poly.h"
#include "poly_funcs_5_5.h"
#include "poly_funcs_5_6.h"

typedef double (*PolyFunc)(double a[], double x, long degree);

#define TEST_TIMES 10000
#define MAX_DEGREE 1000
#define DEGREE_STEP 10
#define CPU_FREQ 1400000000

/* Record cycle count per test time of each degree */
double exec_cyc[TEST_TIMES] = {0};

int compare(const void *a, const void *b)
{
    return (*(double *) a - *(double *) b);
}

double tvgetf()
{
    struct timespec ts;
    double sec;

    clock_gettime(CLOCK_REALTIME, &ts);
    sec = ts.tv_nsec;
    sec /= 1e9;
    sec += ts.tv_sec;

    return sec;
}

double test_poly(PolyFunc poly, long degree)
{
    /* Create test array */
    double a[degree + 1];
    for (long i = 0; i < degree + 1; i++) {
        a[i] = (double) i;
    }

    double ans = 0;
    for (int i = 0; i < TEST_TIMES; i++) {
        double t1 = tvgetf();
        ans = poly(a, -1, degree);
        double t2 = tvgetf();

        exec_cyc[i] = (t2 - t1) * CPU_FREQ;

        /* Check correctness */
        if (ans != (double) degree / 2) {
            fprintf(stderr, "wrong answer: %lf (should be %lf)\n", ans,
                    (double) degree / 2);
            exit(1);
        }
    }

    /* Exclude extreme values and calculate the average */
    double total_cyc = 0;
    qsort(exec_cyc, TEST_TIMES, sizeof(double), compare);
    int extreme_num = TEST_TIMES / 20;
    for (int i = 0 + extreme_num; i < TEST_TIMES - extreme_num; i++) {
        total_cyc += exec_cyc[i];
    }
    return total_cyc / (TEST_TIMES * 9 / 10);
}

int main(int argc, char *argv[])
{
    int arg = atoi(argv[1]);
    if (argc != 2 && (arg < 1 || arg > 3)) {
        printf("Error: invalid argument\n");
        return 0;
    }

    double cycle_1, cycle_2;
    if (arg == 1) {
        for (int i = 0; i < MAX_DEGREE; i += DEGREE_STEP) {
            cycle_1 = test_poly(poly_5_05, i);
            cycle_2 = test_poly(poly_5_06, i);
            printf("%d\t%lf\t%lf\n", i, cycle_1, cycle_2);
        }
    } else if (arg == 2) {
        for (int i = 0; i < MAX_DEGREE; i += DEGREE_STEP) {
            cycle_1 = test_poly(poly_5_05, i);
            cycle_2 = test_poly(poly_5_05_6way, i);
            printf("%d\t%lf\t%lf\n", i, cycle_1, cycle_2);
        }
    } else if (arg == 3) {
        for (int i = 0; i < MAX_DEGREE; i += DEGREE_STEP) {
            cycle_1 = test_poly(poly_5_06, i);
            cycle_2 = test_poly(poly_5_06_rev, i);
            printf("%d\t%lf\t%lf\n", i, cycle_1, cycle_2);
        }
    } else {
        for (int i = 0; i < MAX_DEGREE; i += DEGREE_STEP) {
            cycle_1 = test_poly(poly_5_05, i);
            printf("%d\t%lf\t", i, cycle_1);

            cycle_1 = test_poly(poly_5_05_rev_2, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_rev_3, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_rev_4, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_rev_5, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_rev_6, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_rev_7, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_rev_8, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_3way, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_6way, i);
            printf("%lf\t", cycle_1);

            cycle_1 = test_poly(poly_5_05_9way, i);
            printf("%lf\n", cycle_1);
        }
    }

    return 0;
}
