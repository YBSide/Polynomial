#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>
typedef enum {DOUBLE, COMPLEX} el_type;
struct polynomial {
    el_type el_type;
    void *odds;
    int power;
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

void multiply_polynomials(polynomial p, polynomial q) {
    printf("multiply: ");
    polynomial result;
    result.odds = malloc(sizeof(double) * (max_power(p, q) * 2 + min_power(p, q)));
    int i, j, l;
    for (i=0; i<(max_power(p, q) + min_power(p, q)); ++i) {
        if ((p.el_type == COMPLEX) || (q.el_type == COMPLEX)) {
            result.el_type = COMPLEX;
            *((double complex *)result.odds + i) = 0 + 0 * I;
        }
        else {
            result.el_type = DOUBLE;
            *((double *)result.odds + i) = 0;
        }
    }

    for (i=0; i<max_power(p, q); ++i) {
        for (j=0; j<min_power(p, q); ++j) {
            if ((min_pol(p, q).el_type == COMPLEX) && (max_pol(p, q).el_type == min_pol(p, q).el_type))
                *((double complex *)result.odds + i + j) += *((double complex *)max_pol(p, q).odds + i) * *((double complex *)min_pol(p, q).odds + j);
            if ((min_pol(p, q).el_type == DOUBLE) && (max_pol(p, q).el_type == min_pol(p, q).el_type))
                *((double *)result.odds + i + j) += *((double *)max_pol(p, q).odds + i) * *((double *)min_pol(p, q).odds + j);
            if ((min_pol(p, q).el_type == COMPLEX) && (max_pol(p, q).el_type == DOUBLE))
                *((double complex *)result.odds + i + j) += *((double *)max_pol(p, q).odds + i) * *((double complex *)min_pol(p, q).odds + j);
            if ((min_pol(p, q).el_type == DOUBLE) && (max_pol(p, q).el_type == COMPLEX))
                *((double complex *)result.odds + i + j) += *((double complex *)max_pol(p, q).odds + i) * *((double *)min_pol(p, q).odds + j);
        }
    }
    for(l=0; l<i+j; ++l) {
        if (result.el_type == COMPLEX) {
            if ((*((double complex *)result.odds + l) == 0) && (i == 1) && (j == 1) && (l == 0))
                printf("%s%g%s%g%s","(", creal(*((double complex *)result.odds + l)), " + ", cimag(*((double complex *)result.odds + l)), "*I)");
            if (*((double complex *)result.odds + l) != 0)  {
                printf("%s%g%s%g%s","(", creal(*((double complex *)result.odds + l)), " + ", cimag(*((double complex *)result.odds + l)), "*I)");
                printf("%s%d", "x^", l);
                if (l != i+j-2)
                    printf("%s", " + ");

            }
        }
        else {
            if ((*((double *)result.odds + l) == 0) && (i == 1) && (j == 1) && (l == 0))
                printf("%g", *((double *)result.odds + l));
            if (*((double *)result.odds + l) != 0)  {
                printf("%g", *((double *)result.odds + l));
                printf("%s%d", "x^", l);
                if (l != i+j-2)
                    printf("%s", " + ");
            }

        }
    }
    printf("\n");
}

void add_polynomials(polynomial p, polynomial q) {
    printf("add: ");
    polynomial result;
    if ((p.el_type == DOUBLE) && (q.el_type == DOUBLE))
        result.odds = malloc(100*sizeof(double));
    if ((p.el_type == COMPLEX) || (q.el_type == COMPLEX))
        result.odds = malloc(100*sizeof(complex));
    result.power = max_power(p, q);
    for (int i=0; i < max_power(p, q); ++i) {
        if (i<min_power(p, q)) {
            if ((min_pol(p, q).el_type == COMPLEX) && (max_pol(p, q).el_type == min_pol(p, q).el_type)) {
                *((double complex*)result.odds + i)= *((double complex*)max_pol(p, q).odds + i) + *((double complex*)min_pol(p, q).odds + i);
                result.el_type = COMPLEX;
            }
            if ((min_pol(p, q).el_type == DOUBLE) && (max_pol(p, q).el_type == min_pol(p, q).el_type)) {
                *((double*)result.odds + i) = *((double*)max_pol(p, q).odds + i) + *((double*)min_pol(p, q).odds + i);
                result.el_type = DOUBLE;
            }
            if ((min_pol(p, q).el_type == COMPLEX) && (max_pol(p, q).el_type == DOUBLE)){
                *((double complex*)result.odds + i)= creal(*((double complex*)min_pol(p, q).odds + i)) + *((double*)max_pol(p, q).odds + i) + cimag(*((double complex*)min_pol(p, q).odds + i)) * I;
                result.el_type = COMPLEX;
            }
            if ((min_pol(p, q).el_type == DOUBLE) && (max_pol(p, q).el_type == COMPLEX)){
                *((double complex*)result.odds + i) = creal(*((double complex*)max_pol(p, q).odds + i)) + *((double*)min_pol(p, q).odds + i) + cimag(*((double complex*)max_pol(p, q).odds + i)) * I;
                result.el_type = COMPLEX;
            }
        }
        else {
            if (max_pol(p, q).el_type == COMPLEX)
                *((double complex*)result.odds + i) = *((double complex*)max_pol(p, q).odds + i) + 0 + 0 * I;
            if ((max_pol(p, q).el_type == DOUBLE) && (min_pol(p, q).el_type == DOUBLE))
                *((double*)result.odds + i) = *((double*)max_pol(p, q).odds + i) + 0;
            if ((max_pol(p, q).el_type == DOUBLE) && (min_pol(p, q).el_type == COMPLEX))
                *((double complex*)result.odds + i) = *((double *)max_pol(p, q).odds + i) + 0 + 0 * I;

        }
        if (result.el_type == COMPLEX) {
            if (*((double complex*)result.odds + i) != 0 + 0 * I) {
                printf("%s%g%s%g%s","(", creal(*((double complex*)result.odds + i)), " + ", cimag(*((double complex*)result.odds + i)), "*I)");
                    printf("%s%d", "x^", i);
                if (i != max_power(p, q)-1)
                    printf("%s", " + ");
            }
        }
        else if (*((double*)result.odds + i) != 0) {
            printf("%g", *((double*)result.odds + i));
                printf("%s%d", "x^", i);
            if (i != max_power(p, q)-1)
                printf("%s", " + ");
        }

    }
    printf("\n");
    free(result.odds);
}

void calculate_if_x_number (polynomial p) {
    int validation_check = 0;
    double complex complex_result = 0 + 0 * I;
    double real_result=0;
    double real;
    double imag;
    if (p.el_type == COMPLEX) {
        printf("%s", "Enter the real and imaginary part of argument: ");
        validation_check = scanf("%lf%lf", &real, &imag);
        if (validation_check != 2) {
            printf("%s", "Incorrect answer.GET OUT!!!\n");
            exit(1);
        }
        for (int i=0; i<p.power; ++i)
            complex_result = complex_result + *((double complex *)p.odds + i) * cpow(real + imag * I, i);
        printf("%g%s%g%s",creal(complex_result), " + ", cimag(complex_result), "*I\n");
    }
    else {

        printf("%s", "Enter the real part of argument: ");
        validation_check = scanf("%lf", &real);
        if (validation_check != 1) {
            printf("%s", "Incorrect answer.GET OUT!!!\n");
            exit(1);
        }
        for (int i=0; i<p.power; ++i)
            real_result = real_result + *((double *)p.odds + i) * pow(real, i);
        printf("%g%s",real_result, "\n");
    }
}

void *set_elements(void *array, el_type el_type, int *power) {
    int index_pointer=0;
    int validation_check=0;
    char answer[30]="";
    double real;
    double imag;
    // array = calloc(100, sizeof(void*));
    if (el_type == DOUBLE)
        array = malloc(100*sizeof(double));
    if (el_type == COMPLEX)
        array = malloc(100*sizeof(complex));
    while (strcmp(answer, "n")) {
        if (el_type == COMPLEX) {
            printf("%s%d%s", "Enter the real and imaginary part of the coefficient at x^",
                   index_pointer, ": ");
            validation_check = scanf("%lf%lf", &real, &imag);
            if (validation_check != 2) {
                printf("%s", "Incorrect answer.GET OUT!!!\n");
                exit(1);
            }
        }
        if (el_type == DOUBLE) {
            printf("%s%d%s", "Enter the real part of the coefficient at x^",
                   index_pointer, ": ");
            validation_check = scanf("%lf", &real);
            if (validation_check != 1) {
                printf("%s", "Incorrect answer.GET OUT!!!\n");
                exit(1);
            }
        }

        if (el_type == COMPLEX) {
            *((double complex *)array + index_pointer) = real + imag * I;
        }
        if (el_type == DOUBLE) {
            *((double *)array + index_pointer) = real;
        }
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
    *power = index_pointer;
    return array;
}


int main() {
    void *A;
    void *B;
    int *power = malloc(sizeof(int));
    char answer[30];
    char element_type[2];
    el_type el_type;
    printf("%s", "First polynomial.\n");
    printf("%s", "Enter element type. DOUBLE(d) or COMPLEX(c)");
    scanf("%s", element_type);
    while (strcmp(element_type, "d") && strcmp(element_type, "c")) {
        printf("%s", "Incorrect answer.\n ");
        scanf("%s", element_type);
    }
    if (!strcmp(element_type, "c"))
        el_type = COMPLEX;
    else
        el_type = DOUBLE;
    A = set_elements(A, el_type, power);
    polynomial first_polynomial = {el_type, A, *power};
    printf("%s", "Second polynomial.\n");
    printf("%s", "Enter element type. DOUBLE(d) or COMPLEX(c)");
    scanf("%s", element_type);
    while (strcmp(element_type, "d") && strcmp(element_type, "c")) {
        printf("%s", "Incorrect answer.\n ");
        scanf("%s", element_type);
    }
    if (!strcmp(element_type, "c"))
        el_type = COMPLEX;
    else
        el_type = DOUBLE;
    B = set_elements(B, el_type, power);
    polynomial second_polynomial = {el_type, B, *power};
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




