#include <stdio.h>
#include <stdlib.h>

#define SPLIT_NUM 8
#define UNROL_NUM 8

int main(int argc, char *argv[]){

    /* header files */
    FILE *hf = fopen("dynamic_poly.h", "w");
    for (int i = 1; i <= SPLIT_NUM; i++) {
        for (int j = 1; j <= UNROL_NUM; j++) {
            fprintf(hf, "double poly_%d_%d(double a[], double x, long d);",
                    i, j);
        }
    }
    fclose(hf);

    /* c files */
    FILE *cf = fopen("dynamic_poly.c", "w");
    for (int i = 1; i <= SPLIT_NUM; i++) {
        for (int j = 1; j <= UNROL_NUM; j++) {
            /* function name */
            fprintf(cf, "double poly_%d_%d(double a[], double x, long degree)",
                    i, j);
            fprintf(cf, "{\n");
            fprintf(cf, "long i;\n");
            /* variables used for splitting */
            fprintf(cf, "double result_0 = a[0];\n");
            for (int k = 1; k < SPLIT_NUM; k++) {
                fprintf(cf, "double result_%d = 0;\n", k);
            }

            /* compute power to the x*/
            int pw_times = i * j;
            fprintf(cf, "double xpwr = x;\n");
            fprintf(cf, "double x_pow_0 = 1;\n");
            fprintf(cf, "double x_pow_1 = x;\n");
            for (int k = 2; k <= pw_times; k++) {
                fprintf(cf, "double x_pow_%d = x_pow_%d * x;\n", k, k - 1);
            }

            /* main for loop */
            fprintf(cf, "for (i = 1; i <= degree - %d; i += %d) {\n",
                    pw_times - 1, pw_times);
            int idx_cnt = 0;
            for (int k = 0; k < i; k++) {
                fprintf(cf, "result_%d += (a[i + %d] * x_pow_%d", k, idx_cnt,
                        idx_cnt);
                idx_cnt++;
                for (int l = 1; l < j; l++) {
                    fprintf(cf, " + a[i + %d] * x_pow_%d", idx_cnt, idx_cnt);
                    idx_cnt++;
                }
                fprintf(cf, ") * xpwr;\n");
            }
            fprintf(cf, "xpwr = xpwr * x_pow_%d;\n", pw_times);
            fprintf(cf, "}");

            /* remain element */
            fprintf(cf, "for (; i <= degree; i++) {\n");
            fprintf(cf, "result_0 += a[i] * xpwr;\n");
            fprintf(cf, "xpwr = xpwr * x;\n}");

            /* sum the all splitting variables */
            fprintf(cf, "return result_0");
            for (int k = 1; k < SPLIT_NUM; k++) {
                fprintf(cf, " + result_%d", k);
            }
            fprintf(cf, ";\n");
            fprintf(cf, "}");
        }
    }
    fclose(cf);
    return 0;
}
