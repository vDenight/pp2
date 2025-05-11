#include <stdio.h>
#include <stdlib.h>

#include "array_short.h"

enum main_codes {
    MAIN_OK = 0,
    MAIN_INCORRECT_INPUT = 1,
    MAIN_INCORRECT_INPUT_DATA = 2,
    MAIN_ALLOC_FAIL = 8
};

int main(void) {
    short* array_one = NULL, *array_two = NULL, *array_three = NULL;
    int size_one = 0, size_two = 0;

    printf("Podaj rozmiar tablicy: ");

    if (scanf("%d", &size_one) != 1) {
        printf("Incorrect input");
        return MAIN_INCORRECT_INPUT;
    }

    if (size_one < 1) {
        printf("Incorrect input data");
        return MAIN_INCORRECT_INPUT_DATA;
    }

    array_one = create_array_short(size_one);
    if (array_one == NULL) {
        printf("Failed to allocate memory");
        return MAIN_ALLOC_FAIL;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < size_one; i++) {
        if (scanf("%hd", array_one + i) != 1) {
            free(array_one);
            printf("Incorrect input");
            return MAIN_INCORRECT_INPUT;
        }
    }

    printf("Podaj rozmiar drugiej tablicy: ");

    if (scanf("%d", &size_two) != 1) {
        free(array_one);
        printf("Incorrect input");
        return MAIN_INCORRECT_INPUT;
    }

    if (size_two< 1) {
        free(array_one);
        printf("Incorrect input data");
        return MAIN_INCORRECT_INPUT_DATA;
    }

    array_two = create_array_short(size_two);
    if (array_two == NULL) {
        free(array_one);
        printf("Failed to allocate memory");
        return MAIN_ALLOC_FAIL;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < size_two; i++) {
        if (scanf("%hd", array_two + i) != 1) {
            free(array_one);
            free(array_two);
            printf("Incorrect input");
            return MAIN_INCORRECT_INPUT;
        }
    }

    int err_code;
    array_three = concatenate_arrays_short(array_one, size_one,
         array_two, size_two, &err_code);
    if (err_code == ALLOC_FAIL) {
        free(array_one);
        free(array_two);
        printf("Failed to allocate memory");
        return MAIN_ALLOC_FAIL;
    }

    sort_short(array_three, size_one + size_two);
    display_vector_short(array_three, size_one + size_two);

    free(array_one);
    free(array_two);
    free(array_three);
    return MAIN_OK;
}