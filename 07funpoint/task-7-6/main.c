#include <stdio.h>
#include <stdlib.h>

#include "comparators.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

int main() {

    int (**funcs)(int, int) = calloc(4, sizeof(int (*)(int, int)));

    if (funcs == NULL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    *funcs = comp_int;
    *(funcs + 1) = comp_int_abs;
    *(funcs + 2) = comp_int_length;
    *(funcs + 3) = comp_int_digit_sum;

    int arr_len = 0;
    printf("Podaj dlugosc tablicy: ");
    if (!scanf("%d", &arr_len)) {
        free(funcs);
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (arr_len < 1) {
        free(funcs);
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    // now we alloc the table
    int* tab = calloc(arr_len, sizeof(int));
    if (!tab) {
        free(funcs);
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < arr_len; i++) {
        if (!scanf("%d", (tab + i))) {
            free(tab);
            free(funcs);
            printf("Incorrect input");
            return INCORRECT_INPUT;
        }
    }

    int op;
    printf("Podaj rodzaj operacji: ");
    if (!scanf("%d", &op)) {
        free(tab);
        free(funcs);
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    if (op < 0 || op > 3) {
        free(tab);
        free(funcs);
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    sort_int(tab, arr_len, *(funcs + op));

    for (int i = 0; i < arr_len; i++) {
        printf("%d ", *(tab + i));
    }

    free(tab);
    free(funcs);
    return 0;
}