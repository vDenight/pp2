//
// Created by mrybczynski on 5/28/2025.
//
#include "comparators.h"
#include <stdlib.h>
#include <stddef.h>

int comp_int(int a, int b) {
    return a - b;
}

int comp_int_abs(int a, int b) {
    return abs(a) - abs(b);
}

int comp_int_length(int a, int b) {
    int a_digits = 1;
    int b_digits = 1;

    while ((a = a/10) != 0) {
        a_digits++;
    }

    while ((b = b/10) != 0) {
        b_digits++;
    }

    return a_digits - b_digits;
}

int comp_int_digits_sum(int a, int b) {
    a = abs(a);
    b = abs(b);
    int current_mgn = 1;
    int digit_sum_a = 0;
    int digit_sum_b = 0;
    for (int i = 0; i < 9; i++) {
        digit_sum_a += (a % (current_mgn * 10)) / current_mgn;
        digit_sum_b += (b % (current_mgn * 10)) / current_mgn;
        current_mgn *= 10;
    }

    return digit_sum_a - digit_sum_b;
}

int sort_int(int* tab, int size, int(*comparator)(int, int)) {

    if (tab == NULL || size <= 0 || comparator == NULL) return 1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (comparator(*(tab + j), *(tab + j + 1)) > 0) {
                int temp = *(tab + j);
                *(tab + j) = *(tab + j + 1);
                *(tab + j + 1) = temp;
            }
        }
    }

    return 0;
}
