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

double poly_5_06(double a[], double x, long degree)
{
    long i;
    double result = a[degree];
    for (i = degree - 1; i >= 0; i--) {
        result = a[i] + x * result;
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
    for (i = 1; i < degree - 1; i += 2) {
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
    for (i = 1; i < degree - 1; i += 3) {
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

double poly_5_05_rev(double a[], double x, long degree)
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
    for (i = 1; i < degree - 2; i += 4) {
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

double poly_5_06_rev(double a[], double x, long degree)
{
    long i;
    double result = a[degree];
    for (i = degree - 1; i >= 3; i -= 3) {
        result = a[i] + x * result;
        result = a[i - 1] + x * result;
        result = a[i - 2] + x * result;
    }

    for (; i > 0; i--) {
        result = a[i] + x * result;
    }

    return result;
}
