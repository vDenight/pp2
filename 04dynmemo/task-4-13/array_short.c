//
// Created by mcihal on 11.05.25.
//

#include <stdlib.h>
#include "array_short.h"

#include <stdio.h>
#include <string.h>

short *create_array_short(int N) {
    if (N <= 0) return NULL;

    short *arr = NULL;
    arr = (short *)malloc(sizeof(short) * N);
    if (arr == NULL) return NULL;

    return arr;
}

short *concatenate_arrays_short(const short *a1, int size1, const short *a2, int size2, int *err_code) {
    if (a1 == NULL || a2 == NULL || size1 <= 0 || size2 <= 0) {
    if (err_code) *err_code = INCORRECT_INPUT;
        return NULL;
    }

    short *conc_arr = NULL;
    conc_arr = (short *)malloc(sizeof(short) * (size1 + size2));
    if (conc_arr == NULL) {
        if (err_code) *err_code = ALLOC_FAIL;
        return NULL;
    }

    int j = 0;

    // first array
    for (int i = 0; i < size1; i++, j++) memcpy(conc_arr + j, a1 + i, sizeof(short));

    // second array
    for (int i = 0; i < size2; i++, j++) memcpy(conc_arr + j, a2 + i, sizeof(short));

    if (err_code) *err_code = OK;
    return conc_arr;
}

int short_compare(const void* short_one, const void* short_two) {
    return *((short *)short_one) - *((short *)short_two);
}

int sort_short(short* tab, int size) {
    if (tab == NULL || size <= 0) return INCORRECT_INPUT;
    qsort(tab, (int) size, (int) sizeof(short), short_compare);

    return OK;
}

void display_vector_short(const short* tab, int size) {
    if (tab == NULL || size <= 0) return;
    for (int i = 0; i < size; i++) {
        printf("%d ", *(tab + i));
    }
    printf("\n");
}
