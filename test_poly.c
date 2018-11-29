#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dynamic_gen/gen_plot.h"
#include "dynamic_gen/gen_poly.h"

typedef double (*PolyFunc)(double a[], double x, long degree);

#define TEST_TIMES 10000
#define MAX_DEGREE 1000
#define DEGREE_STEP 10
#define CPU_FREQ 1400000000

enum error_type { TOO_FEW_ARGS, NULL_RETURN, WRONG_ARGS, PLOT_ERROR };

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

    for (int i = 0; i < TEST_TIMES; i++) {
        double t1 = tvgetf();
        double ans = poly(a, -1, degree);
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

void help_message()
{
    printf("Usage ./test_poly [Options] [argument]\n");
    printf("Available options: \n");
    printf(
        "\tdefault: run every instances of unrolling number and split "
        "number\n");
    printf("\t         and show the best CPE found on the system\n");
    printf("\t         also look for the processor model name and max freq\n");
    printf("\tplot: plot comparison graph for every argument listed\n");
    printf("\t      issue- shall we set maximum argument number?\n");
    printf("\tcompare: evaluate CPE for different argument,\n");
    printf("\t            and look for the best one\n");
    printf("\thelp: show this help message again\n");
}

void runtime_error_message(int type)
{
    switch (type) {
    case WRONG_ARGS:
        printf("Wrong arguments, please check the following help\n");
        help_message();
        break;
    case TOO_FEW_ARGS:
        printf("Too few arguments, please check the following help\n");
        help_message();
        break;
    case NULL_RETURN:
        printf("Error when creating func array\n");
        break;
    case PLOT_ERROR:
        printf("Some error with plotting code...\n");
        break;

    default:
        help_message();
    }
}

PolyFunc *load_function_array()
{
    if (system("clang-format -i dynamic_gen/dynamic_poly.c") == -1) {
        return NULL;
    }
    printf("Successfully formatted\n");

    if (system("gcc -c -fPIC dynamic_gen/dynamic_poly.c") == -1) {
        return NULL;
    }
    printf("Successfully compiled dynamic.c\n");

    if (system("gcc -o libdynamic_poly.so -shared dynamic_poly.o") == -1) {
        return NULL;
    }
    printf("Successfully create dynamic library\n");

    void *handle = dlopen("./libdynamic_poly.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    PolyFunc *func_arr = dlsym(handle, "func_arr");

    char *error;
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    return func_arr;
}

double default_test()
{
    // default test, find lowest CPE
    gen_init(64);
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            gen_append_poly(i, j);
        }
    }

    PolyFunc *func_arr = load_function_array();
    if (func_arr == NULL) {
        runtime_error_message(NULL_RETURN);
        return 0;
    }

    double min = 10.0;
    for (int i = 1; i <= 8; i++) {
        for (int k = 1; k <= 8; k++) {
            double CPE = 0.0;
            int count = 0;
            for (int j = 0; j < MAX_DEGREE; j += DEGREE_STEP) {
                count++;
                double cycle = test_poly(func_arr[i * k - 1], j);
                // printf("cycle = %lf, degree = %d\n", cycle, j);
                if (j != 0) {
                    CPE += (cycle / j);
                }
            }
            CPE /= count;
            printf("Split = %d, Unroll = %d, CPE = %lf\n", i, k, CPE);
            if (CPE < min) {
                min = CPE;
            }
        }
    }

    return min;
}

double compare_test(int n, int *index)
{
    PolyFunc *func_arr = load_function_array();
    if (func_arr == NULL) {
        runtime_error_message(NULL_RETURN);
        return 0;
    }

    double min = 10.0;
    for (int i = 0; i < n; i++) {
        double CPE = 0.0;
        int count = 0;
        for (int j = 0; j < MAX_DEGREE; j += DEGREE_STEP) {
            count++;
            double cycle = test_poly(func_arr[i], j);
            // printf("cycle = %lf, degree = %d\n", cycle, j);
            if (j != 0) {
                CPE += (cycle / j);
            }
        }
        CPE /= count;
        if (CPE < min) {
            *index = i;
            min = CPE;
        }
    }

    return min;
}

int plot_test(int n, char *argv[])
{
    PolyFunc *func_arr = load_function_array();
    if (func_arr == NULL) {
        runtime_error_message(NULL_RETURN);
        return 0;
    }

    gen_plot(n, argv);

    FILE *plot_output = fopen("output.txt", "w");

    for (int j = 0; j < MAX_DEGREE; j += DEGREE_STEP) {
        fprintf(plot_output, "%d ", j);
        double cycle;
        for (int i = 0; i < n; i++) {
            cycle = test_poly(func_arr[i], j);
            fprintf(plot_output, "%lf ", cycle);
        }
        fprintf(plot_output, "\n");
    }

    fclose(plot_output);

    if (system("gnuplot dynamic_gen/plot.gp") == -1) {
        return 0;
    }

    if (system("eog poly.png") == -1) {
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    if (system("sudo cpupower frequency-set -g performance && sleep 1") == -1) {
        return 0;
    }
    // implement 3 type of operation, which are default, plot and compare
    if (argc == 1) {
        // run default, altogether 64 cases
        double result = default_test();
        printf("Lowest CPE = %lf\n", result);
    }

    // check argument correctness
    if (argc >= 2) {
        if (!strcmp(argv[1], "default") && argc == 2) {
            // same as no argument
            // default op should have no further arguments
            double result = default_test();
            printf("Lowest CPE = %lf\n", result);
        } else if (!strcmp(argv[1], "plot")) {
            if (argc == 2) {
                runtime_error_message(TOO_FEW_ARGS);
            }

            gen_init(argc - 2);
            for (int i = 2; i < argc; i++) {
                char *temp = strdup(argv[i]);
                char *pch;
                pch = strtok(temp, ",");
                int x = atoi(pch);
                pch = strtok(NULL, ",");
                int y = atoi(pch);

                free(temp);

                printf("Creating %d splits and %d unroll\n", x, y);
                gen_append_poly(x, y);
            }

            if (!plot_test(argc - 2, argv)) {
                runtime_error_message(PLOT_ERROR);
            }
        } else if (!strcmp(argv[1], "compare")) {
            if (argc < 4) {  // at least 2 to compare
                runtime_error_message(TOO_FEW_ARGS);
            }

            gen_init(argc - 2);
            for (int i = 2; i < argc; i++) {
                char *temp = strdup(argv[i]);
                char *pch;
                pch = strtok(temp, ",");
                int x = atoi(pch);
                pch = strtok(NULL, ",");
                int y = atoi(pch);

                free(temp);

                printf("Creating %d splits and %d unroll\n", x, y);
                gen_append_poly(x, y);
            }

            int index;
            double result = compare_test(argc - 2, &index);
            printf("Best split & unroll: %s\n", argv[index + 2]);
            printf("Lowest CPE = %lf\n", result);
        } else if (!strcmp(argv[1], "help")) {
            help_message();
        } else {
            runtime_error_message(WRONG_ARGS);
        }
    }

    if (system("sudo cpupower frequency-set -g powersave") == -1) {
        return 0;
    }

    printf("Program closing...\n");
    return 0;
}
