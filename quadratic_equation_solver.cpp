#include <stdio.h>
#include <math.h>
void solve_qe(int a, int b, int c);

main()
{
    int a, b, c;

    printf("Enter the coefficients of quadratic equation:\n");
    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    printf("c = ");
    scanf("%d", &c);

    solve_qe(a, b, c);
    return 0;
}


void solve_qe(int a, int b, int c)
{
    float D = b*b - 4*a*c;
    if (a == 0) {
        printf("This equation is not quadratic");
        return;
    }
    if (D < 0) {
        printf("This equation has no real roots");
        return;
    }
    if (D == 0) {
        float x = -b/(2*a);
        printf("This equation has only one real root: %.2f", x);
        return;
    }
    else {
        float x1, x2;
        x1 = (-b + sqrt(D))/(2*a);
        x2 = (-b - sqrt(D))/(2*a);
        printf("This equation has only two real roots: %.2f; %.2f", x1, x2);
        return;
    }
}
