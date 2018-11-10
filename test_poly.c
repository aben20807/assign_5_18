#include <papi.h>
#include <stdio.h>
#include <stdlib.h>
#include "poly_5_05.h"
#include "poly_5_06.h"
#include "poly_5_06_rev.h"

typedef double (*PolyFunc)(double a[], double x, long degree);

#define TEST_TIMES 1000
#define MAX_DEGREE 10000
#define DEGREE_STEP 100

/* Record cycle count per test time of each degree */
long long exec_cyc[TEST_TIMES] = {0};

int compare(const void *a, const void *b)
{
    return (*(int *) a - *(int *) b);
}

double test_poly(PolyFunc poly, long degree)
{
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        exit(1);
    }

    /* Create test array */
    double a[degree + 1];
    for (long i = 0; i < degree + 1; i++) {
        a[i] = (double) i;
    }

    long long s, e;
    double ans = 0;
    for (int i = 0; i < TEST_TIMES; i++) {
        s = PAPI_get_real_cyc();
        ans = poly(a, -1, degree);
        e = PAPI_get_real_cyc();
        exec_cyc[i] = e - s;

        /* Check correctness */
        if (ans != (double) degree / 2) {
            printf("wrong answer: %lf (should be %lf)\n", ans,
                   (double) degree / 2);
        }
    }

    /* Exclude extreme values and calculate the average */
    double total_cyc = 0;
    qsort(exec_cyc, TEST_TIMES, sizeof(long long), compare);
    int extreme_num = TEST_TIMES / 20;
    for (int i = 0 + extreme_num; i < TEST_TIMES - extreme_num; i++) {
        total_cyc += (double) exec_cyc[i];
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
            cycle_2 = test_poly(poly_5_06, i);
            printf("%d\t%lf\t%lf\n", i, cycle_1, cycle_2);
        }
    } else {
        for (int i = 0; i < MAX_DEGREE; i += DEGREE_STEP) {
            cycle_1 = test_poly(poly_5_06, i);
            cycle_2 = test_poly(poly_5_06_rev, i);
            printf("%d\t%lf\t%lf\n", i, cycle_1, cycle_2);
        }
    }

    return 0;
}
