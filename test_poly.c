#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dynamic_gen/dynamic_poly.h"
#include "dynamic_gen/gen_plot.h"

typedef double (*PolyFunc)(double a[], double x, long degree);

typedef struct _RunData RunData;
struct _RunData {
    int unrol_idx;
    int split_idx;
    double cpe;
} run_data[64];

#define TEST_TIMES 10000
#define MAX_DEGREE 1000
#define DEGREE_STEP 10

enum error_type { TOO_FEW_ARGS, WRONG_ARGS, READ_ERROR };

/* Record cycle count per test time of each degree */
double exec_cyc[TEST_TIMES] = {0};

int cyc_cmp(const void *a, const void *b)
{
    return (*(double *) a - *(double *) b);
}

int run_data_cmp(const void *a, const void *b)
{
    RunData *r1 = (RunData *) a;
    RunData *r2 = (RunData *) b;
    return ((double) (r1->cpe) * 100000 - (double) (r2->cpe) * 100000);
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

double test_poly(PolyFunc poly, long degree, long cpu_freq)
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

        exec_cyc[i] = (t2 - t1) * cpu_freq;

        /* Check correctness */
        if (ans != (double) degree / 2) {
            fprintf(stderr, "wrong answer: %lf (should be %lf)\n", ans,
                    (double) degree / 2);
            exit(1);
        }
    }

    /* Exclude extreme values and calculate the average */
    double total_cyc = 0;
    qsort(exec_cyc, TEST_TIMES, sizeof(double), cyc_cmp);
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
    printf("\thelp: show this help message again\n\n");
    printf("\tSAMPLE: ./test_poly compare 1,1 2,2 3,3\n");
}

void runtime_error_message(int type)
{
    switch (type) {
    case WRONG_ARGS:
        printf("Wrong arguments, please check the following help\n");
        break;
    case TOO_FEW_ARGS:
        printf("Too few arguments, please check the following help\n");
        break;
    case READ_ERROR:
        printf("Check file IO and fgets...\n");
        goto exit_program;
    default:
        printf("Unknown error\n");
    }
    help_message();
exit_program:
    exit(1);
}

long read_cpu_freq()
{
    FILE *cpu_file =
        fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");
    if (!cpu_file) {  // error cant read cpuinfo
        runtime_error_message(READ_ERROR);
        return -1;
    }

    char info_line[20] = {0};
    if (fgets(info_line, 20, cpu_file) == NULL) {
        runtime_error_message(READ_ERROR);
        fclose(cpu_file);
        return -1;
    }
    fclose(cpu_file);
    return atol(info_line) * 1000;
}

void print_cpu_model()
{
    FILE *cpu = fopen("/proc/cpuinfo", "r");

    char info_line[200];
    while (fgets(info_line, 200, cpu) != NULL) {
        char *pch;
        pch = strstr(info_line, "model name");
        if (pch) {
            pch = strstr(info_line, "Intel");
            printf("%s", pch);
            break;
        }
    }

    fclose(cpu);
}

void separate_argv(char *argv, int *split_num, int *unrol_num)
{
    char *temp = strdup(argv);
    /* Do seperation */
    *split_num = atoi(strtok(temp, ","));
    *unrol_num = atoi(strtok(NULL, ","));
    free(temp);
    printf("Using %d splits and %d unroll\n", *split_num, *unrol_num);
}

double default_test(int *best_unroll_idx, int *best_split_idx)
{
    // default test, find lowest CPE among 64 poly functions
    long cpu_freq = read_cpu_freq();
    printf("CPU max freq = %ld hz\n", cpu_freq);

    int func_count = 0;
    double min = 100.0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            double CPE = 0.0;
            // if k is 0 cannot compute the ratio (CPE / k)
            for (int k = DEGREE_STEP; k < MAX_DEGREE; k += DEGREE_STEP) {
                double cycle = test_poly(func_arr[func_count], k, cpu_freq);
                // printf("cycle = %lf, degree = %d\n", cycle, k);
                CPE += (cycle / k);
            }
            CPE /= (MAX_DEGREE / DEGREE_STEP - 1);
            // printf("Split = %d, Unroll = %d, CPE = %lf\n", i, j, CPE);
            run_data[func_count].split_idx = i;
            run_data[func_count].unrol_idx = j;
            run_data[func_count].cpe = CPE;
            if (CPE < min) {
                *best_unroll_idx = i;
                *best_split_idx = j;
                min = CPE;
            }
            func_count++;
        }
    }
    return min;
}

