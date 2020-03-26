  //////////////////////////////////////////////////////T E S T S//////////////////////////////////////////////////////

    *((double complex *)A) = 1 + 1 * I;
    *((double complex *)A + 1) = 0 + 1 * I;
    polynomial test_pol_1 = {COMPLEX, A, 2};
    *((double *)B) = 1;i=1;
    polynomial test_pol_2 = {DOUBLE, B, 1};

    if ((max_pol(test_pol_1, test_pol_2).el_type == test_pol_1.el_type) && (max_pol(test_pol_1, test_pol_2).power == test_pol_1.power))
        printf("%s", "1)TEST PASSED!\n");
    else
        printf("%s", "1)TEST FAILED\n");

    if ((min_pol(test_pol_1, test_pol_2).el_type == test_pol_2.el_type) && (min_pol(test_pol_1, test_pol_2).power == test_pol_2.power))
        printf("%s", "2)TEST PASSED!\n");
    else
        printf("%s", "2)TEST FAILED\n");

    if (max_power(test_pol_1, test_pol_2) == test_pol_1.power)
        printf("%s", "3)TEST PASSED!\n");
    else
        printf("%s", "3)TEST FAILED\n");

    if (min_power(test_pol_1, test_pol_2) == test_pol_2.power)
        printf("%s", "4)TEST PASSED!\n");
    else
        printf("%s", "4)TEST FAILED\n");

    multiply_polynomials(test_pol_1, test_pol_2, tmp);
    if (*((double complex *)tmp) == 1 + 1 * I)
        printf("%s", "5)TEST PASSED!\n");
    else
        printf("%s", "5)TEST FAILED\n");

    add_polynomials(test_pol_1, test_pol_2, tmp);
    if (*((double complex *)tmp) == 2 + 1 * I)
        printf("%s", "6)TEST PASSED!\n");
    else
        printf("%s", "6)TEST FAILED\n");

    calculate_if_x_number(test_pol_1, tmp, i);
    if (*((double complex *)tmp) == 1 + 2 * I)
        printf("%s", "7)TEST PASSED!\n");
    else
        printf("%s", "7)TEST FAILED\n");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
