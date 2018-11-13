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

double poly_5_05_rev(double a[], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr = x;
    double x_square = x * x;
    double x_qube = x * x_square;
    for (i = 1; i < degree - 1; i += 3) {
        result += a[i] * xpwr;
        result += a[i + 1] * xpwr * x;
        result += a[i + 2] * xpwr * x_square;
        xpwr = xpwr * x_qube;
    }

    for (; i <= degree; i++) {
        result += a[i] * xpwr;
        xpwr = xpwr * x;
    }
    return result;
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