double compare_test(int func_num, int *min_cpe_idx, char *argv[])
{
    long cpu_freq = read_cpu_freq();
    printf("freq = %ld hz\n", cpu_freq);

    int split_num[64];
    int unrol_num[64];
    for (int i = 0; i < func_num; i++) {
        separate_argv(argv[i + 2], &split_num[i], &unrol_num[i]);
    }

    double min = 100.0;
    for (int i = 0; i < func_num; i++) {
        double CPE = 0.0;
        // if j is 0 cannot compute the ratio (CPE / j)
        for (int j = DEGREE_STEP; j < MAX_DEGREE; j += DEGREE_STEP) {
            int func_idx = (split_num[i] - 1) * 8 + (unrol_num[i] - 1);
            double cycle = test_poly(func_arr[func_idx], j, cpu_freq);
            CPE += (cycle / j);
        }
        CPE /= (MAX_DEGREE / DEGREE_STEP - 1);
        if (CPE < min) {
            *min_cpe_idx = i;
            min = CPE;
        }
    }
    return min;
}

void plot_test(int func_num, char *argv[])
{
    long cpu_freq = read_cpu_freq();
    printf("freq = %ld hz\n", cpu_freq);

    gen_plot(func_num, argv);

    int split_num[64];
    int unrol_num[64];
    for (int i = 0; i < func_num; i++) {
        separate_argv(argv[i + 2], &split_num[i], &unrol_num[i]);
    }

    FILE *plot_output = fopen("output.txt", "w");
    for (int i = 0; i < MAX_DEGREE; i += DEGREE_STEP) {
        fprintf(plot_output, "%d ", i);
        double cycle;
        for (int j = 0; j < func_num; j++) {
            int func_idx = (split_num[j] - 1) * 8 + (unrol_num[j] - 1);
            cycle = test_poly(func_arr[func_idx], i, cpu_freq);
            fprintf(plot_output, "%lf ", cycle);
        }
        fprintf(plot_output, "\n");
    }
    fclose(plot_output);
}

int main(int argc, char *argv[])
{
    printf("Please copy the result between lines\n--------------------\n");
    print_cpu_model();
    /* Implement 3 type of operations: default, plot and compare */
    /* check argument correctness */
    if (argc >= 2) {
        if (!strcmp(argv[1], "default") && argc == 2) {
            /* default op should have no further arguments */
            int best_unroll_idx;
            int best_split_idx;
            default_test(&best_unroll_idx, &best_split_idx);

            qsort(run_data, 64, sizeof(run_data[0]), run_data_cmp);
            for (int i = 0; i < 3; i++) {
                printf("%d,%d: %lf\n", run_data[i].split_idx,
                       run_data[i].unrol_idx, run_data[i].cpe);
            }
        } else if (!strcmp(argv[1], "plot")) {
            /*
             *  provide at least 1 more argument to plot
             *  Ex: ./test_poly plot 1,1
             */
            if (argc == 2) {
                runtime_error_message(TOO_FEW_ARGS);
                return 0;
            }
            plot_test(argc - 2, argv);
        } else if (!strcmp(argv[1], "compare")) {
            /*
             *  provide at least 2 more argument to compare
             *  Ex: ./test_poly compare 1,1 2,2 3,3
             */
            if (argc < 4) {  // at least 2 to compare
                runtime_error_message(TOO_FEW_ARGS);
                return 0;
            }
            int min_cpe_idx;
            double min_cpe = compare_test(argc - 2, &min_cpe_idx, argv);
            printf("Best split & unroll: %s\n", argv[min_cpe_idx + 2]);
            printf("Lowest CPE = %lf\n", min_cpe);
        } else if (!strcmp(argv[1], "help")) {
            help_message();
        } else {
            runtime_error_message(WRONG_ARGS);
            return 0;
        }
    }

    printf("--------------------\n");
    printf("Program closing...\n");
    return 0;
}
