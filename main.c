#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>

struct polynomial {
    int power;
    double complex *odds;
};
typedef struct polynomial polynomial;

polynomial max_pol(polynomial p, polynomial q) {
    polynomial max_pol;
    if (p.power <= q.power)
        max_pol = q;
    else
        max_pol = p;
    return max_pol;
}

polynomial min_pol(polynomial p, polynomial q) {
    polynomial min_pol;
    if (p.power <= q.power)
        min_pol = p;
    else
        min_pol = q;
    return min_pol;
}

int max_power(polynomial p, polynomial q) {
    int max_power;

    if (p.power <= q.power)
        max_power = q.power;
    else
        max_power = p.power;
    return max_power;
}

int min_power(polynomial p, polynomial q) {
    int min_power;
    if (p.power <= q.power)
        min_power = p.power;
    else
        min_power = q.power;
    return min_power;
}

void add_polynomials(polynomial p, polynomial q) {
    printf("add: ");
    polynomial result;
    result.odds = malloc(sizeof(double) * max_power(p, q) * 2);
    result.power = max_power(p, q);
    for (int i=0; i < max_power(p, q); ++i) {
        if (i<min_power(p, q))
            result.odds[i] = max_pol(p, q).odds[i] + min_pol(p, q).odds[i];
        else
            result.odds[i] = max_pol(p, q).odds[i] + (0 + 0 * I);
        if (result.odds[i] != 0) {
            printf("%s%g%s%g%s","(", creal(result.odds[i]), " + ", cimag(result.odds[i]), "*I)");
            printf("%s%d", "x^",i);
            if (i != max_power(p, q)-1)
                printf("%s", " + ");
        }
    }
    printf("\n");
    free(result.odds);
}

void multiply_polynomials(polynomial p, polynomial q) {
    printf("multiply: ");
    polynomial result;
    result.odds = malloc(sizeof(double) * (max_power(p, q) * 2 + min_power(p, q)));
    int i, j, l;
    for (i=0; i<(max_power(p, q) + min_power(p, q)); ++i)
        result.odds[i] = 0 + 0 * I;
    for (i=0; i<max_power(p, q); ++i) {
        for (j=0; j<min_power(p, q); ++j) {
            result.odds[i+j] += max_pol(p, q).odds[i] * min_pol(p, q).odds[j];
        }
    }
    for(l=0; l<i+j; ++l) {
        if ((result.odds[l] == 0) && (i == 1) && (j == 1) && (l == 0))
            printf("%s%g%s%g%s","(", creal(result.odds[l]), " + ", cimag(result.odds[l]), "*I)");
        if (result.odds[l] != 0)  {
            printf("%s%g%s%g%s","(", creal(result.odds[l]), " + ", cimag(result.odds[l]), "*I)");
            printf("%s%d", "x^",l);
            if (l != i+j-2)
                printf("%s", " + ");

        }
    }
    printf("\n");
}

int set_elements(double complex **array) {
    int index_pointer=0;
    char answer[30]="";
    double real;
    double imag;
    *array = malloc(100 * sizeof(double) * 2);
    while (strcmp(answer, "n")) {
        printf("%s%d%s", "Enter the real and imaginary part of the coefficient at x^",
                index_pointer, ": ");
        scanf("%lf%lf", &real, &imag);
        (*array)[index_pointer] = real + imag * I;
        ++index_pointer;
        printf("%s", "Do you want to continue enter odds? YES(y) or NO(n).\n");
        scanf("%s", answer);
        while (strcmp(answer, "n") && strcmp(answer, "y")) {
            printf("%s", "Incorrect answer.\n ");
            scanf("%s", answer);
        }
        if (!strcmp(answer, "n"))
            break;
    }
    return index_pointer;
}

void calculate_if_x_number (polynomial p) {
    double complex result=0 + 0 * I;
    double real;
    double imag;
    printf("%s", "Enter the real and imaginary part of argument: ");
    scanf("%lf%lf", &real, &imag);
    for (int i=0; i<p.power; ++i)
        result = result + p.odds[i] * cpow(real + imag * I, i);
    printf("%g%s%g%s",creal(result), " + ", cimag(result), "*I\n");
}

int main() {
    double complex *A;
    double complex *B;
    char answer[30];
    printf("%s", "First polynomial.\n");
    polynomial first_polynomial = {set_elements(&A), A};
    printf("%s", "Second polynomial.\n");
    polynomial second_polynomial = {set_elements(&B), B};
    add_polynomials(first_polynomial, second_polynomial);
    multiply_polynomials(first_polynomial, second_polynomial);
    printf("%s", "Do you want to indicate argument for calculating polynomials? YES(y) or NO(n).\n");
    scanf("%s", answer);
    while (strcmp(answer, "n") && strcmp(answer, "y")) {
        printf("%s", "Incorrect answer.\n ");
        scanf("%s", answer);
    }
    if (!strcmp(answer, "y")) {
        printf("%s", "Calculated first polynomial: ");
        calculate_if_x_number(first_polynomial);
        printf("%s", "Calculated second polynomial: ");
        calculate_if_x_number(second_polynomial);
    }
    free(A);
    free(B);
    return 0;
}




