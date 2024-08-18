#include <TXLib.h>
#include <stdio.h>
#include <math.h>
int solve_qe(double a, double b, double c, double *px1, double *px2);
int solve_nonqe(double b, double c, double *px1);  // Solve linear equation (a = 0)
void answer_qe(int number, double x1, double x2);  // Print answer of the quadratic equation

int main()
{
    int number = 0;  // Number of solutions (3 = infinite)
    double a = 0; double b = 0; double c = 0;
    double x1 = 0; double x2 = 0;

    printf("Enter the coefficients of quadratic equation:\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);

    number = solve_qe(a, b, c, &x1, &x2);
    answer_qe(number, x1, x2);

    return 0;
}


void answer_qe(int number, double x1, double x2)  // Print answer of the quadratic equation
{
    if (number == 0)
        printf("This equation has no real roots\n");
    else if (number == 1)
        printf("This equation has only one real root: %.2f\n", x1);
    else if (number == 2)
        printf("This equation has only two real roots: %.2f; %.2f\n", x1, x2);
    else if (number == 3)
        printf("This equation has an infinite number of real roots\n");
    else
        printf("Unknown error\n");
}


int solve_qe(double a, double b, double c, double *px1, double *px2)
{
    double D = b*b - 4*a*c;
    if (abs(a) <= 0.1E-10)
        return solve_nonqe(b, c, px1);
    else if (D < 0)
        return 0;
    else if (abs(D) <= 0.1E-10) {
        *px1 = -b/(2*a);
        return 1;
    }
    else {
        *px1 = (-b + sqrt(D))/(2*a);
        *px2 = (-b - sqrt(D))/(2*a);
        return 2;
    }
}


int solve_nonqe(double b, double c, double *px1)  // Solve linear equation (a = 0)
{
    if (abs(b) <= 0.1E-10) {
        if (abs(c) <= 0.1E-10)
            return 3;
        else
            return 0;
    }
    else {
        *px1 = -c/b;
        return 1;
    }
}
