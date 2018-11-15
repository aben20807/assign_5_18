double poly_5_05(double a[], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr = x;
    for (i = 1; i <= degree; i++) {
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}

double poly_5_05_rev_2(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    for (i = 1; i <= degree - 1; i += 2) {
        result_0 += a[i] * xpwr;
        result_1 += a[i + 1] * xpwr * x;
        xpwr = xpwr * x_pow_2;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1;
}

double poly_5_05_rev_3(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double result_2 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    for (i = 1; i <= degree - 2; i += 3) {
        result_0 += a[i] * xpwr;
        result_1 += a[i + 1] * xpwr * x;
        result_2 += a[i + 2] * xpwr * x_pow_2;
        xpwr = xpwr * x_pow_3;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1 + result_2;
}

double poly_5_05_rev_4(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double result_2 = 0;
    double result_3 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    double x_pow_4 = x * x_pow_3;
    for (i = 1; i <= degree - 3; i += 4) {
        result_0 += a[i] * xpwr;
        result_1 += a[i + 1] * xpwr * x;
        result_2 += a[i + 2] * xpwr * x_pow_2;
        result_3 += a[i + 3] * xpwr * x_pow_3;
        xpwr = xpwr * x_pow_4;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1 + result_2 + result_3;
}

double poly_5_05_rev_5(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double result_2 = 0;
    double result_3 = 0;
    double result_4 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    double x_pow_4 = x * x_pow_3;
    double x_pow_5 = x * x_pow_4;
    for (i = 1; i <= degree - 4; i += 5) {
        result_0 += a[i] * xpwr;
        result_1 += a[i + 1] * xpwr * x;
        result_2 += a[i + 2] * xpwr * x_pow_2;
        result_3 += a[i + 3] * xpwr * x_pow_3;
        result_4 += a[i + 4] * xpwr * x_pow_4;
        xpwr = xpwr * x_pow_5;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1 + result_2 + result_3 + result_4;
}

double poly_5_05_rev_6(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double result_2 = 0;
    double result_3 = 0;
    double result_4 = 0;
    double result_5 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    double x_pow_4 = x * x_pow_3;
    double x_pow_5 = x * x_pow_4;
    double x_pow_6 = x * x_pow_5;
    for (i = 1; i <= degree - 5; i += 6) {
        result_0 += a[i] * xpwr;
        result_1 += a[i + 1] * xpwr * x;
        result_2 += a[i + 2] * xpwr * x_pow_2;
        result_3 += a[i + 3] * xpwr * x_pow_3;
        result_4 += a[i + 4] * xpwr * x_pow_4;
        result_5 += a[i + 5] * xpwr * x_pow_5;
        xpwr = xpwr * x_pow_6;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1 + result_2 + result_3 + result_4 + result_5;
}

double poly_5_05_rev_7(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double result_2 = 0;
    double result_3 = 0;
    double result_4 = 0;
    double result_5 = 0;
    double result_6 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    double x_pow_4 = x * x_pow_3;
    double x_pow_5 = x * x_pow_4;
    double x_pow_6 = x * x_pow_5;
    double x_pow_7 = x * x_pow_6;
    for (i = 1; i <= degree - 6; i += 7) {
        result_0 += a[i] * xpwr;
        result_1 += a[i + 1] * xpwr * x;
        result_2 += a[i + 2] * xpwr * x_pow_2;
        result_3 += a[i + 3] * xpwr * x_pow_3;
        result_4 += a[i + 4] * xpwr * x_pow_4;
        result_5 += a[i + 5] * xpwr * x_pow_5;
        result_6 += a[i + 6] * xpwr * x_pow_6;
        xpwr = xpwr * x_pow_7;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1 + result_2 + result_3 + result_4 + result_5 +
           result_6;
}

double poly_5_05_rev_8(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double result_2 = 0;
    double result_3 = 0;
    double result_4 = 0;
    double result_5 = 0;
    double result_6 = 0;
    double result_7 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    double x_pow_4 = x * x_pow_3;
    double x_pow_5 = x * x_pow_4;
    double x_pow_6 = x * x_pow_5;
    double x_pow_7 = x * x_pow_6;
    double x_pow_8 = x * x_pow_7;
    for (i = 1; i <= degree - 7; i += 8) {
        result_0 += a[i] * xpwr;
        result_1 += a[i + 1] * xpwr * x;
        result_2 += a[i + 2] * xpwr * x_pow_2;
        result_3 += a[i + 3] * xpwr * x_pow_3;
        result_4 += a[i + 4] * xpwr * x_pow_4;
        result_5 += a[i + 5] * xpwr * x_pow_5;
        result_6 += a[i + 6] * xpwr * x_pow_6;
        result_7 += a[i + 7] * xpwr * x_pow_7;
        xpwr = xpwr * x_pow_8;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1 + result_2 + result_3 + result_4 + result_5 +
           result_6 + result_7;
}

double poly_5_05_3way(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    for (i = 1; i <= degree - 2; i += 3) {
        result_0 += (a[i] + a[i + 1] * x + a[i + 2] * x_pow_2) * xpwr;
        xpwr = xpwr * x_pow_3;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0;
}

double poly_5_05_6way(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double result_2 = 0;
    double result_3 = 0;
    double result_4 = 0;
    double result_5 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    double x_pow_4 = x * x_pow_3;
    double x_pow_5 = x * x_pow_4;
    double x_pow_6 = x * x_pow_5;
    for (i = 1; i <= degree - 5; i += 6) {
        result_0 += (a[i] + a[i + 1] * x + a[i + 2] * x_pow_2) * xpwr;
        result_3 +=
            (a[i + 3] * x_pow_3 + a[i + 4] * x_pow_4 + a[i + 5] * x_pow_5) *
            xpwr;
        xpwr = xpwr * x_pow_6;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1 + result_2 + result_3 + result_4 + result_5;
}

double poly_5_05_9way(double a[], double x, long degree)
{
    long i;
    double result_0 = a[0];
    double result_1 = 0;
    double result_2 = 0;
    double result_3 = 0;
    double result_4 = 0;
    double result_5 = 0;
    double xpwr = x;
    double x_pow_2 = x * x;
    double x_pow_3 = x * x_pow_2;
    double x_pow_4 = x * x_pow_3;
    double x_pow_5 = x * x_pow_4;
    double x_pow_6 = x * x_pow_5;
    double x_pow_7 = x * x_pow_6;
    double x_pow_8 = x * x_pow_7;
    double x_pow_9 = x * x_pow_8;
    for (i = 1; i <= degree - 8; i += 9) {
        result_0 += (a[i] + a[i + 1] * x + a[i + 2] * x_pow_2) * xpwr;
        result_3 +=
            (a[i + 3] * x_pow_3 + a[i + 4] * x_pow_4 + a[i + 5] * x_pow_5) *
            xpwr;
        result_4 +=
            (a[i + 6] * x_pow_6 + a[i + 7] * x_pow_7 + a[i + 8] * x_pow_8) *
            xpwr;
        xpwr = xpwr * x_pow_9;
    }

    for (; i <= degree; i++) {
        result_0 += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result_0 + result_1 + result_2 + result_3 + result_4 + result_5;
}