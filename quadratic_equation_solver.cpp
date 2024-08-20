#include <stdio.h>
#include <math.h>
#include <assert.h>

int input_coefs(double* a, double* b, double* c);
int solve_quad_eq(double a, double b, double c, double *x1, double *x2);
int solve_line_eq(double b, double c, double *x1);
int print_roots(int number, double x1, double x2);
bool ezero(double x);

enum ROOTS_NUMBER
{
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INFINITE_NUM_OF_ROOTS
};
struct coefficients
{
    double a;
    double b;
    double c;
};
struct roots
{
    double x1;
    double x2;
};

int main()
{
    struct coefficients coefs = {0, 0, 0};
    struct roots roots = {0, 0};
    int equation_roots_number = 0;
    int code_status = 0;

    code_status = input_coefs(&coefs.a, &coefs.b, &coefs.c);
    if (code_status != 0)
        return code_status;
    equation_roots_number = solve_quad_eq(coefs.a, coefs.b, coefs.c, &roots.x1, &roots.x2);
    code_status = print_roots(equation_roots_number, roots.x1, roots.x2);

    return code_status;
}


int input_coefs(double* a, double* b, double* c)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(a != b);
    assert(a != c);
    assert(b != c);

    printf("# Enter the coefficients of quadratic equation:\n");

    printf("# a = ");
    if (scanf("%lf", a) != 1)
    {
        printf("Invalid value");
        return 1;
    }

    printf("# b = ");
    if (scanf("%lf", b) != 1)
    {
        printf("Invalid value");
        return 1;
    }

    printf("# c = ");
    if (scanf("%lf", c) != 1)
    {
        printf("Invalid value");
        return 1;
    }
    return 0;
}


int solve_quad_eq(double a, double b, double c, double* x1, double* x2)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    double D = b*b - 4*a*c;
    if (ezero(a))
        return solve_line_eq(b, c, x1);
    else if (D < 0)
        return 0;
    else if (ezero(D))
    {
        *x1 = -b/(2*a);
        return 1;
    }
    else
    {
        *x1 = (-b - sqrt(D))/(2*a);
        *x2 = (-b + sqrt(D))/(2*a);
        return 2;
    }
}


int solve_line_eq(double b, double c, double* x1)
{
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    assert(x1 != NULL);

    if (ezero(b))
    {
        if (ezero(c))
            return 3;
        else
            return 0;
    }
    else
    {
        *x1 = -c/b;
        return 1;
    }
}


int print_roots(int number, double x1, double x2)
{
    assert(std::isfinite(number));
    assert(std::isfinite(x1));
    assert(std::isfinite(x2));

    if (ezero(x1))
        x1 = 0.0;
    if (ezero(x2))
        x2 = 0.0;

    switch (number)
    {
        case NO_ROOTS:
        {
            printf("This equation has no real roots\n");
            return 0;
        }
        case ONE_ROOT:
        {
            printf("This equation has only one real root: %.2f\n", x1);
            return 0;
        }
        case TWO_ROOTS:
        {
            printf("This equation has only two real roots: %.2f; %.2f\n", x1, x2);
            return 0;
        }
        case INFINITE_NUM_OF_ROOTS:
        {
            printf("This equation has an infinite number of real roots\n");
            return 0;
        }
        default:
        {
            printf("Unknown error:\n"
                   "print_roots(): variable number = %d is invalid\n", number);
            return 1;
        }
    }
}


bool ezero(double x)
{
    assert(std::isfinite(x));
    return abs(x) <= 0.1E-7;
}
