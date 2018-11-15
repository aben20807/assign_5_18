double poly_5_06(double a[], double x, long degree)
{
    long i;
    double result = a[degree];
    for (i = degree - 1; i >= 0; i--) {
        result = a[i] + x * result;
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
