double poly_5_05_rev(double a[], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr[degree];
    xpwr[0] = 1;
    for (i = 1; i <= degree; i++) {
        xpwr[i] = xpwr[i - 1] * x;
    }
    for (i = 1; i <= degree; i++) {
        result += a[i] * xpwr[i];
    }
    return result;
}
